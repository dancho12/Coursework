# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Project\Coursework

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Project\Coursework\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Coursework.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Coursework.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Coursework.dir/flags.make

CMakeFiles/Coursework.dir/main.c.obj: CMakeFiles/Coursework.dir/flags.make
CMakeFiles/Coursework.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Project\Coursework\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Coursework.dir/main.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Coursework.dir\main.c.obj   -c C:\Project\Coursework\main.c

CMakeFiles/Coursework.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Coursework.dir/main.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Project\Coursework\main.c > CMakeFiles\Coursework.dir\main.c.i

CMakeFiles/Coursework.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Coursework.dir/main.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Project\Coursework\main.c -o CMakeFiles\Coursework.dir\main.c.s

# Object files for target Coursework
Coursework_OBJECTS = \
"CMakeFiles/Coursework.dir/main.c.obj"

# External object files for target Coursework
Coursework_EXTERNAL_OBJECTS =

Coursework.exe: CMakeFiles/Coursework.dir/main.c.obj
Coursework.exe: CMakeFiles/Coursework.dir/build.make
Coursework.exe: CMakeFiles/Coursework.dir/linklibs.rsp
Coursework.exe: CMakeFiles/Coursework.dir/objects1.rsp
Coursework.exe: CMakeFiles/Coursework.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Project\Coursework\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Coursework.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Coursework.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Coursework.dir/build: Coursework.exe

.PHONY : CMakeFiles/Coursework.dir/build

CMakeFiles/Coursework.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Coursework.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Coursework.dir/clean

CMakeFiles/Coursework.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Project\Coursework C:\Project\Coursework C:\Project\Coursework\cmake-build-debug C:\Project\Coursework\cmake-build-debug C:\Project\Coursework\cmake-build-debug\CMakeFiles\Coursework.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Coursework.dir/depend

