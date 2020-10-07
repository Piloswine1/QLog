_i = [include_directories('.'), inc_dirs]

_f = [
    'parser.cpp'
]

_l = library('parser',
    files(_f),
    include_directories: _i
)

parser_dep = declare_dependency(
	include_directories: _i,
	link_with: _l
)