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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\DELL\Documents\ACM\OJOnly

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\DELL\Documents\ACM\OJOnly\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/OJOnly.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OJOnly.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OJOnly.dir/flags.make

CMakeFiles/OJOnly.dir/main.cpp.obj: CMakeFiles/OJOnly.dir/flags.make
CMakeFiles/OJOnly.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\DELL\Documents\ACM\OJOnly\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OJOnly.dir/main.cpp.obj"
	D:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\OJOnly.dir\main.cpp.obj -c C:\Users\DELL\Documents\ACM\OJOnly\main.cpp

CMakeFiles/OJOnly.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OJOnly.dir/main.cpp.i"
	D:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\DELL\Documents\ACM\OJOnly\main.cpp > CMakeFiles\OJOnly.dir\main.cpp.i

CMakeFiles/OJOnly.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OJOnly.dir/main.cpp.s"
	D:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\DELL\Documents\ACM\OJOnly\main.cpp -o CMakeFiles\OJOnly.dir\main.cpp.s

# Object files for target OJOnly
OJOnly_OBJECTS = \
"CMakeFiles/OJOnly.dir/main.cpp.obj"

# External object files for target OJOnly
OJOnly_EXTERNAL_OBJECTS =

OJOnly.exe: CMakeFiles/OJOnly.dir/main.cpp.obj
OJOnly.exe: CMakeFiles/OJOnly.dir/build.make
OJOnly.exe: CMakeFiles/OJOnly.dir/linklibs.rsp
OJOnly.exe: CMakeFiles/OJOnly.dir/objects1.rsp
OJOnly.exe: CMakeFiles/OJOnly.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\DELL\Documents\ACM\OJOnly\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable OJOnly.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\OJOnly.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OJOnly.dir/build: OJOnly.exe

.PHONY : CMakeFiles/OJOnly.dir/build

CMakeFiles/OJOnly.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\OJOnly.dir\cmake_clean.cmake
.PHONY : CMakeFiles/OJOnly.dir/clean

CMakeFiles/OJOnly.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\DELL\Documents\ACM\OJOnly C:\Users\DELL\Documents\ACM\OJOnly C:\Users\DELL\Documents\ACM\OJOnly\cmake-build-debug C:\Users\DELL\Documents\ACM\OJOnly\cmake-build-debug C:\Users\DELL\Documents\ACM\OJOnly\cmake-build-debug\CMakeFiles\OJOnly.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OJOnly.dir/depend
