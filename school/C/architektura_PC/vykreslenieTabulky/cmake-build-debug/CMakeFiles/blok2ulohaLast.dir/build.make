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
CMAKE_SOURCE_DIR = C:\Users\marma\CLionProjects\prog2\blok2ulohaLast

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\marma\CLionProjects\prog2\blok2ulohaLast\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/blok2ulohaLast.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/blok2ulohaLast.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/blok2ulohaLast.dir/flags.make

CMakeFiles/blok2ulohaLast.dir/main.c.obj: CMakeFiles/blok2ulohaLast.dir/flags.make
CMakeFiles/blok2ulohaLast.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\marma\CLionProjects\prog2\blok2ulohaLast\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/blok2ulohaLast.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\blok2ulohaLast.dir\main.c.obj   -c C:\Users\marma\CLionProjects\prog2\blok2ulohaLast\main.c

CMakeFiles/blok2ulohaLast.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/blok2ulohaLast.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\marma\CLionProjects\prog2\blok2ulohaLast\main.c > CMakeFiles\blok2ulohaLast.dir\main.c.i

CMakeFiles/blok2ulohaLast.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/blok2ulohaLast.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\marma\CLionProjects\prog2\blok2ulohaLast\main.c -o CMakeFiles\blok2ulohaLast.dir\main.c.s

# Object files for target blok2ulohaLast
blok2ulohaLast_OBJECTS = \
"CMakeFiles/blok2ulohaLast.dir/main.c.obj"

# External object files for target blok2ulohaLast
blok2ulohaLast_EXTERNAL_OBJECTS =

blok2ulohaLast.exe: CMakeFiles/blok2ulohaLast.dir/main.c.obj
blok2ulohaLast.exe: CMakeFiles/blok2ulohaLast.dir/build.make
blok2ulohaLast.exe: CMakeFiles/blok2ulohaLast.dir/linklibs.rsp
blok2ulohaLast.exe: CMakeFiles/blok2ulohaLast.dir/objects1.rsp
blok2ulohaLast.exe: CMakeFiles/blok2ulohaLast.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\marma\CLionProjects\prog2\blok2ulohaLast\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable blok2ulohaLast.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\blok2ulohaLast.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/blok2ulohaLast.dir/build: blok2ulohaLast.exe

.PHONY : CMakeFiles/blok2ulohaLast.dir/build

CMakeFiles/blok2ulohaLast.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\blok2ulohaLast.dir\cmake_clean.cmake
.PHONY : CMakeFiles/blok2ulohaLast.dir/clean

CMakeFiles/blok2ulohaLast.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\marma\CLionProjects\prog2\blok2ulohaLast C:\Users\marma\CLionProjects\prog2\blok2ulohaLast C:\Users\marma\CLionProjects\prog2\blok2ulohaLast\cmake-build-debug C:\Users\marma\CLionProjects\prog2\blok2ulohaLast\cmake-build-debug C:\Users\marma\CLionProjects\prog2\blok2ulohaLast\cmake-build-debug\CMakeFiles\blok2ulohaLast.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/blok2ulohaLast.dir/depend
