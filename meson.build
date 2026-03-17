project('4jcraft-chucklegrounds', ['cpp', 'c'],
  version : '0.1.0',
  meson_version: '>= 1.1',
  default_options : [
    'cpp_std=c++23',
    'warning_level=0',
    'buildtype=debug', # for now
    'unity=on', # merge source files per target
    'unity_size=8', # TODO: mess around with this
    'b_pch=true', # precompiled headers
  ],
)

cmake = import('cmake')
pymod = import('python')
python = pymod.find_installation('python3', required: true)

cc = meson.get_compiler('cpp')

is_emscripten = host_machine.system() == 'emscripten'

# system deps
if is_emscripten
    # These are handled in Emscripten via -sUSE_<whatever> (except GL4ES)
    glu_dep = declare_dependency()
    sdl2_dep = declare_dependency()
    thread_dep = declare_dependency()
    zlib_dep   = declare_dependency()

    # GL4ES stuff
    gl4es_opt = cmake.subproject_options()
    gl4es_opt.add_cmake_defines({'STATICLIB': true, 'NOX11': true, 'NOEGL': true})
    gl4es_opt.set_override_option('unity', 'off')

    gl4es_proj = cmake.subproject('gl4es', options: gl4es_opt)
    gl_dep = gl4es_proj.dependency('GL')
else
    gl_dep  = dependency('gl')
    glu_dep = dependency('glu')
    sdl2_dep   = dependency('sdl2') # Yes.. i know sdl3 is out, but there's not point upgrading right now except when
                                # someone is gonna ask me "Hey juicey can you make it SDL3?" and i'd be like fuck you and still do it.
    thread_dep = dependency('threads')
    zlib_dep = dependency('zlib')
endif

# compile flags (chagne ts juicey)
global_cpp_args = [
  '-fpermissive',
  '-Wshift-count-overflow',
  '-pipe',             # use pipes instead of temp files between compiler stages
]

# global ccp defs type shi
global_cpp_defs = [
  '-DSPLIT_SAVES',
  '-D_LARGE_WORLDS',
  '-D_EXTENDED_ACHIEVEMENTS',
  '-D_DEBUG_MENUS_ENABLED',
  '-D_DEBUG',
  '-DDEBUG',
]

if is_emscripten
  common_args = [
    '--use-port=zlib',
    '--use-port=sdl2',
  ]

  add_project_arguments(
    '-pthread',
    common_args,
    language: 'cpp'
  )

  add_project_link_arguments(
    '-sFULL_ES2=1',
    '-sALLOW_MEMORY_GROWTH=1',
    '-sPTHREAD_POOL_SIZE=4',
    '-sERROR_ON_UNDEFINED_SYMBOLS=0',
    '-sASSERTIONS=0',
    common_args,
    language: 'cpp'
  )
endif

# DecalOverdose: yes i know it's bad to do this but I don't know a better way to do this.
if host_machine.system() == 'linux' or is_emscripten
  global_cpp_defs += [
    '-Dlinux',
    '-D__linux',
    '-D__linux__',
  ]
endif

subdir('4J.Render')
subdir('4J.Input')
subdir('4J.Profile')
subdir('4J.Storage')
subdir('Minecraft.Assets')
subdir('Minecraft.World')
subdir('Minecraft.Client')
