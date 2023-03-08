CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = node.o list.o stackrecursion.o

stackrecursion: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o stackrecursion list.o node.o stackrecursion.o
	
list.o: list.cpp list.h node.cpp node.h
	$(CXX) -g $(CXXFLAGS) -c list.cpp
	
node.o: node.cpp node.h
	$(CXX) -g $(CXXFLAGS) -c node.cpp
	
stackrecursion.o: stackrecursion.cpp list.cpp list.h node.cpp node.h
	$(CXX) -g $(CXXFLAGS) -c stackrecursion.cpp
	
	

clean: 
	rm -f *.o stackrecursion
