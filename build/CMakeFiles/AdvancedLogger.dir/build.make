# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /data/zjs_project/learn/AdvancedLogger

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /data/zjs_project/learn/AdvancedLogger/build

# Include any dependencies generated for this target.
include CMakeFiles/AdvancedLogger.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AdvancedLogger.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AdvancedLogger.dir/flags.make

CMakeFiles/AdvancedLogger.dir/Logger.cpp.o: CMakeFiles/AdvancedLogger.dir/flags.make
CMakeFiles/AdvancedLogger.dir/Logger.cpp.o: ../Logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/zjs_project/learn/AdvancedLogger/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AdvancedLogger.dir/Logger.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AdvancedLogger.dir/Logger.cpp.o -c /data/zjs_project/learn/AdvancedLogger/Logger.cpp

CMakeFiles/AdvancedLogger.dir/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AdvancedLogger.dir/Logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/zjs_project/learn/AdvancedLogger/Logger.cpp > CMakeFiles/AdvancedLogger.dir/Logger.cpp.i

CMakeFiles/AdvancedLogger.dir/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AdvancedLogger.dir/Logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/zjs_project/learn/AdvancedLogger/Logger.cpp -o CMakeFiles/AdvancedLogger.dir/Logger.cpp.s

CMakeFiles/AdvancedLogger.dir/mian.cpp.o: CMakeFiles/AdvancedLogger.dir/flags.make
CMakeFiles/AdvancedLogger.dir/mian.cpp.o: ../mian.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/zjs_project/learn/AdvancedLogger/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/AdvancedLogger.dir/mian.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AdvancedLogger.dir/mian.cpp.o -c /data/zjs_project/learn/AdvancedLogger/mian.cpp

CMakeFiles/AdvancedLogger.dir/mian.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AdvancedLogger.dir/mian.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/zjs_project/learn/AdvancedLogger/mian.cpp > CMakeFiles/AdvancedLogger.dir/mian.cpp.i

CMakeFiles/AdvancedLogger.dir/mian.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AdvancedLogger.dir/mian.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/zjs_project/learn/AdvancedLogger/mian.cpp -o CMakeFiles/AdvancedLogger.dir/mian.cpp.s

# Object files for target AdvancedLogger
AdvancedLogger_OBJECTS = \
"CMakeFiles/AdvancedLogger.dir/Logger.cpp.o" \
"CMakeFiles/AdvancedLogger.dir/mian.cpp.o"

# External object files for target AdvancedLogger
AdvancedLogger_EXTERNAL_OBJECTS =

AdvancedLogger: CMakeFiles/AdvancedLogger.dir/Logger.cpp.o
AdvancedLogger: CMakeFiles/AdvancedLogger.dir/mian.cpp.o
AdvancedLogger: CMakeFiles/AdvancedLogger.dir/build.make
AdvancedLogger: CMakeFiles/AdvancedLogger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/data/zjs_project/learn/AdvancedLogger/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable AdvancedLogger"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AdvancedLogger.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AdvancedLogger.dir/build: AdvancedLogger

.PHONY : CMakeFiles/AdvancedLogger.dir/build

CMakeFiles/AdvancedLogger.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AdvancedLogger.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AdvancedLogger.dir/clean

CMakeFiles/AdvancedLogger.dir/depend:
	cd /data/zjs_project/learn/AdvancedLogger/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/zjs_project/learn/AdvancedLogger /data/zjs_project/learn/AdvancedLogger /data/zjs_project/learn/AdvancedLogger/build /data/zjs_project/learn/AdvancedLogger/build /data/zjs_project/learn/AdvancedLogger/build/CMakeFiles/AdvancedLogger.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AdvancedLogger.dir/depend

