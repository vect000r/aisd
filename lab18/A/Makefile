# Compiler options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Graph files
GRAPH_HDR = graph.hpp
GRAPH_SRC = graph.cpp
GRAPH_OBJ = graph.o

# Knight files
KNIGHT_SRC = knight.cpp
KNIGHT_OBJ = knight.o

# Main executable
MAIN_EXE = main.exe

# Default target - build main executable
all: $(MAIN_EXE)

# Compile graph object file
$(GRAPH_OBJ): $(GRAPH_SRC) $(GRAPH_HDR)
	$(CXX) $(CXXFLAGS) -c $(GRAPH_SRC) -o $(GRAPH_OBJ)

# Compile knight object file (depends on graph)
$(KNIGHT_OBJ): $(KNIGHT_SRC) $(GRAPH_HDR)
	$(CXX) $(CXXFLAGS) -c $(KNIGHT_SRC) -o $(KNIGHT_OBJ)

# Link main executable
$(MAIN_EXE): main.cpp $(KNIGHT_OBJ) $(GRAPH_OBJ)
	$(CXX) $(CXXFLAGS) main.cpp $(KNIGHT_OBJ) $(GRAPH_OBJ) -o $(MAIN_EXE)

# Clean rules
clean:
	rm -f $(MAIN_EXE) $(KNIGHT_OBJ) $(GRAPH_OBJ)

# Run the main program
run: $(MAIN_EXE)
	./$(MAIN_EXE)

# Phony targets
.PHONY: all clean run