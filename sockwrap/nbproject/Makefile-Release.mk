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
	build/Release/GNU-Generic/client.o \
	build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/socket.o \
	build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/network.o \
	build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/sockwrap/../cppsocket/main.o \
	build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/serversocket.o \
	build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/clientsocket.o

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
.build-conf: ${BUILD_SUBPROJECTS} dist/Release/GNU-Generic/sockwrap

dist/Release/GNU-Generic/sockwrap: ${OBJECTFILES}
	@${MKDIR} -p dist/Release/GNU-Generic
	${LINK.cc} -o dist/Release/GNU-Generic/sockwrap ${OBJECTFILES} ${LDLIBSOPTIONS} 

build/Release/GNU-Generic/client.o: client.cc 
	@${MKDIR} -p build/Release/GNU-Generic
	$(COMPILE.cc) -O2 -o build/Release/GNU-Generic/client.o client.cc

build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/socket.o: ../cppsocket/socket.cpp 
	@${MKDIR} -p build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket
	$(COMPILE.cc) -O2 -o build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/socket.o ../cppsocket/socket.cpp

build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/network.o: ../cppsocket/network.cpp 
	@${MKDIR} -p build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket
	$(COMPILE.cc) -O2 -o build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/network.o ../cppsocket/network.cpp

build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/sockwrap/../cppsocket/main.o: ../cppsocket/main.cpp 
	@${MKDIR} -p build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/sockwrap/../cppsocket
	$(COMPILE.cc) -O2 -o build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/sockwrap/../cppsocket/main.o ../cppsocket/main.cpp

build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/serversocket.o: ../cppsocket/serversocket.cpp 
	@${MKDIR} -p build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket
	$(COMPILE.cc) -O2 -o build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/serversocket.o ../cppsocket/serversocket.cpp

build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/clientsocket.o: ../cppsocket/clientsocket.cpp 
	@${MKDIR} -p build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket
	$(COMPILE.cc) -O2 -o build/Release/GNU-Generic/_ext/Users/mdurrer/NetBeans/cppsocket/clientsocket.o ../cppsocket/clientsocket.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/GNU-Generic/sockwrap

# Subprojects
.clean-subprojects:
