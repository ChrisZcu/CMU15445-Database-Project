if(EXISTS "/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/test/b_plus_tree_contention_test[1]_tests.cmake")
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/test/b_plus_tree_contention_test[1]_tests.cmake")
else()
  add_test(b_plus_tree_contention_test_NOT_BUILT b_plus_tree_contention_test_NOT_BUILT)
endif()
