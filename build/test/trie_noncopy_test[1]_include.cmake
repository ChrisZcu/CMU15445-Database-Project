if(EXISTS "/Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/test/trie_noncopy_test[1]_tests.cmake")
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/test/trie_noncopy_test[1]_tests.cmake")
else()
  add_test(trie_noncopy_test_NOT_BUILT trie_noncopy_test_NOT_BUILT)
endif()
