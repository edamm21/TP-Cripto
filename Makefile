# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nachograsso/Desktop/ITBA/CRIPTO/TP-Cripto

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nachograsso/Desktop/ITBA/CRIPTO/TP-Cripto

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/nachograsso/Desktop/ITBA/CRIPTO/TP-Cripto/CMakeFiles /Users/nachograsso/Desktop/ITBA/CRIPTO/TP-Cripto//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/nachograsso/Desktop/ITBA/CRIPTO/TP-Cripto/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named TP_Cripto

# Build rule for target.
TP_Cripto: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 TP_Cripto
.PHONY : TP_Cripto

# fast build rule for target.
TP_Cripto/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/build
.PHONY : TP_Cripto/fast

src/args_parser.o: src/args_parser.c.o

.PHONY : src/args_parser.o

# target to build an object file
src/args_parser.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/args_parser.c.o
.PHONY : src/args_parser.c.o

src/args_parser.i: src/args_parser.c.i

.PHONY : src/args_parser.i

# target to preprocess a source file
src/args_parser.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/args_parser.c.i
.PHONY : src/args_parser.c.i

src/args_parser.s: src/args_parser.c.s

.PHONY : src/args_parser.s

# target to generate assembly for a file
src/args_parser.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/args_parser.c.s
.PHONY : src/args_parser.c.s

src/common/helper.o: src/common/helper.c.o

.PHONY : src/common/helper.o

# target to build an object file
src/common/helper.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/common/helper.c.o
.PHONY : src/common/helper.c.o

src/common/helper.i: src/common/helper.c.i

.PHONY : src/common/helper.i

# target to preprocess a source file
src/common/helper.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/common/helper.c.i
.PHONY : src/common/helper.c.i

src/common/helper.s: src/common/helper.c.s

.PHONY : src/common/helper.s

# target to generate assembly for a file
src/common/helper.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/common/helper.c.s
.PHONY : src/common/helper.c.s

src/distribution.o: src/distribution.c.o

.PHONY : src/distribution.o

# target to build an object file
src/distribution.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/distribution.c.o
.PHONY : src/distribution.c.o

src/distribution.i: src/distribution.c.i

.PHONY : src/distribution.i

# target to preprocess a source file
src/distribution.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/distribution.c.i
.PHONY : src/distribution.c.i

src/distribution.s: src/distribution.c.s

.PHONY : src/distribution.s

# target to generate assembly for a file
src/distribution.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/distribution.c.s
.PHONY : src/distribution.c.s

src/finding.o: src/finding.c.o

.PHONY : src/finding.o

# target to build an object file
src/finding.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/finding.c.o
.PHONY : src/finding.c.o

src/finding.i: src/finding.c.i

.PHONY : src/finding.i

# target to preprocess a source file
src/finding.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/finding.c.i
.PHONY : src/finding.c.i

src/finding.s: src/finding.c.s

.PHONY : src/finding.s

# target to generate assembly for a file
src/finding.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/finding.c.s
.PHONY : src/finding.c.s

src/header_parser.o: src/header_parser.c.o

.PHONY : src/header_parser.o

# target to build an object file
src/header_parser.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/header_parser.c.o
.PHONY : src/header_parser.c.o

src/header_parser.i: src/header_parser.c.i

.PHONY : src/header_parser.i

# target to preprocess a source file
src/header_parser.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/header_parser.c.i
.PHONY : src/header_parser.c.i

src/header_parser.s: src/header_parser.c.s

.PHONY : src/header_parser.s

# target to generate assembly for a file
src/header_parser.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/header_parser.c.s
.PHONY : src/header_parser.c.s

src/main.o: src/main.c.o

.PHONY : src/main.o

# target to build an object file
src/main.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/main.c.o
.PHONY : src/main.c.o

src/main.i: src/main.c.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/main.c.i
.PHONY : src/main.c.i

src/main.s: src/main.c.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TP_Cripto.dir/build.make CMakeFiles/TP_Cripto.dir/src/main.c.s
.PHONY : src/main.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... TP_Cripto"
	@echo "... src/args_parser.o"
	@echo "... src/args_parser.i"
	@echo "... src/args_parser.s"
	@echo "... src/common/helper.o"
	@echo "... src/common/helper.i"
	@echo "... src/common/helper.s"
	@echo "... src/distribution.o"
	@echo "... src/distribution.i"
	@echo "... src/distribution.s"
	@echo "... src/finding.o"
	@echo "... src/finding.i"
	@echo "... src/finding.s"
	@echo "... src/header_parser.o"
	@echo "... src/header_parser.i"
	@echo "... src/header_parser.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

