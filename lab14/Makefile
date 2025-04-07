CXX = g++
LIBS =
CXXFLAGS = -Wall -std=c++11
OBJECTS = main.o  setSimple.o setHashed.o setLinked.o
HFILES =  setSimple.hpp setHashed.hpp setLinked.hpp
TARGET = main.out

%.o : %.cpp $(HFILES) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJECTS) -o $(TARGET)

.PHONY : clean

clean :
	$(RM) $(TARGET) *.o core