# Makefile for PriorityQueueTests

# Compiler options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Paths
PARENT_DIR = ..

# Result directories
PRIORITY_QUEUE_RESULTS = PriorityQueueResults

# Header files
PRIORITY_QUEUE_HDR = $(PARENT_DIR)/priorityQueue.hpp
PRIORITY_HEAP_HDR = $(PARENT_DIR)/priorityHeap.hpp
SET_SIMPLE_HDR = $(PARENT_DIR)/$(PARENT_DIR)/lab14/setSimple.hpp

# Source files
PRIORITY_QUEUE_SRC = $(PARENT_DIR)/priorityQueue.cpp
PRIORITY_HEAP_SRC = $(PARENT_DIR)/priorityHeap.cpp
SET_SIMPLE_SRC = $(PARENT_DIR)/$(PARENT_DIR)/lab14/setSimple.cpp

# Object files
PRIORITY_QUEUE_OBJ = $(PARENT_DIR)/priorityQueue.o
PRIORITY_HEAP_OBJ = $(PARENT_DIR)/priorityHeap.o
SET_SIMPLE_OBJ = $(PARENT_DIR)/$(PARENT_DIR)/lab14/setSimple.o

# Executables
PRIORITY_QUEUE_EXE = priorityQueueTests

# Default target - build executable
all: directories $(PRIORITY_QUEUE_EXE)

# Create result directories
directories:
	mkdir -p $(PRIORITY_QUEUE_RESULTS)

# Compile object files
$(SET_SIMPLE_OBJ): $(SET_SIMPLE_SRC) $(SET_SIMPLE_HDR)
	$(CXX) $(CXXFLAGS) -c $(SET_SIMPLE_SRC) -o $(SET_SIMPLE_OBJ)

$(PRIORITY_HEAP_OBJ): $(PRIORITY_HEAP_SRC) $(PRIORITY_HEAP_HDR)
	$(CXX) $(CXXFLAGS) -c $(PRIORITY_HEAP_SRC) -o $(PRIORITY_HEAP_OBJ)

$(PRIORITY_QUEUE_OBJ): $(PRIORITY_QUEUE_SRC) $(PRIORITY_QUEUE_HDR) $(SET_SIMPLE_HDR)
	$(CXX) $(CXXFLAGS) -c $(PRIORITY_QUEUE_SRC) -o $(PRIORITY_QUEUE_OBJ)

# Linking rules
$(PRIORITY_QUEUE_EXE): priorityQueueTests.cpp $(PRIORITY_QUEUE_OBJ) $(PRIORITY_HEAP_OBJ) $(SET_SIMPLE_OBJ)
	$(CXX) $(CXXFLAGS) -I$(PARENT_DIR) priorityQueueTests.cpp $(PRIORITY_QUEUE_OBJ) $(PRIORITY_HEAP_OBJ) $(SET_SIMPLE_OBJ) -o $(PRIORITY_QUEUE_EXE)

# Clean rules
clean:
	rm -f $(PRIORITY_QUEUE_EXE) $(PRIORITY_QUEUE_OBJ) $(PRIORITY_HEAP_OBJ) $(SET_SIMPLE_OBJ)
	rm -rf $(PRIORITY_QUEUE_RESULTS)

# Run tests
run: $(PRIORITY_QUEUE_EXE)
	./$(PRIORITY_QUEUE_EXE)

# Phony targets
.PHONY: all directories clean run