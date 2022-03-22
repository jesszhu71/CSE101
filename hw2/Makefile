CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = node.o list.o wrapper.o

nqueens: $(OBJECTS)
		$(CXX) -g $(CXXFLAGS) -o nqueens list.o wrapper.o node.o
	
	
list.o: list.cpp list.h node.cpp node.h
		$(CXX) -g $(CXXFLAGS) -c list.cpp
		
node.o: node.cpp node.h
		$(CXX) -g $(CXXFLAGS) -c node.cpp
		
wrapper.o: list.cpp list.h wrapper.cpp node.cpp node.h
		$(CXX) -g $(CXXFLAGS) -c wrapper.cpp
	
clean:
	rm -f *.o nqueens