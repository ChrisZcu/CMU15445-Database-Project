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

# Utility rule file for p0.02-function-error_test.

# Include any custom commands dependencies for this target.
include test/CMakeFiles/p0.02-function-error_test.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/p0.02-function-error_test.dir/progress.make

test/CMakeFiles/p0.02-function-error_test:
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/test && ../bin/bustub-sqllogictest /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/test/sql/p0.02-function-error.slt --verbose -d --in-memory

p0.02-function-error_test: test/CMakeFiles/p0.02-function-error_test
p0.02-function-error_test: test/CMakeFiles/p0.02-function-error_test.dir/build.make
.PHONY : p0.02-function-error_test

# Rule to build all files generated by this target.
test/CMakeFiles/p0.02-function-error_test.dir/build: p0.02-function-error_test
.PHONY : test/CMakeFiles/p0.02-function-error_test.dir/build

test/CMakeFiles/p0.02-function-error_test.dir/clean:
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/test && $(CMAKE_COMMAND) -P CMakeFiles/p0.02-function-error_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/p0.02-function-error_test.dir/clean

test/CMakeFiles/p0.02-function-error_test.dir/depend:
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/test /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/test /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/test/CMakeFiles/p0.02-function-error_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/p0.02-function-error_test.dir/depend

