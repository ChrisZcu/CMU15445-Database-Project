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
CMAKE_SOURCE_DIR = /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build

# Include any dependencies generated for this target.
include src/recovery/CMakeFiles/bustub_recovery.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/recovery/CMakeFiles/bustub_recovery.dir/compiler_depend.make

# Include the progress variables for this target.
include src/recovery/CMakeFiles/bustub_recovery.dir/progress.make

# Include the compile flags for this target's objects.
include src/recovery/CMakeFiles/bustub_recovery.dir/flags.make

src/recovery/CMakeFiles/bustub_recovery.dir/checkpoint_manager.cpp.o: src/recovery/CMakeFiles/bustub_recovery.dir/flags.make
src/recovery/CMakeFiles/bustub_recovery.dir/checkpoint_manager.cpp.o: /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/src/recovery/checkpoint_manager.cpp
src/recovery/CMakeFiles/bustub_recovery.dir/checkpoint_manager.cpp.o: src/recovery/CMakeFiles/bustub_recovery.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/recovery/CMakeFiles/bustub_recovery.dir/checkpoint_manager.cpp.o"
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/recovery && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/recovery/CMakeFiles/bustub_recovery.dir/checkpoint_manager.cpp.o -MF CMakeFiles/bustub_recovery.dir/checkpoint_manager.cpp.o.d -o CMakeFiles/bustub_recovery.dir/checkpoint_manager.cpp.o -c /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/src/recovery/checkpoint_manager.cpp

src/recovery/CMakeFiles/bustub_recovery.dir/checkpoint_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bustub_recovery.dir/checkpoint_manager.cpp.i"
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/recovery && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/src/recovery/checkpoint_manager.cpp > CMakeFiles/bustub_recovery.dir/checkpoint_manager.cpp.i

src/recovery/CMakeFiles/bustub_recovery.dir/checkpoint_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bustub_recovery.dir/checkpoint_manager.cpp.s"
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/recovery && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/src/recovery/checkpoint_manager.cpp -o CMakeFiles/bustub_recovery.dir/checkpoint_manager.cpp.s

src/recovery/CMakeFiles/bustub_recovery.dir/log_manager.cpp.o: src/recovery/CMakeFiles/bustub_recovery.dir/flags.make
src/recovery/CMakeFiles/bustub_recovery.dir/log_manager.cpp.o: /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/src/recovery/log_manager.cpp
src/recovery/CMakeFiles/bustub_recovery.dir/log_manager.cpp.o: src/recovery/CMakeFiles/bustub_recovery.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/recovery/CMakeFiles/bustub_recovery.dir/log_manager.cpp.o"
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/recovery && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/recovery/CMakeFiles/bustub_recovery.dir/log_manager.cpp.o -MF CMakeFiles/bustub_recovery.dir/log_manager.cpp.o.d -o CMakeFiles/bustub_recovery.dir/log_manager.cpp.o -c /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/src/recovery/log_manager.cpp

src/recovery/CMakeFiles/bustub_recovery.dir/log_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bustub_recovery.dir/log_manager.cpp.i"
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/recovery && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/src/recovery/log_manager.cpp > CMakeFiles/bustub_recovery.dir/log_manager.cpp.i

src/recovery/CMakeFiles/bustub_recovery.dir/log_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bustub_recovery.dir/log_manager.cpp.s"
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/recovery && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/src/recovery/log_manager.cpp -o CMakeFiles/bustub_recovery.dir/log_manager.cpp.s

src/recovery/CMakeFiles/bustub_recovery.dir/log_recovery.cpp.o: src/recovery/CMakeFiles/bustub_recovery.dir/flags.make
src/recovery/CMakeFiles/bustub_recovery.dir/log_recovery.cpp.o: /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/src/recovery/log_recovery.cpp
src/recovery/CMakeFiles/bustub_recovery.dir/log_recovery.cpp.o: src/recovery/CMakeFiles/bustub_recovery.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/recovery/CMakeFiles/bustub_recovery.dir/log_recovery.cpp.o"
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/recovery && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/recovery/CMakeFiles/bustub_recovery.dir/log_recovery.cpp.o -MF CMakeFiles/bustub_recovery.dir/log_recovery.cpp.o.d -o CMakeFiles/bustub_recovery.dir/log_recovery.cpp.o -c /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/src/recovery/log_recovery.cpp

src/recovery/CMakeFiles/bustub_recovery.dir/log_recovery.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bustub_recovery.dir/log_recovery.cpp.i"
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/recovery && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/src/recovery/log_recovery.cpp > CMakeFiles/bustub_recovery.dir/log_recovery.cpp.i

src/recovery/CMakeFiles/bustub_recovery.dir/log_recovery.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bustub_recovery.dir/log_recovery.cpp.s"
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/recovery && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/src/recovery/log_recovery.cpp -o CMakeFiles/bustub_recovery.dir/log_recovery.cpp.s

bustub_recovery: src/recovery/CMakeFiles/bustub_recovery.dir/checkpoint_manager.cpp.o
bustub_recovery: src/recovery/CMakeFiles/bustub_recovery.dir/log_manager.cpp.o
bustub_recovery: src/recovery/CMakeFiles/bustub_recovery.dir/log_recovery.cpp.o
bustub_recovery: src/recovery/CMakeFiles/bustub_recovery.dir/build.make
.PHONY : bustub_recovery

# Rule to build all files generated by this target.
src/recovery/CMakeFiles/bustub_recovery.dir/build: bustub_recovery
.PHONY : src/recovery/CMakeFiles/bustub_recovery.dir/build

src/recovery/CMakeFiles/bustub_recovery.dir/clean:
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/recovery && $(CMAKE_COMMAND) -P CMakeFiles/bustub_recovery.dir/cmake_clean.cmake
.PHONY : src/recovery/CMakeFiles/bustub_recovery.dir/clean

src/recovery/CMakeFiles/bustub_recovery.dir/depend:
	cd /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/src/recovery /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/recovery /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/recovery/CMakeFiles/bustub_recovery.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/recovery/CMakeFiles/bustub_recovery.dir/depend

