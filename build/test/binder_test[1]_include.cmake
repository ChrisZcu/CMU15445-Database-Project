if(EXISTS "/Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/test/binder_test[1]_tests.cmake")
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/test/binder_test[1]_tests.cmake")
else()
  add_test(binder_test_NOT_BUILT binder_test_NOT_BUILT)
endif()
