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
CMAKE_SOURCE_DIR = /home/xzhuka01/proj1/ivs_project_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xzhuka01/proj1/ivs_project_1/build

# Utility rule file for pack.

# Include the progress variables for this target.
include CMakeFiles/pack.dir/progress.make

CMakeFiles/pack:
	cd /home/xzhuka01/proj1/ivs_project_1 && /usr/bin/cmake -E tar cfv xlogin00.zip --format=zip black_box_tests.cpp white_box_tests.cpp tdd_code.h tdd_code.cpp

pack: CMakeFiles/pack
pack: CMakeFiles/pack.dir/build.make

.PHONY : pack

# Rule to build all files generated by this target.
CMakeFiles/pack.dir/build: pack

.PHONY : CMakeFiles/pack.dir/build

CMakeFiles/pack.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pack.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pack.dir/clean

CMakeFiles/pack.dir/depend:
	cd /home/xzhuka01/proj1/ivs_project_1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xzhuka01/proj1/ivs_project_1 /home/xzhuka01/proj1/ivs_project_1 /home/xzhuka01/proj1/ivs_project_1/build /home/xzhuka01/proj1/ivs_project_1/build /home/xzhuka01/proj1/ivs_project_1/build/CMakeFiles/pack.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pack.dir/depend
