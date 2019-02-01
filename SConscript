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
pms_specs.c
portable.c
raf_queue.c
strupr.c
util.c
validate.cc
xml.cc
oap.cc
OAProbeFactory.cc
OAPUserConfig.cc
Particle.cc
Probe.cc
PMS2D.cc
Fast2D.cc
CIP.cc
TwoDS.cc
HVPS.cc
""")

includes = Split("""
ACconfig.h Application.h CIP.h Canvas.h Cursor.h Fast2D.h HVPS.h OAProbeFactory.h
OAPUserConfig.h PMS2D.h PMSspex.h Particle.h PixMap.h PostScript.h Printer.h
Probe.h Queue.h SQLrt.h TextWindow.h TwoDS.h Window.h XFonts.h XPen.h XmError.h
XmFile.h OAP.h XmQuery.h XmWarn.h ac.h adsIO.h adsIOrt.h constants.h hdrAPI.h
header.h libraf.h pgsql.h pms.h portable.h raf.h rafTime.h raf_queue.h tapeIO.h
""")

# No mtio.h on macosx.
if env['PLATFORM'] != 'darwin':
  sources.append(['tapeIO.c', 'tapeIO++.cc'])

libraf = env.StaticLibrary('raf' , sources)
env.Default(libraf)
env.Install("$INSTALL_PREFIX/lib", libraf)
env.Install("$INSTALL_PREFIX/include/raf", includes)
il = env.Alias('install-lib', "$INSTALL_PREFIX/lib")
ii = env.Alias('install-inc', "$INSTALL_PREFIX/include/raf")
env.Alias('install', [il, ii])

def raf(env):
    env.AppendLibrary('raf')
    env.Append(CPPPATH=env.Dir('..'))

Export('raf')
