/*
-------------------------------------------------------------------------
OBJECT NAME:	pms.c

FULL NAME:	

ENTRY POINTS:	InitPMSspecs()
		ReleasePMSspecs()
		GetPMSparameter()
		GetPMSlist()

STATIC FNS:	none

DESCRIPTION:	

COPYRIGHT:	University Corporation for Atmospheric Research, 1995
-------------------------------------------------------------------------
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "constants.h"
#include "pms.h"

static char	**PMSfile = NULL;

/**
 * true is old processing, prior to 2022.  false is new.
 * Difference in the PMSspecs file is that FIRST_BIN & LAST_BIN will be one less
 * for new processing (e.g.  0 & 30 instead of 1 and 31).
 *
 * New PMSspecs files are marked with a line "NoLegacyZeroBin".
 */
static bool legacyZeroBin = TRUE;

char	*GetMemory(size_t);

/* -------------------------------------------------------------------- */
void InitPMSspecs(const char fileName[])
{
  int	i, cnt, fCnt = 0;
  char	*file[2048], PMSbuffer[512], *p;
  FILE	*fp[5];

  if (PMSfile)
    return;

  if ((fp[fCnt] = fopen(fileName, "r")) == NULL)
    {
    fprintf(stderr, "libpms: Can't open PMSspecs file [%s]\n", fileName);
    exit(1);
    }


  /* Read file and strip out comments.
   */
  for (cnt = 0; fCnt >= 0; )
    {
    if (fgets(PMSbuffer, 512, fp[fCnt]) == NULL)
      {
      fclose(fp[fCnt--]);
      continue;
      }

    if (strstr(PMSbuffer, "NoLegacyZeroBin") )
      legacyZeroBin = FALSE;

    if (strncmp(PMSbuffer, "#include", 8) == 0)
      {
      char	newName[256], *p, *p1;

      strcpy(newName, fileName);
      p1 = strrchr(newName, '/');

      p = strtok(PMSbuffer, "\"");
      p = strtok(NULL, "\"");

      if (p1 == NULL || p[0] == '/')
        strcpy(newName, p);
      else
        strcpy(p1+1, p);

      if ((fp[++fCnt] = fopen(newName, "r")) == NULL)
        {
        fprintf(stderr, "libpms: Can't open PMSspecs include file [%s], continuing.\n", newName);
        --fCnt;
        }

      continue;
      }

    if (PMSbuffer[0] == COMMENT)
      continue;


    PMSbuffer[strlen(PMSbuffer)] = '\0';	/* Ditch newline	*/

    if ( (p = strchr(PMSbuffer, COMMENT)) )
      *p = '\0';
    else
      p = &PMSbuffer[strlen(PMSbuffer)];

    while ( p > PMSbuffer && isspace(*(--p)) )	/* Strip trailing white-space	*/
      *p = '\0';

    if ( isspace(PMSbuffer[0]) )	/* Belongs to previous line	*/
      {
      p = realloc(file[cnt-1], strlen(file[cnt-1]) + strlen(PMSbuffer)+1);

      if (p == NULL)
        {
        fprintf(stderr, "InitPMSspecs: realloc failure.\n");
        exit(1);
        }

      file[cnt-1] = p;
      strcat(file[cnt-1], PMSbuffer);
      }
    else	/* Fresh line		*/
      {
      file[cnt] = GetMemory(strlen(PMSbuffer)+1);
      strcpy(file[cnt], PMSbuffer);
      ++cnt;
      }
    }


  if ((PMSfile = calloc((size_t)cnt+1, sizeof(char *))) == NULL)
    {
    fprintf(stderr, "InitPMSspecs: out of memory.\n");
    exit(1);
    }

  for (i = 0; i < cnt; ++i)
    PMSfile[i] = file[i];

  PMSfile[i] = NULL;
}

/* -------------------------------------------------------------------- */
char *GetPMSparameter(const char serialNumber[], const char parameter[])
{
  int	i;
  char	*p;

  for (i = 0; PMSfile[i]; ++i)
    {
    if (strncmp(PMSfile[i], "START", 5) == 0)
      {
      for (p = &PMSfile[i][5]; *p == ' ' || *p == '\t'; ++p)
        ;

      if (strcmp(serialNumber, p) == 0)
        {
        int	len = strlen(parameter);

        for (; PMSfile[i]; ++i)
          {
          if (strcmp(PMSfile[i], "END") == 0)
            return(NULL);

          if (strncmp(PMSfile[i], parameter, len) == 0)
            {
            if (PMSfile[i][len] != ' ' && PMSfile[i][len] != '\t')
              continue;

            for (p = &PMSfile[i][len]; *p == ' ' || *p == '\t'; ++p)
              ;

            return(p);
            }
          }
        }
      }
    }

  return(NULL);
}

/* -------------------------------------------------------------------- */
void ReleasePMSspecs()
{
  if (PMSfile)
    {
    int	i;

    for (i = 0; PMSfile[i]; ++i)
      free(PMSfile[i]);

    free(PMSfile);

    PMSfile = NULL;
    }
}

/* -------------------------------------------------------------------- */
bool isPMSspecsLegacyZeroBin()
{
  return legacyZeroBin;
}

/* -------------------------------------------------------------------- */
int GetPMSlist(char *list[]) /* returns list of serial numbers */
{
  int     i, cnt = 0;
  char    *p;

  list[0] = NULL;

  for (i = 0; PMSfile[i]; ++i)
    if (strncmp(PMSfile[i], "START", 5) == 0)
      {
      for (p = &PMSfile[i][5]; *p == ' ' || *p == '\t'; ++p)
        ;

      list[cnt] = GetMemory(strlen(p)+1);
      strcpy(list[cnt], p);
      list[++cnt] = NULL;
      }

  return(cnt);
}
