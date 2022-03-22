CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = linkedlist.o wrapper.o

bard: $(OBJECTS)
		$(CXX) -g $(CXXFLAGS) -o bard linkedlist.o wrapper.o

linkedlist.o: linkedlist.cpp linkedlist.h
		$(CXX) -g $(CXXFLAGS) -c linkedlist.cpp
		
wrapper.o: linkedlist.cpp linkedlist.h wrapper.cpp
		$(CXX) -g $(CXXFLAGS) -c wrapper.cpp
		
clean:
		rm -f *.o
		rm bard