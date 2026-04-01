project(
  '4jcraft',
  ['cpp', 'c'],
  version: '0.1.0',
  meson_version: '>= 1.7',
  default_options: [
    'cpp_std=c++23',
    'warning_level=0',
    'buildtype=debug', # for now
    'unity=on', # merge source files per target
    'unity_size=8', # TODO: mess around with this
    'b_pch=true', # precompiled headers
  ],
)

if get_option('assets_mode')
  full_build = false
else
  full_build = true
endif

pymod = import('python')
python = pymod.find_installation('python3', required: true)

cc = meson.get_compiler('cpp')

use_gles = get_option('renderer') == 'gles'

global_cpp_defs = [
  '-DSPLIT_SAVES',
  '-D_LARGE_WORLDS',
  '-D_EXTENDED_ACHIEVEMENTS',
  '-D_DEBUG_MENUS_ENABLED',
  '-D_DEBUG',
  '-DDEBUG',
]

if host_machine.system() == 'linux'
  global_cpp_defs += ['-Dlinux', '-D__linux', '-D__linux__']
endif

if use_gles
  global_cpp_defs += ['-DGLES']
endif

add_project_arguments(global_cpp_defs, language: ['cpp', 'c'])

global_cpp_args = [
  '-fpermissive',
  '-Wshift-count-overflow',
  '-pipe',
]
add_project_arguments(global_cpp_args, language: 'cpp')

sdl2_dep = dependency('sdl2', required: full_build)
thread_dep = dependency('threads', required: full_build)

if full_build
  dl_dep = cc.find_library('dl', required: true)
endif

# GLES vs Desktop GL
if use_gles
  gl_dep = dependency('glesv2', required: full_build)
  glu_dep = dependency('', required: false)
else
  gl_dep = dependency('gl', required: full_build)
  glu_dep = dependency('glu', required: full_build)
endif

stb = subproject('stb').get_variable('stb_inc')
stb_dep = declare_dependency(include_directories: stb)

miniaudio_dep = dependency('miniaudio', required: full_build)

if full_build
  subdir('4J.Render')
  subdir('4J.Input')
  subdir('4J.Profile')
  subdir('4J.Storage')
endif

subdir('Minecraft.Assets')

if full_build
  subdir('Minecraft.World')
  subdir('Minecraft.Client')
endif
