# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.26.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.26.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build

# Utility rule file for check-clang-tidy-p2.

# Include any custom commands dependencies for this target.
include CMakeFiles/check-clang-tidy-p2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/check-clang-tidy-p2.dir/progress.make

CMakeFiles/check-clang-tidy-p2:
	/Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build_support/run_clang_tidy.py -clang-tidy-binary CLANG_TIDY_BIN-NOTFOUND -p /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build src/include/storage/page/b_plus_tree_page.h src/storage/page/b_plus_tree_page.cpp src/include/storage/page/b_plus_tree_internal_page.h src/storage/page/b_plus_tree_internal_page.cpp src/include/storage/page/b_plus_tree_leaf_page.h src/storage/page/b_plus_tree_leaf_page.cpp src/include/storage/index/index_iterator.h src/storage/index/index_iterator.cpp src/include/storage/index/b_plus_tree.h src/storage/index/b_plus_tree.cpp src/include/storage/page/page_guard.h src/storage/page/page_guard.cpp src/include/buffer/lru_k_replacer.h src/buffer/lru_k_replacer.cpp src/include/buffer/buffer_pool_manager.h src/buffer/buffer_pool_manager.cpp

check-clang-tidy-p2: CMakeFiles/check-clang-tidy-p2
check-clang-tidy-p2: CMakeFiles/check-clang-tidy-p2.dir/build.make
.PHONY : check-clang-tidy-p2

# Rule to build all files generated by this target.
CMakeFiles/check-clang-tidy-p2.dir/build: check-clang-tidy-p2
.PHONY : CMakeFiles/check-clang-tidy-p2.dir/build

CMakeFiles/check-clang-tidy-p2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/check-clang-tidy-p2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/check-clang-tidy-p2.dir/clean

CMakeFiles/check-clang-tidy-p2.dir/depend:
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/CMakeFiles/check-clang-tidy-p2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/check-clang-tidy-p2.dir/depend

