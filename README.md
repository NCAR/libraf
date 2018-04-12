# libraf
Library of C and C++ routines for EOL/RAF projects.  Used by external projects ncpp and xpms2d.

## Documentation ###
Functions and subrouties in the libraf library.

| Function | Language | Install location          | Description         |
| -------- | -------- | ------------------------- | ------------------- |
| cio      | (C)      | $LOCAL/src/libraf/cio.c   | Tape I/O utilities that may be used for tape reading/writing, etc. |
| util     | (C)      | $LOCAL/src/libraf/util.c  |  Utilities that may be used for general purpose string manipulation, etc. |
| flote    | (FORTRAN)| $LOCAL/src/libraf/flote.f | A general purpose plotting tick mark finder subroutine. |
| sendpr   | (FORTRAN)| $LOCAL/src/libraf/sendpr.f| A utility used to send output to the system lineprinter from a FORTRAN program. |
| sendhc   | (FORTRAN)| $LOCAL/src/libraf/sendhc.f| A utility used to send output to the system laser printer from a FORTRAN program. |

### Environment ###

### Dependencies ###

### Installation ####
This library may be used by placing a "-lraf" in your compile statement.
