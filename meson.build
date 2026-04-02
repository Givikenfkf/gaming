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

pymod = import('python')
python = pymod.find_installation('python3', required: true)

cc = meson.get_compiler('cpp')

use_gles = get_option('renderer') == 'gles'

global_cpp_defs = [
  '-DSPLIT_SAVES',
  '-D_EXTENDED_ACHIEVEMENTS',
  '-D_DEBUG_MENUS_ENABLED',
  '-D_DEBUG',
  '-DDEBUG',
]

if host_machine.system() != 'emscripten'
  global_cpp_defs += '-D_LARGE_WORLDS'
endif

if host_machine.system() == 'emscripten'
  common_args = [
    '-sMEMORY64=1',
    '-pthread',
    '--use-port=zlib',
    '--use-port=sdl2',
  ]

  add_project_arguments(
    '-DMA_NO_ALSA',
    common_args,
    language: ['c', 'cpp']
  )

  add_project_link_arguments(
    '-sFULL_ES3=1',
    '-sALLOW_MEMORY_GROWTH=1',
    '-sPTHREAD_POOL_SIZE=4',
    '-sERROR_ON_UNDEFINED_SYMBOLS=0',
    '-sASSERTIONS=0',
    '-sFORCE_FILESYSTEM=1',
    '-g',
    common_args,
    language: 'cpp'
  )
endif

# DecalOverdose: yes i know it's bad to do this but I don't know a better way to do this.
if host_machine.system() == 'linux' or host_machine.system() == 'emscripten'
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

# system deps
if host_machine.system() == 'emscripten'
    # These are handled in Emscripten via -sUSE_<whatever>
  sdl2_dep = declare_dependency()
  zlib_dep = declare_dependency()
  thread_dep = declare_dependency()
  dl_dep = declare_dependency()
else
  sdl2_dep = dependency('sdl2')
  zlib_dep = dependency('zlib')
  thread_dep = dependency('threads')
  dl_dep = cc.find_library('dl', required: true)
endif

# GLES vs Desktop GL
if use_gles
  if host_machine.system() != 'emscripten'
    gl_dep = dependency('glesv2', required: true)
  else
    gl_dep = declare_dependency()
  endif

  glu_dep = dependency('', required: false)
else
  gl_dep = dependency('gl', required: true)
  glu_dep = dependency('glu', required: true)
endif

stb = subproject('stb').get_variable('stb_inc')
stb_dep = declare_dependency(include_directories: stb)

miniaudio_dep = dependency('miniaudio')

subdir('4J.Render')
subdir('4J.Input')
subdir('4J.Profile')
subdir('4J.Storage')

subdir('Minecraft.Assets')
subdir('Minecraft.World')
subdir('Minecraft.Client')
