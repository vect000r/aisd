# Compiler options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Graph files
GRAPH_HDR = graph.hpp
GRAPH_SRC = graph.cpp
GRAPH_OBJ = graph.o

MAIN_EXE = A.exe

# Default target - build executable
all: $(MAIN_EXE)

# Compile graph object file
$(GRAPH_OBJ): $(GRAPH_SRC) $(GRAPH_HDR)
	$(CXX) $(CXXFLAGS) -c $(GRAPH_SRC) -o $(GRAPH_OBJ)

# Linking rules
$(MAIN_EXE): A.cpp $(GRAPH_OBJ)
	$(CXX) $(CXXFLAGS) A.cpp $(GRAPH_OBJ) -o $(MAIN_EXE)

# Clean rules
clean:
	rm -f $(MAIN_EXE) $(GRAPH_OBJ)

# Run tests
run: $(MAIN_EXE)
	./$(MAIN_EXE)

# Phony targets
.PHONY: all clean run