# -*- python -*-

Import('env')

sources = Split("""
ACconfig.cc
Application.cc
Canvas.cc
Cursor.cc
PMSspex.cc
PixMap.cc
PostScript.cc
Printer.cc
Queue.cc
TextWindow.cc
rafTime.cc
Window.cc
XFonts.cc
XPen.cc
Xerror.c
Xfile.c
XmError.cc
XmFile.cc
XmQuery.cc
XmWarn.cc
Xquery.c
Xwarn.c
ac.c
adsIO.cc
adsIOrt.cc
date.c
get_ac_name.c
getmem.c
gettext.cc
hdrAPI.cc
nc_time.c
ntohf.cc
pms_specs.c
portable.c
raf_queue.c
strupr.c
validate.cc
""")

#chost.c
#tapeIO.c
#tapeIO++.cc
#util.c

std = env.StaticLibrary('raf' , sources)
#env.Default(env.Install('#/lib/', raf))
