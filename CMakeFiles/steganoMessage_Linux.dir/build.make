# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_SOURCE_DIR = /home/florian/git/steganoMessage

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/florian/git/steganoMessage

# Include any dependencies generated for this target.
include CMakeFiles/steganoMessage_Linux.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/steganoMessage_Linux.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/steganoMessage_Linux.dir/flags.make

CMakeFiles/steganoMessage_Linux.dir/src/main.cpp.o: CMakeFiles/steganoMessage_Linux.dir/flags.make
CMakeFiles/steganoMessage_Linux.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/florian/git/steganoMessage/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/steganoMessage_Linux.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/steganoMessage_Linux.dir/src/main.cpp.o -c /home/florian/git/steganoMessage/src/main.cpp

CMakeFiles/steganoMessage_Linux.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/steganoMessage_Linux.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/florian/git/steganoMessage/src/main.cpp > CMakeFiles/steganoMessage_Linux.dir/src/main.cpp.i

CMakeFiles/steganoMessage_Linux.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/steganoMessage_Linux.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/florian/git/steganoMessage/src/main.cpp -o CMakeFiles/steganoMessage_Linux.dir/src/main.cpp.s

# Object files for target steganoMessage_Linux
steganoMessage_Linux_OBJECTS = \
"CMakeFiles/steganoMessage_Linux.dir/src/main.cpp.o"

# External object files for target steganoMessage_Linux
steganoMessage_Linux_EXTERNAL_OBJECTS =

steganoMessage_Linux: CMakeFiles/steganoMessage_Linux.dir/src/main.cpp.o
steganoMessage_Linux: CMakeFiles/steganoMessage_Linux.dir/build.make
steganoMessage_Linux: lib/libsrc.a
steganoMessage_Linux: /usr/lib/libjpeg.so
steganoMessage_Linux: CMakeFiles/steganoMessage_Linux.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/florian/git/steganoMessage/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable steganoMessage_Linux"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/steganoMessage_Linux.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/steganoMessage_Linux.dir/build: steganoMessage_Linux

.PHONY : CMakeFiles/steganoMessage_Linux.dir/build

CMakeFiles/steganoMessage_Linux.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/steganoMessage_Linux.dir/cmake_clean.cmake
.PHONY : CMakeFiles/steganoMessage_Linux.dir/clean

CMakeFiles/steganoMessage_Linux.dir/depend:
	cd /home/florian/git/steganoMessage && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/florian/git/steganoMessage /home/florian/git/steganoMessage /home/florian/git/steganoMessage /home/florian/git/steganoMessage /home/florian/git/steganoMessage/CMakeFiles/steganoMessage_Linux.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/steganoMessage_Linux.dir/depend

