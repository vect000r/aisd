CXX = g++
LIBS =
CXXFLAGS = -Wall -std=c++11
OBJECTS = main.o doublelist.o deque.o
HFILES = doublelist.hpp deque.hpp
TARGET = main.out

%.o : %.cpp $(HFILES) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJECTS) -o $(TARGET)

.PHONY : clean

clean :
	$(RM) $(TARGET) *.o core