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

# Utility rule file for fix-clang-tidy.

# Include any custom commands dependencies for this target.
include CMakeFiles/fix-clang-tidy.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/fix-clang-tidy.dir/progress.make

CMakeFiles/fix-clang-tidy:
	/Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build_support/run_clang_tidy.py -clang-tidy-binary CLANG_TIDY_BIN-NOTFOUND -p /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build -clang-apply-replacements-binary CLANG_APPLY_REPLACEMENTS_BIN-NOTFOUND -fix

fix-clang-tidy: CMakeFiles/fix-clang-tidy
fix-clang-tidy: CMakeFiles/fix-clang-tidy.dir/build.make
.PHONY : fix-clang-tidy

# Rule to build all files generated by this target.
CMakeFiles/fix-clang-tidy.dir/build: fix-clang-tidy
.PHONY : CMakeFiles/fix-clang-tidy.dir/build

CMakeFiles/fix-clang-tidy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fix-clang-tidy.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fix-clang-tidy.dir/clean

CMakeFiles/fix-clang-tidy.dir/depend:
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/CMakeFiles/fix-clang-tidy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fix-clang-tidy.dir/depend

