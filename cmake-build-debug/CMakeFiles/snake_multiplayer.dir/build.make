# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/niedzwiedzwo/Desktop/clion-2017.2.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/niedzwiedzwo/Desktop/clion-2017.2.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/niedzwiedzwo/CLionProjects/snake_multiplayer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/niedzwiedzwo/CLionProjects/snake_multiplayer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/snake_multiplayer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/snake_multiplayer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/snake_multiplayer.dir/flags.make

CMakeFiles/snake_multiplayer.dir/main.cpp.o: CMakeFiles/snake_multiplayer.dir/flags.make
CMakeFiles/snake_multiplayer.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/niedzwiedzwo/CLionProjects/snake_multiplayer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/snake_multiplayer.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/snake_multiplayer.dir/main.cpp.o -c /home/niedzwiedzwo/CLionProjects/snake_multiplayer/main.cpp

CMakeFiles/snake_multiplayer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/snake_multiplayer.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/niedzwiedzwo/CLionProjects/snake_multiplayer/main.cpp > CMakeFiles/snake_multiplayer.dir/main.cpp.i

CMakeFiles/snake_multiplayer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/snake_multiplayer.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/niedzwiedzwo/CLionProjects/snake_multiplayer/main.cpp -o CMakeFiles/snake_multiplayer.dir/main.cpp.s

CMakeFiles/snake_multiplayer.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/snake_multiplayer.dir/main.cpp.o.requires

CMakeFiles/snake_multiplayer.dir/main.cpp.o.provides: CMakeFiles/snake_multiplayer.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/snake_multiplayer.dir/build.make CMakeFiles/snake_multiplayer.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/snake_multiplayer.dir/main.cpp.o.provides

CMakeFiles/snake_multiplayer.dir/main.cpp.o.provides.build: CMakeFiles/snake_multiplayer.dir/main.cpp.o


# Object files for target snake_multiplayer
snake_multiplayer_OBJECTS = \
"CMakeFiles/snake_multiplayer.dir/main.cpp.o"

# External object files for target snake_multiplayer
snake_multiplayer_EXTERNAL_OBJECTS =

snake_multiplayer: CMakeFiles/snake_multiplayer.dir/main.cpp.o
snake_multiplayer: CMakeFiles/snake_multiplayer.dir/build.make
snake_multiplayer: CMakeFiles/snake_multiplayer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/niedzwiedzwo/CLionProjects/snake_multiplayer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable snake_multiplayer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/snake_multiplayer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/snake_multiplayer.dir/build: snake_multiplayer

.PHONY : CMakeFiles/snake_multiplayer.dir/build

CMakeFiles/snake_multiplayer.dir/requires: CMakeFiles/snake_multiplayer.dir/main.cpp.o.requires

.PHONY : CMakeFiles/snake_multiplayer.dir/requires

CMakeFiles/snake_multiplayer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/snake_multiplayer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/snake_multiplayer.dir/clean

CMakeFiles/snake_multiplayer.dir/depend:
	cd /home/niedzwiedzwo/CLionProjects/snake_multiplayer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/niedzwiedzwo/CLionProjects/snake_multiplayer /home/niedzwiedzwo/CLionProjects/snake_multiplayer /home/niedzwiedzwo/CLionProjects/snake_multiplayer/cmake-build-debug /home/niedzwiedzwo/CLionProjects/snake_multiplayer/cmake-build-debug /home/niedzwiedzwo/CLionProjects/snake_multiplayer/cmake-build-debug/CMakeFiles/snake_multiplayer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/snake_multiplayer.dir/depend
