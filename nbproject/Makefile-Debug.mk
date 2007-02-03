#
# Gererated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add custumized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=g77

# Include project Makefile
include Makefile

# Object Files
OBJECTFILES= \
	build/Debug/GNU-Linux-x86/main.o \
	build/Debug/GNU-Linux-x86/invaders.o \
	build/Debug/GNU-Linux-x86/rom.o \
	build/Debug/GNU-Linux-x86/cpu.o \
	build/Debug/GNU-Linux-x86/memory.o \
	build/Debug/GNU-Linux-x86/environment.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=\
	-lSDL \
	-lSDL_image

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Debug/GNU-Linux-x86/si

dist/Debug/GNU-Linux-x86/si: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -o dist/Debug/GNU-Linux-x86/si ${OBJECTFILES} ${LDLIBSOPTIONS} 

build/Debug/GNU-Linux-x86/main.o: main.cc 
	${MKDIR} -p build/Debug/GNU-Linux-x86
	$(COMPILE.cc) -g -o build/Debug/GNU-Linux-x86/main.o main.cc

build/Debug/GNU-Linux-x86/invaders.o: invaders.cc 
	${MKDIR} -p build/Debug/GNU-Linux-x86
	$(COMPILE.cc) -g -o build/Debug/GNU-Linux-x86/invaders.o invaders.cc

build/Debug/GNU-Linux-x86/rom.o: rom.cc 
	${MKDIR} -p build/Debug/GNU-Linux-x86
	$(COMPILE.cc) -g -o build/Debug/GNU-Linux-x86/rom.o rom.cc

build/Debug/GNU-Linux-x86/cpu.o: cpu.cc 
	${MKDIR} -p build/Debug/GNU-Linux-x86
	$(COMPILE.cc) -g -o build/Debug/GNU-Linux-x86/cpu.o cpu.cc

build/Debug/GNU-Linux-x86/memory.o: memory.cc 
	${MKDIR} -p build/Debug/GNU-Linux-x86
	$(COMPILE.cc) -g -o build/Debug/GNU-Linux-x86/memory.o memory.cc

build/Debug/GNU-Linux-x86/environment.o: environment.cc 
	${MKDIR} -p build/Debug/GNU-Linux-x86
	$(COMPILE.cc) -g -o build/Debug/GNU-Linux-x86/environment.o environment.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/si

# Subprojects
.clean-subprojects:
