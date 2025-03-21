CXX = g++
LIBS =
CXXFLAGS = -Wall -std=c++11
OBJECTS = main.o dictionarySimple.o setLinked.o setSimple.o
HFILES = dictionarySimple.hpp setLinked.hpp setSimple.hpp
TARGET = main.out

%.o : %.cpp $(HFILES) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJECTS) -o $(TARGET)

.PHONY : clean

clean :
	$(RM) $(TARGET) *.o core