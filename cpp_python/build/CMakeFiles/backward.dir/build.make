# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.12.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.12.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/d/Documents/semi/program/cpp_python

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/d/Documents/semi/program/cpp_python/build

# Include any dependencies generated for this target.
include CMakeFiles/backward.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/backward.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/backward.dir/flags.make

CMakeFiles/backward.dir/backward.cpp.o: CMakeFiles/backward.dir/flags.make
CMakeFiles/backward.dir/backward.cpp.o: ../backward.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/d/Documents/semi/program/cpp_python/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/backward.dir/backward.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/backward.dir/backward.cpp.o -c /Users/d/Documents/semi/program/cpp_python/backward.cpp

CMakeFiles/backward.dir/backward.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/backward.dir/backward.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/d/Documents/semi/program/cpp_python/backward.cpp > CMakeFiles/backward.dir/backward.cpp.i

CMakeFiles/backward.dir/backward.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/backward.dir/backward.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/d/Documents/semi/program/cpp_python/backward.cpp -o CMakeFiles/backward.dir/backward.cpp.s

# Object files for target backward
backward_OBJECTS = \
"CMakeFiles/backward.dir/backward.cpp.o"

# External object files for target backward
backward_EXTERNAL_OBJECTS =

backward.cpython-36m-darwin.so: CMakeFiles/backward.dir/backward.cpp.o
backward.cpython-36m-darwin.so: CMakeFiles/backward.dir/build.make
backward.cpython-36m-darwin.so: CMakeFiles/backward.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/d/Documents/semi/program/cpp_python/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library backward.cpython-36m-darwin.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/backward.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/backward.dir/build: backward.cpython-36m-darwin.so

.PHONY : CMakeFiles/backward.dir/build

CMakeFiles/backward.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/backward.dir/cmake_clean.cmake
.PHONY : CMakeFiles/backward.dir/clean

CMakeFiles/backward.dir/depend:
	cd /Users/d/Documents/semi/program/cpp_python/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/d/Documents/semi/program/cpp_python /Users/d/Documents/semi/program/cpp_python /Users/d/Documents/semi/program/cpp_python/build /Users/d/Documents/semi/program/cpp_python/build /Users/d/Documents/semi/program/cpp_python/build/CMakeFiles/backward.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/backward.dir/depend

