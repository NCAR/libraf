/*
-------------------------------------------------------------------------
OBJECT NAME:	textfile.c

FULL NAME:	Read/Free Text File

DESCRIPTION:	Reads a text file into the user supplied list of pointers.
		Comment lines and blank lines are removed.  A comment line
		is one which starts with '#'.

COPYRIGHT:	University Corporation for Atmospheric Research, 2020
-------------------------------------------------------------------------
*/

#ifndef _libraf_textfile_h_
#define _libraf_textfile_h_

#include <string>
#include <vector>


/* -------------------------------------------------------------------- */
class TextFile {

public:

  TextFile(const std::string& filename);

  size_t size() { return _lines.size(); }

  std::string Line(int index) { return _lines[index]; }
//  const char * Line(int index) { return _lines[index].c_str(); }

protected:
  std::vector<std::string>  _lines;

  static const char COMMENT;

};

#endif
