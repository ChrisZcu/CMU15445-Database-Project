if(EXISTS "/Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/test/rwlatch_test[1]_tests.cmake")
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/test/rwlatch_test[1]_tests.cmake")
else()
  add_test(rwlatch_test_NOT_BUILT rwlatch_test_NOT_BUILT)
endif()
