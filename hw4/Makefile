CXX = g++
CXXFLAGS = -Wall

OBJECTS = wrapper.o

sixdegrees: $(OBJECTS)
		$(CXX) -g $(CXXFLAGS) -o sixdegrees wrapper.o

wrapper.o: wrapper.cpp
		$(CXX) -g $(CXXFLAGS) -c wrapper.cpp
		
clean:
		rm -f *o
		rm sixdegrees
	