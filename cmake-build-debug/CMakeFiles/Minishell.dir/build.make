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
CMAKE_COMMAND = /Users/ccarl/Desktop/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Users/ccarl/Desktop/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ccarl/Desktop/Minishell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ccarl/Desktop/Minishell/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/minishell.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/minishell.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/minishell.dir/flags.make

CMakeFiles/minishell.dir/main.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ccarl/Desktop/Minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/minishell.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minishell.dir/main.c.o   -c /Users/ccarl/Desktop/Minishell/main.c

CMakeFiles/minishell.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ccarl/Desktop/Minishell/main.c > CMakeFiles/minishell.dir/main.c.i

CMakeFiles/minishell.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ccarl/Desktop/Minishell/main.c -o CMakeFiles/minishell.dir/main.c.s

CMakeFiles/minishell.dir/GNL/get_next_line.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/GNL/get_next_line.c.o: ../GNL/get_next_line.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ccarl/Desktop/Minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/minishell.dir/GNL/get_next_line.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minishell.dir/GNL/get_next_line.c.o   -c /Users/ccarl/Desktop/Minishell/GNL/get_next_line.c

CMakeFiles/minishell.dir/GNL/get_next_line.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/GNL/get_next_line.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ccarl/Desktop/Minishell/GNL/get_next_line.c > CMakeFiles/minishell.dir/GNL/get_next_line.c.i

CMakeFiles/minishell.dir/GNL/get_next_line.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/GNL/get_next_line.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ccarl/Desktop/Minishell/GNL/get_next_line.c -o CMakeFiles/minishell.dir/GNL/get_next_line.c.s

CMakeFiles/minishell.dir/GNL/get_next_line_utils.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/GNL/get_next_line_utils.c.o: ../GNL/get_next_line_utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ccarl/Desktop/Minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/minishell.dir/GNL/get_next_line_utils.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minishell.dir/GNL/get_next_line_utils.c.o   -c /Users/ccarl/Desktop/Minishell/GNL/get_next_line_utils.c

CMakeFiles/minishell.dir/GNL/get_next_line_utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/GNL/get_next_line_utils.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ccarl/Desktop/Minishell/GNL/get_next_line_utils.c > CMakeFiles/minishell.dir/GNL/get_next_line_utils.c.i

CMakeFiles/minishell.dir/GNL/get_next_line_utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/GNL/get_next_line_utils.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ccarl/Desktop/Minishell/GNL/get_next_line_utils.c -o CMakeFiles/minishell.dir/GNL/get_next_line_utils.c.s

CMakeFiles/minishell.dir/shell_loop.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/shell_loop.c.o: ../shell_loop.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ccarl/Desktop/Minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/minishell.dir/shell_loop.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minishell.dir/shell_loop.c.o   -c /Users/ccarl/Desktop/Minishell/shell_loop.c

CMakeFiles/minishell.dir/shell_loop.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/shell_loop.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ccarl/Desktop/Minishell/shell_loop.c > CMakeFiles/minishell.dir/shell_loop.c.i

CMakeFiles/minishell.dir/shell_loop.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/shell_loop.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ccarl/Desktop/Minishell/shell_loop.c -o CMakeFiles/minishell.dir/shell_loop.c.s

CMakeFiles/minishell.dir/libft/ft_strcmp.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/libft/ft_strcmp.c.o: ../libft/ft_strcmp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ccarl/Desktop/Minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/minishell.dir/libft/ft_strcmp.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minishell.dir/libft/ft_strcmp.c.o   -c /Users/ccarl/Desktop/Minishell/libft/ft_strcmp.c

CMakeFiles/minishell.dir/libft/ft_strcmp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/libft/ft_strcmp.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ccarl/Desktop/Minishell/libft/ft_strcmp.c > CMakeFiles/minishell.dir/libft/ft_strcmp.c.i

CMakeFiles/minishell.dir/libft/ft_strcmp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/libft/ft_strcmp.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ccarl/Desktop/Minishell/libft/ft_strcmp.c -o CMakeFiles/minishell.dir/libft/ft_strcmp.c.s

CMakeFiles/minishell.dir/parser.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/parser.c.o: ../parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ccarl/Desktop/Minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/minishell.dir/parser.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minishell.dir/parser.c.o   -c /Users/ccarl/Desktop/Minishell/parser.c

CMakeFiles/minishell.dir/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/parser.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ccarl/Desktop/Minishell/parser.c > CMakeFiles/minishell.dir/parser.c.i

CMakeFiles/minishell.dir/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/parser.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ccarl/Desktop/Minishell/parser.c -o CMakeFiles/minishell.dir/parser.c.s

CMakeFiles/minishell.dir/list_utils.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/list_utils.c.o: ../list_utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ccarl/Desktop/Minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/minishell.dir/list_utils.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minishell.dir/list_utils.c.o   -c /Users/ccarl/Desktop/Minishell/list_utils.c

CMakeFiles/minishell.dir/list_utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/list_utils.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ccarl/Desktop/Minishell/list_utils.c > CMakeFiles/minishell.dir/list_utils.c.i

