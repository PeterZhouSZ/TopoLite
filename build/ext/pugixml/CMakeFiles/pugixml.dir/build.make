# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.15.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.15.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ziqwang/Documents/GitHub/TopoLite

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ziqwang/Documents/GitHub/TopoLite/build

# Include any dependencies generated for this target.
include ext/pugixml/CMakeFiles/pugixml.dir/depend.make

# Include the progress variables for this target.
include ext/pugixml/CMakeFiles/pugixml.dir/progress.make

# Include the compile flags for this target's objects.
include ext/pugixml/CMakeFiles/pugixml.dir/flags.make

ext/pugixml/CMakeFiles/pugixml.dir/src/pugixml.cpp.o: ext/pugixml/CMakeFiles/pugixml.dir/flags.make
ext/pugixml/CMakeFiles/pugixml.dir/src/pugixml.cpp.o: ../ext/pugixml/src/pugixml.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ziqwang/Documents/GitHub/TopoLite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ext/pugixml/CMakeFiles/pugixml.dir/src/pugixml.cpp.o"
	cd /Users/ziqwang/Documents/GitHub/TopoLite/build/ext/pugixml && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pugixml.dir/src/pugixml.cpp.o -c /Users/ziqwang/Documents/GitHub/TopoLite/ext/pugixml/src/pugixml.cpp

ext/pugixml/CMakeFiles/pugixml.dir/src/pugixml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pugixml.dir/src/pugixml.cpp.i"
	cd /Users/ziqwang/Documents/GitHub/TopoLite/build/ext/pugixml && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ziqwang/Documents/GitHub/TopoLite/ext/pugixml/src/pugixml.cpp > CMakeFiles/pugixml.dir/src/pugixml.cpp.i

ext/pugixml/CMakeFiles/pugixml.dir/src/pugixml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pugixml.dir/src/pugixml.cpp.s"
	cd /Users/ziqwang/Documents/GitHub/TopoLite/build/ext/pugixml && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ziqwang/Documents/GitHub/TopoLite/ext/pugixml/src/pugixml.cpp -o CMakeFiles/pugixml.dir/src/pugixml.cpp.s

# Object files for target pugixml
pugixml_OBJECTS = \
"CMakeFiles/pugixml.dir/src/pugixml.cpp.o"

# External object files for target pugixml
pugixml_EXTERNAL_OBJECTS =

ext/pugixml/libpugixml.a: ext/pugixml/CMakeFiles/pugixml.dir/src/pugixml.cpp.o
ext/pugixml/libpugixml.a: ext/pugixml/CMakeFiles/pugixml.dir/build.make
ext/pugixml/libpugixml.a: ext/pugixml/CMakeFiles/pugixml.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ziqwang/Documents/GitHub/TopoLite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libpugixml.a"
	cd /Users/ziqwang/Documents/GitHub/TopoLite/build/ext/pugixml && $(CMAKE_COMMAND) -P CMakeFiles/pugixml.dir/cmake_clean_target.cmake
	cd /Users/ziqwang/Documents/GitHub/TopoLite/build/ext/pugixml && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pugixml.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ext/pugixml/CMakeFiles/pugixml.dir/build: ext/pugixml/libpugixml.a

.PHONY : ext/pugixml/CMakeFiles/pugixml.dir/build

ext/pugixml/CMakeFiles/pugixml.dir/clean:
	cd /Users/ziqwang/Documents/GitHub/TopoLite/build/ext/pugixml && $(CMAKE_COMMAND) -P CMakeFiles/pugixml.dir/cmake_clean.cmake
.PHONY : ext/pugixml/CMakeFiles/pugixml.dir/clean

ext/pugixml/CMakeFiles/pugixml.dir/depend:
	cd /Users/ziqwang/Documents/GitHub/TopoLite/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ziqwang/Documents/GitHub/TopoLite /Users/ziqwang/Documents/GitHub/TopoLite/ext/pugixml /Users/ziqwang/Documents/GitHub/TopoLite/build /Users/ziqwang/Documents/GitHub/TopoLite/build/ext/pugixml /Users/ziqwang/Documents/GitHub/TopoLite/build/ext/pugixml/CMakeFiles/pugixml.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ext/pugixml/CMakeFiles/pugixml.dir/depend

