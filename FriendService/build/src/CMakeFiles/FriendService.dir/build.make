# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jixu/Mycode/ShiLei/DistroChat/FriendService

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build

# Include any dependencies generated for this target.
include src/CMakeFiles/FriendService.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/FriendService.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/FriendService.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/FriendService.dir/flags.make

src/CMakeFiles/FriendService.dir/Logger.cc.o: src/CMakeFiles/FriendService.dir/flags.make
src/CMakeFiles/FriendService.dir/Logger.cc.o: ../src/Logger.cc
src/CMakeFiles/FriendService.dir/Logger.cc.o: src/CMakeFiles/FriendService.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/FriendService.dir/Logger.cc.o"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/FriendService.dir/Logger.cc.o -MF CMakeFiles/FriendService.dir/Logger.cc.o.d -o CMakeFiles/FriendService.dir/Logger.cc.o -c /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/Logger.cc

src/CMakeFiles/FriendService.dir/Logger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FriendService.dir/Logger.cc.i"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/Logger.cc > CMakeFiles/FriendService.dir/Logger.cc.i

src/CMakeFiles/FriendService.dir/Logger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FriendService.dir/Logger.cc.s"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/Logger.cc -o CMakeFiles/FriendService.dir/Logger.cc.s

src/CMakeFiles/FriendService.dir/friendService.cpp.o: src/CMakeFiles/FriendService.dir/flags.make
src/CMakeFiles/FriendService.dir/friendService.cpp.o: ../src/friendService.cpp
src/CMakeFiles/FriendService.dir/friendService.cpp.o: src/CMakeFiles/FriendService.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/FriendService.dir/friendService.cpp.o"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/FriendService.dir/friendService.cpp.o -MF CMakeFiles/FriendService.dir/friendService.cpp.o.d -o CMakeFiles/FriendService.dir/friendService.cpp.o -c /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/friendService.cpp

src/CMakeFiles/FriendService.dir/friendService.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FriendService.dir/friendService.cpp.i"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/friendService.cpp > CMakeFiles/FriendService.dir/friendService.cpp.i

src/CMakeFiles/FriendService.dir/friendService.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FriendService.dir/friendService.cpp.s"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/friendService.cpp -o CMakeFiles/FriendService.dir/friendService.cpp.s

src/CMakeFiles/FriendService.dir/run.cpp.o: src/CMakeFiles/FriendService.dir/flags.make
src/CMakeFiles/FriendService.dir/run.cpp.o: ../src/run.cpp
src/CMakeFiles/FriendService.dir/run.cpp.o: src/CMakeFiles/FriendService.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/FriendService.dir/run.cpp.o"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/FriendService.dir/run.cpp.o -MF CMakeFiles/FriendService.dir/run.cpp.o.d -o CMakeFiles/FriendService.dir/run.cpp.o -c /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/run.cpp

src/CMakeFiles/FriendService.dir/run.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FriendService.dir/run.cpp.i"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/run.cpp > CMakeFiles/FriendService.dir/run.cpp.i

src/CMakeFiles/FriendService.dir/run.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FriendService.dir/run.cpp.s"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/run.cpp -o CMakeFiles/FriendService.dir/run.cpp.s

src/CMakeFiles/FriendService.dir/proto/friendService.pb.cc.o: src/CMakeFiles/FriendService.dir/flags.make
src/CMakeFiles/FriendService.dir/proto/friendService.pb.cc.o: ../src/proto/friendService.pb.cc
src/CMakeFiles/FriendService.dir/proto/friendService.pb.cc.o: src/CMakeFiles/FriendService.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/FriendService.dir/proto/friendService.pb.cc.o"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/FriendService.dir/proto/friendService.pb.cc.o -MF CMakeFiles/FriendService.dir/proto/friendService.pb.cc.o.d -o CMakeFiles/FriendService.dir/proto/friendService.pb.cc.o -c /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/proto/friendService.pb.cc

src/CMakeFiles/FriendService.dir/proto/friendService.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FriendService.dir/proto/friendService.pb.cc.i"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/proto/friendService.pb.cc > CMakeFiles/FriendService.dir/proto/friendService.pb.cc.i

src/CMakeFiles/FriendService.dir/proto/friendService.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FriendService.dir/proto/friendService.pb.cc.s"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/proto/friendService.pb.cc -o CMakeFiles/FriendService.dir/proto/friendService.pb.cc.s

