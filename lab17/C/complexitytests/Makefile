# Compiler options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Graph files (in parent directory)
GRAPH_HDR = ../graph.hpp
GRAPH_SRC = ../graph.cpp
GRAPH_OBJ = graph.o

# Test files
TEST_SRC = graphTests.cpp
TEST_EXE = graphTests

# Default target - build test executable
all: $(TEST_EXE)

# Compile graph object file
$(GRAPH_OBJ): $(GRAPH_SRC) $(GRAPH_HDR)
	$(CXX) $(CXXFLAGS) -c $(GRAPH_SRC) -o $(GRAPH_OBJ)

# Linking rules
$(TEST_EXE): $(TEST_SRC) $(GRAPH_OBJ)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) $(GRAPH_OBJ) -o $(TEST_EXE)

# Clean rules
clean:
	rm -f $(TEST_EXE) $(GRAPH_OBJ)

# Run tests
run: $(TEST_EXE)
	./$(TEST_EXE)

# Create results directory
setup:
	mkdir -p graphResults

# Phony targets
.PHONY: all clean run setup