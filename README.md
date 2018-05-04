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

The raf library is written in C. It requires netCDF libraries be installed.

The utilities build and run on any Unix/Linux operating system, including Mac OS X.

### Dependencies ###

To install these programs on your computer, ensure the following libraries are installed:

* netcdf-cxx-devel (will pull in netcdf-cxx, netcdf-devel, and netcdf)

### Installation ####

* git clone https://github.com/ncareol/eol_scons site_scons
* git clone https://github.com/ncar/libraf
* cd libraf
* scons --site_dir=../site_scons <- build libraf.a in the libraf dir
* scons install --site-dir=../site_scons <- install libraf.a under libraf/lib and includes under libraf/include/raf.
* scons install --site-dir=../site_scons --prefix=<path_to_install_dir> <- installs under <path_to_install_dir>/lib and <path_to_install_dir>/include/raf.

This library may be used by placing a "-lraf" in your compile statement.
