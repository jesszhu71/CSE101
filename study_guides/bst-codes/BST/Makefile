CXX = g++
CXXFLAGS = -Wall

OBJECTS = bst.o wrapper.o

wordrange: $(OBJECTS)
		$(CXX) -g $(CXXFLAGS) -o wordrange bst.o wrapper.o
		
bst.o: bst.cpp bst.h
		$(CXX) -g $(CXXFLAGS) -c bst.cpp
		
wrapper.o: bst.cpp bst.h wrapper.cpp
		$(CXX) -g $(CXXFLAGS) -c wrapper.cpp
		
clean:
		rm -f *.o
		rm wordrange