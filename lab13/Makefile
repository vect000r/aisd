CXX = g++
LIBS =
CXXFLAGS = -Wall -std=c++11
OBJECTS = main.o dictionarySimple.o setSimple.o setLinked.o 
HFILES = dictionarySimple.hpp setSimple.hpp setLinked.hpp
TARGET = main.out

%.o : %.cpp $(HFILES) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJECTS) -o $(TARGET)

.PHONY : clean

clean :
	$(RM) $(TARGET) *.o core