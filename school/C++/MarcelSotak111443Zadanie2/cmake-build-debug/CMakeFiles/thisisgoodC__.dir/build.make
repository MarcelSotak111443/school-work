# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\marma\CLionProjects\prog2\thisisgoodC++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\marma\CLionProjects\prog2\thisisgoodC++\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/thisisgoodC__.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/thisisgoodC__.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/thisisgoodC__.dir/flags.make

CMakeFiles/thisisgoodC__.dir/main.cpp.obj: CMakeFiles/thisisgoodC__.dir/flags.make
CMakeFiles/thisisgoodC__.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\marma\CLionProjects\prog2\thisisgoodC++\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/thisisgoodC__.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\thisisgoodC__.dir\main.cpp.obj -c C:\Users\marma\CLionProjects\prog2\thisisgoodC++\main.cpp

CMakeFiles/thisisgoodC__.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/thisisgoodC__.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\marma\CLionProjects\prog2\thisisgoodC++\main.cpp > CMakeFiles\thisisgoodC__.dir\main.cpp.i

CMakeFiles/thisisgoodC__.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/thisisgoodC__.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\marma\CLionProjects\prog2\thisisgoodC++\main.cpp -o CMakeFiles\thisisgoodC__.dir\main.cpp.s

# Object files for target thisisgoodC__
thisisgoodC___OBJECTS = \
"CMakeFiles/thisisgoodC__.dir/main.cpp.obj"

# External object files for target thisisgoodC__
thisisgoodC___EXTERNAL_OBJECTS =

thisisgoodC__.exe: CMakeFiles/thisisgoodC__.dir/main.cpp.obj
thisisgoodC__.exe: CMakeFiles/thisisgoodC__.dir/build.make
thisisgoodC__.exe: CMakeFiles/thisisgoodC__.dir/linklibs.rsp
thisisgoodC__.exe: CMakeFiles/thisisgoodC__.dir/objects1.rsp
thisisgoodC__.exe: CMakeFiles/thisisgoodC__.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\marma\CLionProjects\prog2\thisisgoodC++\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable thisisgoodC__.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\thisisgoodC__.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/thisisgoodC__.dir/build: thisisgoodC__.exe

.PHONY : CMakeFiles/thisisgoodC__.dir/build

CMakeFiles/thisisgoodC__.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\thisisgoodC__.dir\cmake_clean.cmake
.PHONY : CMakeFiles/thisisgoodC__.dir/clean

CMakeFiles/thisisgoodC__.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\marma\CLionProjects\prog2\thisisgoodC++ C:\Users\marma\CLionProjects\prog2\thisisgoodC++ C:\Users\marma\CLionProjects\prog2\thisisgoodC++\cmake-build-debug C:\Users\marma\CLionProjects\prog2\thisisgoodC++\cmake-build-debug C:\Users\marma\CLionProjects\prog2\thisisgoodC++\cmake-build-debug\CMakeFiles\thisisgoodC__.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/thisisgoodC__.dir/depend
