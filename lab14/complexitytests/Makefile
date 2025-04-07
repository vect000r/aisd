# Makefile for setHashedTest

# Compiler options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Paths
PARENT_DIR = ..

# Result directories
SET_HASHED_RESULTS = setHashedResults

# Header files
SET_HASHED_HDR = $(PARENT_DIR)/setHashed.hpp
SET_LINKED_HDR = $(PARENT_DIR)/setLinked.hpp

# Source files
SET_HASHED_SRC = $(PARENT_DIR)/setHashed.cpp
SET_LINKED_SRC = $(PARENT_DIR)/setLinked.cpp

# Object files
SET_HASHED_OBJ = $(PARENT_DIR)/setHashed.o
SET_LINKED_OBJ = $(PARENT_DIR)/setLinked.o

# Executables
SET_HASHED_EXE = setHashedTest

# Default target - build executable
all: directories $(SET_HASHED_EXE)

# Create result directories
directories:
	mkdir -p $(SET_HASHED_RESULTS)

# Compile object files
$(SET_LINKED_OBJ): $(SET_LINKED_SRC) $(SET_LINKED_HDR)
	$(CXX) $(CXXFLAGS) -c $(SET_LINKED_SRC) -o $(SET_LINKED_OBJ)

$(SET_HASHED_OBJ): $(SET_HASHED_SRC) $(SET_HASHED_HDR) $(SET_LINKED_HDR)
	$(CXX) $(CXXFLAGS) -c $(SET_HASHED_SRC) -o $(SET_HASHED_OBJ)

# Linking rules
$(SET_HASHED_EXE): setHashedTest.cpp $(SET_HASHED_OBJ) $(SET_LINKED_OBJ)
	$(CXX) $(CXXFLAGS) -I$(PARENT_DIR) setHashedTest.cpp $(SET_HASHED_OBJ) $(SET_LINKED_OBJ) -o $(SET_HASHED_EXE)

# Clean rules
clean:
	rm -f $(SET_HASHED_EXE) $(SET_HASHED_OBJ) $(SET_LINKED_OBJ)
	rm -rf $(SET_HASHED_RESULTS)

# Run tests
run: $(SET_HASHED_EXE)
	./$(SET_HASHED_EXE)

# Phony targets
.PHONY: all directories clean run