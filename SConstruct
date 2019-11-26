#!python

# This SConstruct does nothing more than load the SConscript in this dir
# The Environment() is created in the SConstruct script
# This dir can be built standalone by executing scons here, or together
# by executing scons in a parent directory

import os
import sys
sys.path.append('../site_scons')
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
        env.Replace(DEFAULT_INSTALL_PREFIX = GetOption('prefix'))
        env.Replace(DEFAULT_OPT_PREFIX = GetOption('prefix'))
    else:
        env['DEFAULT_INSTALL_PREFIX']="#"
        env.Require(['prefixoptions'])

env = Environment(GLOBAL_TOOLS = [Raf_utils])

SConscript('SConscript')

variables = env.GlobalVariables()
variables.Update(env)
Help(variables.GenerateHelpText(env))