CMakeFiles/minishell.dir/list_utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/list_utils.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ccarl/Desktop/Minishell/list_utils.c -o CMakeFiles/minishell.dir/list_utils.c.s

CMakeFiles/minishell.dir/helper.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/helper.c.o: ../helper.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ccarl/Desktop/Minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/minishell.dir/helper.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minishell.dir/helper.c.o   -c /Users/ccarl/Desktop/Minishell/helper.c

CMakeFiles/minishell.dir/helper.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/helper.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ccarl/Desktop/Minishell/helper.c > CMakeFiles/minishell.dir/helper.c.i

CMakeFiles/minishell.dir/helper.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/helper.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ccarl/Desktop/Minishell/helper.c -o CMakeFiles/minishell.dir/helper.c.s

CMakeFiles/minishell.dir/str_utils.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/str_utils.c.o: ../str_utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ccarl/Desktop/Minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/minishell.dir/str_utils.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minishell.dir/str_utils.c.o   -c /Users/ccarl/Desktop/Minishell/str_utils.c

CMakeFiles/minishell.dir/str_utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/str_utils.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ccarl/Desktop/Minishell/str_utils.c > CMakeFiles/minishell.dir/str_utils.c.i

CMakeFiles/minishell.dir/str_utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/str_utils.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ccarl/Desktop/Minishell/str_utils.c -o CMakeFiles/minishell.dir/str_utils.c.s

CMakeFiles/minishell.dir/shell_split.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/shell_split.c.o: ../shell_split.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ccarl/Desktop/Minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/minishell.dir/shell_split.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minishell.dir/shell_split.c.o   -c /Users/ccarl/Desktop/Minishell/shell_split.c

CMakeFiles/minishell.dir/shell_split.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/shell_split.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ccarl/Desktop/Minishell/shell_split.c > CMakeFiles/minishell.dir/shell_split.c.i

CMakeFiles/minishell.dir/shell_split.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/shell_split.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ccarl/Desktop/Minishell/shell_split.c -o CMakeFiles/minishell.dir/shell_split.c.s

CMakeFiles/minishell.dir/shell_join.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/shell_join.c.o: ../shell_join.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ccarl/Desktop/Minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/minishell.dir/shell_join.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minishell.dir/shell_join.c.o   -c /Users/ccarl/Desktop/Minishell/shell_join.c

CMakeFiles/minishell.dir/shell_join.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/shell_join.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ccarl/Desktop/Minishell/shell_join.c > CMakeFiles/minishell.dir/shell_join.c.i

CMakeFiles/minishell.dir/shell_join.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/shell_join.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ccarl/Desktop/Minishell/shell_join.c -o CMakeFiles/minishell.dir/shell_join.c.s

# Object files for target minishell
minishell_OBJECTS = \
"CMakeFiles/minishell.dir/main.c.o" \
"CMakeFiles/minishell.dir/GNL/get_next_line.c.o" \
"CMakeFiles/minishell.dir/GNL/get_next_line_utils.c.o" \
"CMakeFiles/minishell.dir/shell_loop.c.o" \
"CMakeFiles/minishell.dir/libft/ft_strcmp.c.o" \
"CMakeFiles/minishell.dir/parser.c.o" \
"CMakeFiles/minishell.dir/list_utils.c.o" \
"CMakeFiles/minishell.dir/helper.c.o" \
"CMakeFiles/minishell.dir/str_utils.c.o" \
"CMakeFiles/minishell.dir/shell_split.c.o" \
"CMakeFiles/minishell.dir/shell_join.c.o"

# External object files for target minishell
minishell_EXTERNAL_OBJECTS =

minishell: CMakeFiles/minishell.dir/main.c.o
minishell: CMakeFiles/minishell.dir/GNL/get_next_line.c.o
minishell: CMakeFiles/minishell.dir/GNL/get_next_line_utils.c.o
minishell: CMakeFiles/minishell.dir/shell_loop.c.o
minishell: CMakeFiles/minishell.dir/libft/ft_strcmp.c.o
minishell: CMakeFiles/minishell.dir/parser.c.o
minishell: CMakeFiles/minishell.dir/list_utils.c.o
minishell: CMakeFiles/minishell.dir/helper.c.o
minishell: CMakeFiles/minishell.dir/str_utils.c.o
minishell: CMakeFiles/minishell.dir/shell_split.c.o
minishell: CMakeFiles/minishell.dir/shell_join.c.o
minishell: CMakeFiles/minishell.dir/build.make
minishell: CMakeFiles/minishell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ccarl/Desktop/Minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking C executable minishell"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minishell.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/minishell.dir/build: minishell

.PHONY : CMakeFiles/minishell.dir/build

CMakeFiles/minishell.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/minishell.dir/cmake_clean.cmake
.PHONY : CMakeFiles/minishell.dir/clean

CMakeFiles/minishell.dir/depend:
	cd /Users/ccarl/Desktop/Minishell/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ccarl/Desktop/Minishell /Users/ccarl/Desktop/Minishell /Users/ccarl/Desktop/Minishell/cmake-build-debug /Users/ccarl/Desktop/Minishell/cmake-build-debug /Users/ccarl/Desktop/Minishell/cmake-build-debug/CMakeFiles/minishell.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/minishell.dir/depend

