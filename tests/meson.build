gtest_dep = dependency('gtest', main : true, required : false)

test_parser = executable(
	'test_parser', 
	sources: 'test_parser.cpp', 
	dependencies: [gtest_dep, parser_dep]
)
test('parser_related_tests', test_parser, protocol: 'gtest')

test_builder = executable(
        'test_builder',
        sources: ['test_builder.cpp'],
        dependencies: [gtest_dep, builder_dep]
)
test('builder_related_tests', test_builder, protocol: 'gtest')

