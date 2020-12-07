project('grafika-silnik3d', 'cpp',
    version: '0.0.1',
    license: 'GPLv3',
    default_options: ['cpp_std=c++17'])

sdl2_dependency = dependency('sdl2')
glew_dependency = dependency('glew')

incdir = include_directories('include')

subdir('src')

executable('grafika-silnik3d', src_files,
    include_directories: incdir,
    dependencies: [sdl2_dependency, glew_dependency]
    )