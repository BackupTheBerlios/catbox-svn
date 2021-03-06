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
	build/Release/GNU-Linux-x86/main.o \
	build/Release/GNU-Linux-x86/invaders.o \
	build/Release/GNU-Linux-x86/rom.o \
	build/Release/GNU-Linux-x86/cpu.o \
	build/Release/GNU-Linux-x86/memory.o \
	build/Release/GNU-Linux-x86/environment.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Release/GNU-Linux-x86/si

dist/Release/GNU-Linux-x86/si: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -o dist/Release/GNU-Linux-x86/si ${OBJECTFILES} ${LDLIBSOPTIONS} 

build/Release/GNU-Linux-x86/main.o: main.cc 
	${MKDIR} -p build/Release/GNU-Linux-x86
	$(COMPILE.cc) -O2 -o build/Release/GNU-Linux-x86/main.o main.cc

build/Release/GNU-Linux-x86/invaders.o: invaders.cc 
	${MKDIR} -p build/Release/GNU-Linux-x86
	$(COMPILE.cc) -O2 -o build/Release/GNU-Linux-x86/invaders.o invaders.cc

build/Release/GNU-Linux-x86/rom.o: rom.cc 
	${MKDIR} -p build/Release/GNU-Linux-x86
	$(COMPILE.cc) -O2 -o build/Release/GNU-Linux-x86/rom.o rom.cc

build/Release/GNU-Linux-x86/cpu.o: cpu.cc 
	${MKDIR} -p build/Release/GNU-Linux-x86
	$(COMPILE.cc) -O2 -o build/Release/GNU-Linux-x86/cpu.o cpu.cc

build/Release/GNU-Linux-x86/memory.o: memory.cc 
	${MKDIR} -p build/Release/GNU-Linux-x86
	$(COMPILE.cc) -O2 -o build/Release/GNU-Linux-x86/memory.o memory.cc

build/Release/GNU-Linux-x86/environment.o: environment.cc 
	${MKDIR} -p build/Release/GNU-Linux-x86
	$(COMPILE.cc) -O2 -o build/Release/GNU-Linux-x86/environment.o environment.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/si

# Subprojects
.clean-subprojects:
