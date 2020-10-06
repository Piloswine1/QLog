project(
    'Qlog',
    'cpp', 
    license: 'GPL3',
    version: '0.0.1',
    default_options: [
        'cpp_std=c++17'
    ],
)

warnings = [      
    '-Wmisleading-indentation', # warn if indentation implies blocks where blocks do not exist
    '-Wduplicated-cond', # warn if if / else chain has duplicated conditions
    '-Wduplicated-branches', # warn if if / else branches have duplicated code
    '-Wlogical-op', # warn about logical operations being used where bitwise were probably wanted
    '-Wuseless-cast' # warn if you perform a cast to the same type
]

qchat_sources = files(
    'src/builder.cpp',
    'src/parser.cpp'
    
)

incl_dir = include_directories(
    'src'
)

subdir('tests')

executable(
    'Qlog',
    qchat_sources,
    include_directories: incl_dir,
    cpp_args: warnings
)