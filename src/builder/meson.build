_i = [include_directories('.'), inc_dirs]

_f = [
    'builder.cpp'
]

_l = library('builder',
    files(_f),
    include_directories: _i
)

builder_dep = declare_dependency(
	include_directories: _i,
	link_with: _l
)
