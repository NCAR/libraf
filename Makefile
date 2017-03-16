#
# Outside users, you may remove util.c cio.c if they don't compile.
#
DESTDIR=
LIBDIR=		${JLOCAL}/lib
MANDIR=		${JLOCAL}/man/man3
INCLUDEDIR=	${JLOCAL}/include

LIBNAME=	raf

DEFINES=	-DPNG

INCLUDES=	-I${JLOCAL}/include
CFLAGS=		-Wall -g -O2 ${INCLUDES}
CXXFLAGS=	-Wall -g -O2 ${INCLUDES} ${DEFINES}
FFLAGS=		-O

OBJS=	strupr.o tapeIO.o getmem.o Xerror.o Xquery.o Xfile.o Xwarn.o \
	util.o raf_queue.o chost.o date.o portable.o ac.o get_ac_name.o \
	nc_time.o ACconfig.o adsIO.o adsIOrt.o Application.o Canvas.o Cursor.o\
        hdrAPI.o gettext.o ntohf.o PixMap.o PMSspex.o PostScript.o\
        Printer.o Queue.o TextWindow.o Time.o validate.o pms_specs.o\
        Window.o XFonts.o XPen.o XmError.o XmFile.o XmQuery.o XmWarn.o

# cio.o flote.o sendhc.o sendpr.o 

SRCS=	strupr.c tapeIO.c getmem.c Xerror.c Xquery.c Xfile.c Xwarn.c \
	util.c raf_queue.c chost.c date.c portable.c ac.c get_ac_name.c \
	nc_time.c ACconfig.cc adsIO.cc adsIOrt.cc Application.cc Canvas.cc Cursor.cc\
        hdrAPI.cc gettext.cc ntohf.cc PixMap.cc PMSspex.cc PostScript.o\
        Printer.cc Queue.cc TextWindow.o Time.cc validate.cc pms_specs.c\
        Window.cc XFonts.cc XPen.cc XmError.cc XmFile.cc XmQuery.cc XmWarn.cc

# cio.c flote.f sendhc.f sendpr.f 

HDRS=	ac.h


all: lib${LIBNAME}.a

ac.o: ac.h
nc_time.o: /usr/include/netcdf.h

# IO classes.
hdrAPI.o:       hdrAPI.h ntohf.h
adsIO.o:        adsIO.h hdrAPI.h
adsIOrt.o:      adsIOrt.h hdrAPI.h
PMSspex.o:      PMSspex.h
ntohf.o:        ntohf.h

Queue.o:        Queue.h
Time.o:         Time.h

# X-window classes.
Application.o:  Application.h
Canvas.o:       Canvas.h
Cursor.o:       Cursor.h
Printer.o:      Printer.h Window.h
Window.o:       Window.h

# XLib classes
PixMap.o:       PixMap.h
XFonts.o:       XFonts.h
XPen.o:         XPen.h


# Motif dialog boxes
XmError.o:      XmError.h
XmFile.o:       XmFile.h
XmQuery.o:      XmQuery.h
XmWarn.o:       XmWarn.h

lib${LIBNAME}.a: ${OBJS}
	rm -f lib${LIBNAME}.a
	ar cr lib${LIBNAME}.a ${OBJS}

install: all
	install -p --mode=664 lib${LIBNAME}.a ${DESTDIR}/${LIBDIR}
	install -p --mode=444 *.h ${DESTDIR}/${INCLUDEDIR}/raf

include:
	install -c -m 0444 ${LIBNAME}.h ${DESTDIR}/${INCLUDEDIR}

clean:
	rm -f *.o *.a *.ln
