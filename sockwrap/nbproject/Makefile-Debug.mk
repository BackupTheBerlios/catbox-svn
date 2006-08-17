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
	build/Debug/GNU-Generic/client.o \
	build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/socket.o \
	build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/network.o \
	build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/sockwrap/../cppsocket/main.o \
	build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/serversocket.o \
	build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/clientsocket.o

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
.build-conf: ${BUILD_SUBPROJECTS} dist/Debug/GNU-Generic/sockwrap

dist/Debug/GNU-Generic/sockwrap: ${OBJECTFILES}
	@${MKDIR} -p dist/Debug/GNU-Generic
	${LINK.cc} -o dist/Debug/GNU-Generic/sockwrap ${OBJECTFILES} ${LDLIBSOPTIONS} 

build/Debug/GNU-Generic/client.o: client.cc 
	@${MKDIR} -p build/Debug/GNU-Generic
	$(COMPILE.cc) -g -o build/Debug/GNU-Generic/client.o client.cc

build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/socket.o: ../cppsocket/socket.cpp 
	@${MKDIR} -p build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket
	$(COMPILE.cc) -g -o build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/socket.o ../cppsocket/socket.cpp

build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/network.o: ../cppsocket/network.cpp 
	@${MKDIR} -p build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket
	$(COMPILE.cc) -g -o build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/network.o ../cppsocket/network.cpp

build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/sockwrap/../cppsocket/main.o: ../cppsocket/main.cpp 
	@${MKDIR} -p build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/sockwrap/../cppsocket
	$(COMPILE.cc) -g -o build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/sockwrap/../cppsocket/main.o ../cppsocket/main.cpp

build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/serversocket.o: ../cppsocket/serversocket.cpp 
	@${MKDIR} -p build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket
	$(COMPILE.cc) -g -o build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/serversocket.o ../cppsocket/serversocket.cpp

build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/clientsocket.o: ../cppsocket/clientsocket.cpp 
	@${MKDIR} -p build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket
	$(COMPILE.cc) -g -o build/Debug/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/clientsocket.o ../cppsocket/clientsocket.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Generic/sockwrap

# Subprojects
.clean-subprojects:
