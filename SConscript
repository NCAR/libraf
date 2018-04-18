# -*- python -*-

env = Environment(tools=['default','prefixoptions'])

env.Append(CCFLAGS='-g -Wall -Wno-write-strings')
env.Append(CPPDEFINES=['PNG'])
if env['PLATFORM'] == 'darwin':
  env.Append(CPPPATH=['/opt/X11/include'])


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
chost.c
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
util.c
validate.cc
""")

includes = Split("""
ACconfig.h     PixMap.h      TextWindow.h  XmFile.h   adsIOrt.h    ntohf.h     rafTime.h
Application.h  PostScript.h  Window.h      XmQuery.h  constants.h  pgsql.h     raf_queue.h
Canvas.h       Printer.h     XFonts.h      XmWarn.h   hdrAPI.h     pms.h       tapeIO.h
Cursor.h       Queue.h       XPen.h        ac.h       header.h     portable.h
PMSspex.h      SQLrt.h       XmError.h     adsIO.h    libraf.h     raf.h
""")

# No mtio.h on macosx.
if env['PLATFORM'] != 'darwin':
  sources.append(['tapeIO.c', 'tapeIO++.cc'])

raf = env.StaticLibrary('raf' , sources)
env.Default(raf)
env.Install("$INSTALL_PREFIX/lib", raf)
env.Install("$INSTALL_PREFIX/include/raf", includes)
il = env.Alias('install-lib', "$INSTALL_PREFIX/lib")
ii = env.Alias('install-inc', "$INSTALL_PREFIX/include/raf")
env.Alias('install', [il, ii])
