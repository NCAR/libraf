#!python

# This SConstruct wraps the raf tool file in this directory with the
# conventional --prefix option.  The raf library can be built standalone by
# executing scons here, or it can be built as part of a larger source tree.

import os
import sys

# eol_scons will be found either in the parent source tree or in the
# default system locations.
sys.path.append('../site_scons')
import eol_scons

def Raf_utils(env):
    env['INSTALL_RAF'] = install_raf
    env.Require(['prefixoptions'])


install_raf = False
if Dir('#') == Dir('.') :
  install_raf = True

env = Environment(GLOBAL_TOOLS = [Raf_utils])

SConscript('tool_raf.py')

variables = env.GlobalVariables()
variables.Update(env)
Help(variables.GenerateHelpText(env))

