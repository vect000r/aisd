# Compiler options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Graph files
GRAPH_HDR = graph.hpp
GRAPH_SRC = graph.cpp
GRAPH_OBJ = graph.o

MAIN_EXE = main.exe
INTERSECTION_EXE = intersection.exe
INTERPROBLEM_EXE = interproblem.exe

# Default target - build all executables
all: $(MAIN_EXE) $(INTERSECTION_EXE) $(INTERPROBLEM_EXE)

# Compile graph object file
$(GRAPH_OBJ): $(GRAPH_SRC) $(GRAPH_HDR)
	$(CXX) $(CXXFLAGS) -c $(GRAPH_SRC) -o $(GRAPH_OBJ)

# Linking rules
$(MAIN_EXE): main.cpp $(GRAPH_OBJ)
	$(CXX) $(CXXFLAGS) main.cpp $(GRAPH_OBJ) -o $(MAIN_EXE)

$(INTERSECTION_EXE): intersection.cpp $(GRAPH_OBJ)
	$(CXX) $(CXXFLAGS) intersection.cpp $(GRAPH_OBJ) -o $(INTERSECTION_EXE)

$(INTERPROBLEM_EXE): interproblem.cpp $(GRAPH_OBJ)
	$(CXX) $(CXXFLAGS) interproblem.cpp $(GRAPH_OBJ) -o $(INTERPROBLEM_EXE)

# Clean rules
clean:
	rm -f $(MAIN_EXE) $(INTERSECTION_EXE) $(INTERPROBLEM_EXE) $(GRAPH_OBJ)

# Run tests
run: $(MAIN_EXE)
	./$(MAIN_EXE)

intersection: $(INTERSECTION_EXE)
	./$(INTERSECTION_EXE)

interproblem: $(INTERPROBLEM_EXE)
	./$(INTERPROBLEM_EXE)

# Phony targets
.PHONY: all clean run intersection interproblem