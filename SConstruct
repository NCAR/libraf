#!python

# This SConstruct does nothing more than load the SConscript in this dir
# The Environment() is created in the SConstruct script
# This dir can be built standalone by executing scons here, or together
# by executing scons in a parent directory

import re 
import os

# Starting with version 2.3, scons searches for the following site_scons dirs in the 
# order shown (taken from eol_scons documentation):
#    /usr/share/scons/site_scons
#    $HOME/.scons/site_scons
#    ./site_scons
# so check for these before asking user to provide path on command line
if ((not os.path.exists("/usr/share/scons/site_scons")) and
    (not os.path.exists(os.environ['HOME']+"/.scons/site_scons")) and
    (not os.path.exists("./site_scons")) and
    (not re.match(r'(.*)site_scons(.*)',str(GetOption('site_dir'))))
   ):
    print "Must include --site-dir=<path-to-site_scons> as a command line option, e.g. --site-dir=../site_scons. Exiting."
    Exit()

import eol_scons

AddOption('--prefix',
  dest='prefix',
  type='string',
  nargs=1,
  action='store',
  metavar='DIR',
  default='#',
  help='installation prefix')

def Raf_utils(env):
    if GetOption('prefix') != "#":
	env.Replace(INSTALL_PREFIX = GetOption('prefix'))
	env.Replace(OPT_PREFIX=GetOption('prefix'))
    else:
        env['DEFAULT_INSTALL_PREFIX']="#"
	env.Require(['prefixoptions'])

env = Environment(GLOBAL_TOOLS = [Raf_utils])

SConscript('SConscript')

variables = env.GlobalVariables()
variables.Update(env)
Help(variables.GenerateHelpText(env))

