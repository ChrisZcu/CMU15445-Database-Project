if(EXISTS "/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/test/transaction_test[1]_tests.cmake")
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/test/transaction_test[1]_tests.cmake")
else()
  add_test(transaction_test_NOT_BUILT transaction_test_NOT_BUILT)
endif()
