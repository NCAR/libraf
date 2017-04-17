# -*- python -*-

Import('PREFIX')

env = Environment()

env.Append(CCFLAGS='-g -Wall -Wno-write-strings')
env.Append(CPPDEFINES=['PNG'])


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

# No mtio.h on macosx.
if env['PLATFORM'] != 'darwin':
  sources.append(['tapeIO.c', 'tapeIO++.cc'])

raf = env.StaticLibrary('raf' , sources)
env.Default(env.Install(PREFIX+'/lib/', raf))
