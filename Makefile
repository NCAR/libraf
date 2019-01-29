#
# Outside users, you may remove cio.c if they don't compile.
#
DESTDIR=
LIBDIR=		${JLOCAL}/lib
MANDIR=		${JLOCAL}/man/man3
INCLUDEDIR=	${JLOCAL}/include

LIBNAME=	raf

DEFINES=	-DPNG

CC=	gcc
CXX=	g++

# Linux
CFLAGS=		-Wall -g -O2 -Wno-write-strings -Wstrict-aliasing
CXXFLAGS=	-Wall -g -O2 -Wno-write-strings -Wstrict-aliasing ${DEFINES}
NCH_DEP=	/usr/include/netcdf.h

# macosx
# mtio.h does not exist on Mac, comment out two tapeIO files below.
#CFLAGS=		-Wall -g -O2 -Wno-write-strings -Wstrict-aliasing -I/opt/X11/include
#CXXFLAGS=	-Wall -g -O2 -Wno-write-strings -Wstrict-aliasing ${DEFINES} -I/opt/X11/include
#NCH_DEP=	/usr/local/include/netcdf.h

OBJS=	chost.o strupr.o getmem.o Xerror.o Xquery.o Xfile.o Xwarn.o \
	raf_queue.o date.o portable.o ac.o get_ac_name.o util.o \
	nc_time.o ACconfig.o adsIO.o adsIOrt.o Application.o Canvas.o Cursor.o\
        hdrAPI.o gettext.o PixMap.o PMSspex.o PostScript.o xml.o \
	oap.o Particle.o Probe.o PMS2D.o Fast2D.o TwoDS.o CIP.o HVPS.o \
        Printer.o Queue.o TextWindow.o rafTime.o validate.o pms_specs.o\
        Window.o XFonts.o XPen.o XmError.o XmFile.o XmQuery.o XmWarn.o \
	tapeIO.o tapeIO++.o

# cio.o flote.o sendhc.o sendpr.o 

SRCS=	chost.c strupr.c getmem.c Xerror.c Xquery.c Xfile.c Xwarn.c \
	raf_queue.c date.c portable.c ac.c get_ac_name.c util.c \
	nc_time.c ACconfig.cc adsIO.cc adsIOrt.cc Application.cc Canvas.cc Cursor.cc\
        hdrAPI.cc gettext.cc PixMap.cc PMSspex.cc PostScript.cc xml.cc \
	oap.cc Particle.cc Probe.cc PMS2D.cc Fast2D.cc TwoDS.cc CIP.cc HVPS.cc \
        Printer.cc Queue.cc TextWindow.cc rafTime.cc validate.cc pms_specs.c\
        Window.cc XFonts.cc XPen.cc XmError.cc XmFile.cc XmQuery.cc XmWarn.cc \
	tapeIO.c tapeIO++.c

# cio.c flote.f sendhc.f sendpr.f 

HDRS=	ac.h


all: lib${LIBNAME}.a

ac.o: ac.h
nc_time.o: ${NCH_DEP}

# IO classes.
hdrAPI.o:	hdrAPI.h portable.h
adsIO.o:	adsIO.h hdrAPI.h
adsIOrt.o:	adsIOrt.h hdrAPI.h
PMSspex.o:	PMSspex.h
portable.o:	portable.h

Queue.o:	Queue.h
PostScript.o:	PostScript.h
rafTime.o:	rafTime.h

# OAP Classes
oap.o:		OAP.h portable.h
Particle.o:	Particle.h
Probe.o:	Probe.h hdrAPI.h OAPUserConfig.h
PMS2D.o:	PMS2D.h Probe.h OAPUserConfig.h
Fast2D.o:	Fast2D.h Probe.h OAPUserConfig.h
TwoDS.o:	TwoDS.h Probe.h OAPUserConfig.h
CIP.o:		CIP.h Probe.h OAPUserConfig.h
HVPS.o:		HVPS.h Probe.h OAPUserConfig.h

# X-window classes.
Application.o:	Application.h
Canvas.o:	Canvas.h
Cursor.o:	Cursor.h
Printer.o:	Printer.h Window.h
TextWindow.o:	TextWindow.h
Window.o:	Window.h

# XLib classes
PixMap.o:	PixMap.h
XFonts.o:	XFonts.h
XPen.o:		XPen.h


# Motif dialog boxes
XmError.o:	XmError.h
XmFile.o:	XmFile.h
XmQuery.o:	XmQuery.h
XmWarn.o:	XmWarn.h

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
