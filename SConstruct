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

AddOption('--prefix',
  dest='prefix',
  type='string',
  nargs=1,
  action='store',
  metavar='DIR',
  default='#',
  help='installation prefix')

def Raf_utils(env):
    # This just enforces that the --prefix setting is the default for both
    # the OPT_PREFIX and INSTALL_PREFIX.  Both can still be overridden
    # individually if needed.
    env['DEFAULT_INSTALL_PREFIX'] = GetOption('prefix')
    env['DEFAULT_OPT_PREFIX'] = GetOption('prefix')
    env.Require(['prefixoptions'])

env = Environment(GLOBAL_TOOLS = [Raf_utils])

SConscript('tool_raf.py')

variables = env.GlobalVariables()
variables.Update(env)
Help(variables.GenerateHelpText(env))

