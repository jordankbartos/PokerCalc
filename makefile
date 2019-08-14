# file: makefile
# Author: Jordan K Bartos
# Date: August 10, 2019

# compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++0x
# CXXFLAGS += -g
# CXXFLAGS += -Wall
# CXXFLAGS += -pedantic-errors

# cpp files
CPPS = helperFunctions.cpp
CPPS += Game.cpp
CPPS += Player.cpp
CPPS += PlayerGraph.cpp
CPPS += main.cpp

# hpp files
HPPS = helperFunctions.hpp
HPPS += Game.hpp
HPPS += Player.hpp
HPPS += PlayerGraph.hpp
HPPS += Structs.hpp

# object files
OBJS = main.o
OBJS += helperFunctions.o
OBJS += Game.o
OBJS += Player.o
OBJS += PlayerGraph.o

PokerCalc: $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPS) -o PokerCalc

%.o : %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	rm $(OBJS) PokerCalc

# runs the program in valgrind with all the bells and whistles
debug :
	valgrind -v --leak-check=full --track-origins=yes ./PokerCalc

# makes a .zip of the program files for moving it to other systems
zip :
	zip -D PokerCalc.zip $(CPPS) $(HPPS) makefile *.pdf
