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

# Utility rule file for submit-p1.

# Include any custom commands dependencies for this target.
include CMakeFiles/submit-p1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/submit-p1.dir/progress.make

CMakeFiles/submit-p1:
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub && zip project1-submission.zip src/include/storage/page/page_guard.h src/storage/page/page_guard.cpp src/include/buffer/lru_k_replacer.h src/buffer/lru_k_replacer.cpp src/include/buffer/buffer_pool_manager.h src/buffer/buffer_pool_manager.cpp

submit-p1: CMakeFiles/submit-p1
submit-p1: CMakeFiles/submit-p1.dir/build.make
.PHONY : submit-p1

# Rule to build all files generated by this target.
CMakeFiles/submit-p1.dir/build: submit-p1
.PHONY : CMakeFiles/submit-p1.dir/build

CMakeFiles/submit-p1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/submit-p1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/submit-p1.dir/clean

CMakeFiles/submit-p1.dir/depend:
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/CMakeFiles/submit-p1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/submit-p1.dir/depend

