# Compiler options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Paths
PARENT_DIR = ..

# Header files
SET_SIMPLE_HDR = $(PARENT_DIR)/lab13/setSimple.hpp
PRIORITY_QUEUE_HDR = priorityQueue.hpp

# Source files
SET_SIMPLE_SRC = $(PARENT_DIR)/lab13/setSimple.cpp
PRIORITY_QUEUE_SRC = priorityQueue.cpp

# Object files
SET_SIMPLE_OBJ = $(PARENT_DIR)/lab13/setSimple.o
PRIORITY_QUEUE_OBJ = priorityQueue.o

MAIN_EXE = main

# Default target - build executable
all: $(MAIN_EXE)

# Compile object files
$(SET_SIMPLE_OBJ): $(SET_SIMPLE_SRC) $(SET_SIMPLE_HDR)
	$(CXX) $(CXXFLAGS) -c $(SET_SIMPLE_SRC) -o $(SET_SIMPLE_OBJ)

$(PRIORITY_QUEUE_OBJ): $(PRIORITY_QUEUE_SRC) $(PRIORITY_QUEUE_HDR) $(SET_SIMPLE_HDR)
	$(CXX) $(CXXFLAGS) -c $(PRIORITY_QUEUE_SRC) -o $(PRIORITY_QUEUE_OBJ)

# Linking rules
$(MAIN_EXE): main.cpp $(PRIORITY_QUEUE_OBJ) $(SET_SIMPLE_OBJ)
	$(CXX) $(CXXFLAGS) main.cpp $(PRIORITY_QUEUE_OBJ) $(SET_SIMPLE_OBJ) -o $(MAIN_EXE)

# Clean rules
clean:
	rm -f $(MAIN_EXE) $(PRIORITY_QUEUE_OBJ) $(SET_SIMPLE_OBJ)

# Run tests
run: $(MAIN_EXE)
	./$(MAIN_EXE)

# Phony targets
.PHONY: all clean run