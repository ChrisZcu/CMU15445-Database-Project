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

# Include any dependencies generated for this target.
include tools/sqllogictest/CMakeFiles/sqllogictest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tools/sqllogictest/CMakeFiles/sqllogictest.dir/compiler_depend.make

# Include the progress variables for this target.
include tools/sqllogictest/CMakeFiles/sqllogictest.dir/progress.make

# Include the compile flags for this target's objects.
include tools/sqllogictest/CMakeFiles/sqllogictest.dir/flags.make

tools/sqllogictest/CMakeFiles/sqllogictest.dir/sqllogictest.cpp.o: tools/sqllogictest/CMakeFiles/sqllogictest.dir/flags.make
tools/sqllogictest/CMakeFiles/sqllogictest.dir/sqllogictest.cpp.o: /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/tools/sqllogictest/sqllogictest.cpp
tools/sqllogictest/CMakeFiles/sqllogictest.dir/sqllogictest.cpp.o: tools/sqllogictest/CMakeFiles/sqllogictest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tools/sqllogictest/CMakeFiles/sqllogictest.dir/sqllogictest.cpp.o"
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/tools/sqllogictest && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tools/sqllogictest/CMakeFiles/sqllogictest.dir/sqllogictest.cpp.o -MF CMakeFiles/sqllogictest.dir/sqllogictest.cpp.o.d -o CMakeFiles/sqllogictest.dir/sqllogictest.cpp.o -c /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/tools/sqllogictest/sqllogictest.cpp

tools/sqllogictest/CMakeFiles/sqllogictest.dir/sqllogictest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sqllogictest.dir/sqllogictest.cpp.i"
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/tools/sqllogictest && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/tools/sqllogictest/sqllogictest.cpp > CMakeFiles/sqllogictest.dir/sqllogictest.cpp.i

tools/sqllogictest/CMakeFiles/sqllogictest.dir/sqllogictest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sqllogictest.dir/sqllogictest.cpp.s"
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/tools/sqllogictest && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/tools/sqllogictest/sqllogictest.cpp -o CMakeFiles/sqllogictest.dir/sqllogictest.cpp.s

tools/sqllogictest/CMakeFiles/sqllogictest.dir/parser.cpp.o: tools/sqllogictest/CMakeFiles/sqllogictest.dir/flags.make
tools/sqllogictest/CMakeFiles/sqllogictest.dir/parser.cpp.o: /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/tools/sqllogictest/parser.cpp
tools/sqllogictest/CMakeFiles/sqllogictest.dir/parser.cpp.o: tools/sqllogictest/CMakeFiles/sqllogictest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tools/sqllogictest/CMakeFiles/sqllogictest.dir/parser.cpp.o"
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/tools/sqllogictest && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tools/sqllogictest/CMakeFiles/sqllogictest.dir/parser.cpp.o -MF CMakeFiles/sqllogictest.dir/parser.cpp.o.d -o CMakeFiles/sqllogictest.dir/parser.cpp.o -c /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/tools/sqllogictest/parser.cpp

tools/sqllogictest/CMakeFiles/sqllogictest.dir/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sqllogictest.dir/parser.cpp.i"
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/tools/sqllogictest && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/tools/sqllogictest/parser.cpp > CMakeFiles/sqllogictest.dir/parser.cpp.i

tools/sqllogictest/CMakeFiles/sqllogictest.dir/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sqllogictest.dir/parser.cpp.s"
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/tools/sqllogictest && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/tools/sqllogictest/parser.cpp -o CMakeFiles/sqllogictest.dir/parser.cpp.s

# Object files for target sqllogictest
sqllogictest_OBJECTS = \
"CMakeFiles/sqllogictest.dir/sqllogictest.cpp.o" \
"CMakeFiles/sqllogictest.dir/parser.cpp.o"

# External object files for target sqllogictest
sqllogictest_EXTERNAL_OBJECTS =

bin/bustub-sqllogictest: tools/sqllogictest/CMakeFiles/sqllogictest.dir/sqllogictest.cpp.o
bin/bustub-sqllogictest: tools/sqllogictest/CMakeFiles/sqllogictest.dir/parser.cpp.o
bin/bustub-sqllogictest: tools/sqllogictest/CMakeFiles/sqllogictest.dir/build.make
bin/bustub-sqllogictest: lib/libbustub.a
bin/bustub-sqllogictest: lib/libbustub_murmur3.a
bin/bustub-sqllogictest: lib/libduckdb_pg_query.a
bin/bustub-sqllogictest: lib/libfmtd.a
bin/bustub-sqllogictest: lib/libfort.a
bin/bustub-sqllogictest: tools/sqllogictest/CMakeFiles/sqllogictest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../../bin/bustub-sqllogictest"
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/tools/sqllogictest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sqllogictest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/sqllogictest/CMakeFiles/sqllogictest.dir/build: bin/bustub-sqllogictest
.PHONY : tools/sqllogictest/CMakeFiles/sqllogictest.dir/build

tools/sqllogictest/CMakeFiles/sqllogictest.dir/clean:
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/tools/sqllogictest && $(CMAKE_COMMAND) -P CMakeFiles/sqllogictest.dir/cmake_clean.cmake
.PHONY : tools/sqllogictest/CMakeFiles/sqllogictest.dir/clean

tools/sqllogictest/CMakeFiles/sqllogictest.dir/depend:
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/tools/sqllogictest /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/tools/sqllogictest /Users/teechris/Desktop/SUSTech/CMU15445Project/bustub/build/tools/sqllogictest/CMakeFiles/sqllogictest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/sqllogictest/CMakeFiles/sqllogictest.dir/depend

