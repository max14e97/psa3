# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)

ifeq ($(type),opt)
    CPPFLAGS += -g
    LDFLAGS += -g
else
    CPPFLAGS += -O3
    LDFLAGS += -O3
endif

all: pathfinder linkpredictor awardsceremony



# include what ever source code *.hpp files pathfinder relies on (these are merely the ones that were used in the solution)

pathfinder: ActorNode.hpp MovieNode.hpp ActorGraph.hpp

linkpredictor: ActorNode2.hpp MovieNode2.hpp linkGraph.cpp linkpredictor.cpp

awardsceremony: ActorNode3.hpp MovieNode3.hpp part3Graph.cpp awardsceremony.cpp



# include what ever source code *.hpp files ActorGraph relies on (these are merely the ones that were used in the solution)

# Note: you do not have to include a *.cpp file if it aleady has a paired *.hpp file that is already included with class/method headers

ActorGraph.o: ActorNode.hpp MovieNode.hpp ActorGraph.hpp

ActorNode.o: MovieNode.hpp ActorNode.hpp

MovieNode.o: ActorNode.hpp MovieNode.hpp

#main.o: ActorNode.hpp MovieNode.hpp ActorGraph.hpp main.cpp


clean:
	rm -f pathfinder linkpredictor awardsceremony *.o core* *.gch

