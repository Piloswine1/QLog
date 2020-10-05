project('Qlog',
        'cpp', 
        license: 'GPL3',
        version: '0.0.1',
        default_options: ['cpp_std=c++17'],
)

qchat_sources = files(
    'main.cpp'
)

incl_dir = include_directories(
    'src'
)

subdir('tests')

executable('Qlog',
            qchat_sources,
            include_directories: incl_dir,
            )