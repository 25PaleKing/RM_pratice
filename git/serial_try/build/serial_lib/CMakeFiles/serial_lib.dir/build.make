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
CMAKE_SOURCE_DIR = /home/adc/桌面/programming/door/serial_try

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adc/桌面/programming/door/serial_try/build

# Include any dependencies generated for this target.
include serial_lib/CMakeFiles/serial_lib.dir/depend.make

# Include the progress variables for this target.
include serial_lib/CMakeFiles/serial_lib.dir/progress.make

# Include the compile flags for this target's objects.
include serial_lib/CMakeFiles/serial_lib.dir/flags.make

serial_lib/CMakeFiles/serial_lib.dir/serial/serial.cpp.o: serial_lib/CMakeFiles/serial_lib.dir/flags.make
serial_lib/CMakeFiles/serial_lib.dir/serial/serial.cpp.o: ../serial_lib/serial/serial.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adc/桌面/programming/door/serial_try/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object serial_lib/CMakeFiles/serial_lib.dir/serial/serial.cpp.o"
	cd /home/adc/桌面/programming/door/serial_try/build/serial_lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/serial_lib.dir/serial/serial.cpp.o -c /home/adc/桌面/programming/door/serial_try/serial_lib/serial/serial.cpp

serial_lib/CMakeFiles/serial_lib.dir/serial/serial.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serial_lib.dir/serial/serial.cpp.i"
	cd /home/adc/桌面/programming/door/serial_try/build/serial_lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adc/桌面/programming/door/serial_try/serial_lib/serial/serial.cpp > CMakeFiles/serial_lib.dir/serial/serial.cpp.i

serial_lib/CMakeFiles/serial_lib.dir/serial/serial.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serial_lib.dir/serial/serial.cpp.s"
	cd /home/adc/桌面/programming/door/serial_try/build/serial_lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adc/桌面/programming/door/serial_try/serial_lib/serial/serial.cpp -o CMakeFiles/serial_lib.dir/serial/serial.cpp.s

# Object files for target serial_lib
serial_lib_OBJECTS = \
"CMakeFiles/serial_lib.dir/serial/serial.cpp.o"

# External object files for target serial_lib
serial_lib_EXTERNAL_OBJECTS =

serial_lib/libserial_lib.a: serial_lib/CMakeFiles/serial_lib.dir/serial/serial.cpp.o
serial_lib/libserial_lib.a: serial_lib/CMakeFiles/serial_lib.dir/build.make
serial_lib/libserial_lib.a: serial_lib/CMakeFiles/serial_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/adc/桌面/programming/door/serial_try/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libserial_lib.a"
	cd /home/adc/桌面/programming/door/serial_try/build/serial_lib && $(CMAKE_COMMAND) -P CMakeFiles/serial_lib.dir/cmake_clean_target.cmake
	cd /home/adc/桌面/programming/door/serial_try/build/serial_lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serial_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
serial_lib/CMakeFiles/serial_lib.dir/build: serial_lib/libserial_lib.a

.PHONY : serial_lib/CMakeFiles/serial_lib.dir/build

serial_lib/CMakeFiles/serial_lib.dir/clean:
	cd /home/adc/桌面/programming/door/serial_try/build/serial_lib && $(CMAKE_COMMAND) -P CMakeFiles/serial_lib.dir/cmake_clean.cmake
.PHONY : serial_lib/CMakeFiles/serial_lib.dir/clean

serial_lib/CMakeFiles/serial_lib.dir/depend:
	cd /home/adc/桌面/programming/door/serial_try/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adc/桌面/programming/door/serial_try /home/adc/桌面/programming/door/serial_try/serial_lib /home/adc/桌面/programming/door/serial_try/build /home/adc/桌面/programming/door/serial_try/build/serial_lib /home/adc/桌面/programming/door/serial_try/build/serial_lib/CMakeFiles/serial_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : serial_lib/CMakeFiles/serial_lib.dir/depend

