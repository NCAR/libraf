# -*- python -*-

env = Environment(tools=['default','prefixoptions'])

env.Append(CCFLAGS='-g -Wall -std=c++11 -Wno-write-strings')
env.Append(CPPDEFINES=['PNG'])
if env['PLATFORM'] == 'darwin':
  env.Append(CPPPATH=['/opt/X11/include'])


sources = Split("""
ACconfig.cc
PMSspex.cc
Queue.cc
rafTime.cc
ac.c
adsIO.cc
date.c
get_ac_name.c
getmem.c
hdrAPI.cc
nc_time.c
pms_specs.c
portable.c
raf_queue.c
strupr.c
xml.cc
oap.cc
OAProbeFactory.cc
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

# No X11/Motif on Windows
if env['PLATFORM'] != 'msys':
  sources.append(['adsIOrt.cc', 'chost.c', 'Application.cc', 'Canvas.cc', 'Cursor.cc', 'gettext.cc', 'PixMap.cc', 'Printer.cc', 'PostScript.cc', 'TextWindow.cc', 'Window.cc', 'XFonts.cc', 'XPen.cc', 'Xerror.c', 'Xfile.c', 'XmError.cc', 'XmFile.cc', 'XmQuery.cc', 'XmWarn.cc', 'XmWarn.cc', 'Xquery.c', 'Xwarn.c', 'util.c', 'validate.cc'])

# No mtio.h on macosx.
if env['PLATFORM'] == 'posix':
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