src/CMakeFiles/FriendService.dir/model/friendmodel.cpp.o: src/CMakeFiles/FriendService.dir/flags.make
src/CMakeFiles/FriendService.dir/model/friendmodel.cpp.o: ../src/model/friendmodel.cpp
src/CMakeFiles/FriendService.dir/model/friendmodel.cpp.o: src/CMakeFiles/FriendService.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/FriendService.dir/model/friendmodel.cpp.o"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/FriendService.dir/model/friendmodel.cpp.o -MF CMakeFiles/FriendService.dir/model/friendmodel.cpp.o.d -o CMakeFiles/FriendService.dir/model/friendmodel.cpp.o -c /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/model/friendmodel.cpp

src/CMakeFiles/FriendService.dir/model/friendmodel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FriendService.dir/model/friendmodel.cpp.i"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/model/friendmodel.cpp > CMakeFiles/FriendService.dir/model/friendmodel.cpp.i

src/CMakeFiles/FriendService.dir/model/friendmodel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FriendService.dir/model/friendmodel.cpp.s"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/model/friendmodel.cpp -o CMakeFiles/FriendService.dir/model/friendmodel.cpp.s

src/CMakeFiles/FriendService.dir/model/uesrmodel.cpp.o: src/CMakeFiles/FriendService.dir/flags.make
src/CMakeFiles/FriendService.dir/model/uesrmodel.cpp.o: ../src/model/uesrmodel.cpp
src/CMakeFiles/FriendService.dir/model/uesrmodel.cpp.o: src/CMakeFiles/FriendService.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/FriendService.dir/model/uesrmodel.cpp.o"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/FriendService.dir/model/uesrmodel.cpp.o -MF CMakeFiles/FriendService.dir/model/uesrmodel.cpp.o.d -o CMakeFiles/FriendService.dir/model/uesrmodel.cpp.o -c /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/model/uesrmodel.cpp

src/CMakeFiles/FriendService.dir/model/uesrmodel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FriendService.dir/model/uesrmodel.cpp.i"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/model/uesrmodel.cpp > CMakeFiles/FriendService.dir/model/uesrmodel.cpp.i

src/CMakeFiles/FriendService.dir/model/uesrmodel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FriendService.dir/model/uesrmodel.cpp.s"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src/model/uesrmodel.cpp -o CMakeFiles/FriendService.dir/model/uesrmodel.cpp.s

# Object files for target FriendService
FriendService_OBJECTS = \
"CMakeFiles/FriendService.dir/Logger.cc.o" \
"CMakeFiles/FriendService.dir/friendService.cpp.o" \
"CMakeFiles/FriendService.dir/run.cpp.o" \
"CMakeFiles/FriendService.dir/proto/friendService.pb.cc.o" \
"CMakeFiles/FriendService.dir/model/friendmodel.cpp.o" \
"CMakeFiles/FriendService.dir/model/uesrmodel.cpp.o"

# External object files for target FriendService
FriendService_EXTERNAL_OBJECTS =

../bin/FriendService: src/CMakeFiles/FriendService.dir/Logger.cc.o
../bin/FriendService: src/CMakeFiles/FriendService.dir/friendService.cpp.o
../bin/FriendService: src/CMakeFiles/FriendService.dir/run.cpp.o
../bin/FriendService: src/CMakeFiles/FriendService.dir/proto/friendService.pb.cc.o
../bin/FriendService: src/CMakeFiles/FriendService.dir/model/friendmodel.cpp.o
../bin/FriendService: src/CMakeFiles/FriendService.dir/model/uesrmodel.cpp.o
../bin/FriendService: src/CMakeFiles/FriendService.dir/build.make
../bin/FriendService: src/CMakeFiles/FriendService.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable ../../bin/FriendService"
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FriendService.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/FriendService.dir/build: ../bin/FriendService
.PHONY : src/CMakeFiles/FriendService.dir/build

src/CMakeFiles/FriendService.dir/clean:
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src && $(CMAKE_COMMAND) -P CMakeFiles/FriendService.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/FriendService.dir/clean

src/CMakeFiles/FriendService.dir/depend:
	cd /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jixu/Mycode/ShiLei/DistroChat/FriendService /home/jixu/Mycode/ShiLei/DistroChat/FriendService/src /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src /home/jixu/Mycode/ShiLei/DistroChat/FriendService/build/src/CMakeFiles/FriendService.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/FriendService.dir/depend
