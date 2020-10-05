gtest_dep = dependency('gtest', main : true, required : false)

test1 = executable('test1', sources: 'test1.cpp', dependencies: gtest_dep)
test2 = executable('test2', sources: 'test2.cpp', dependencies: gtest_dep)
test3 = executable('test3', sources: 'test3.cpp', dependencies: gtest_dep)

test('simple_assert', test1, protocol: 'gtest')
test('assert_with_header', test2, protocol: 'gtest')
test('failing', test3, protocol: 'gtest')