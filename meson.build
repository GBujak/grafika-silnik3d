project('grafika-silnik3d', 'cpp',
    version: '0.0.1',
    license: 'GPLv3',
    default_options: ['cpp_std=c++17'])

glfw_dependency = dependency('glfw3')
glew_dependency = dependency('glew')

incdir = include_directories('include')

subdir('src')

executable('grafika-silnik3d', src_files,
    include_directories: incdir,
    dependencies: [glfw_dependency, glew_dependency]
    )
