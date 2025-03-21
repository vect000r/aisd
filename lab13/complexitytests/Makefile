# Combined Makefile for all data structure complexity tests

# Compiler options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Paths
PARENT_DIR = ..

# Result directories
SET_SIMPLE_RESULTS = setSimpleResults
SET_LINKED_RESULTS = setLinkedResults
DICT_SIMPLE_RESULTS = dictionarySimpleResults

# Source files for SetSimple
SET_SIMPLE_SRC = setSimpleTest.cpp $(PARENT_DIR)/setSimple.cpp
SET_SIMPLE_HDR = $(PARENT_DIR)/setSimple.hpp
SET_SIMPLE_EXE = setSimpleTest

# Source files for SetLinked
SET_LINKED_SRC = setLinkedTest.cpp $(PARENT_DIR)/setLinked.cpp
SET_LINKED_HDR = $(PARENT_DIR)/setLinked.hpp
SET_LINKED_EXE = setLinkedTest

# Source files for DictionarySimple
DICT_SIMPLE_SRC = dictionarySimpleTest.cpp $(PARENT_DIR)/dictionarySimple.cpp
DICT_SIMPLE_HDR = $(PARENT_DIR)/dictionarySimple.hpp
DICT_SIMPLE_EXE = dictionarySimpleTest

# Default target - build all executables
all: directories $(SET_SIMPLE_EXE) $(SET_LINKED_EXE) $(DICT_SIMPLE_EXE)

# Create result directories
directories:
	mkdir -p $(SET_SIMPLE_RESULTS)
	mkdir -p $(SET_LINKED_RESULTS)
	mkdir -p $(DICT_SIMPLE_RESULTS)

# Linking rules
$(SET_SIMPLE_EXE): $(SET_SIMPLE_SRC) $(SET_SIMPLE_HDR)
	$(CXX) $(CXXFLAGS) -I$(PARENT_DIR) $(SET_SIMPLE_SRC) -o $(SET_SIMPLE_EXE)

$(SET_LINKED_EXE): $(SET_LINKED_SRC) $(SET_LINKED_HDR)
	$(CXX) $(CXXFLAGS) -I$(PARENT_DIR) $(SET_LINKED_SRC) -o $(SET_LINKED_EXE)

$(DICT_SIMPLE_EXE): $(DICT_SIMPLE_SRC) $(DICT_SIMPLE_HDR)
	$(CXX) $(CXXFLAGS) -I$(PARENT_DIR) $(DICT_SIMPLE_SRC) -o $(DICT_SIMPLE_EXE)

# Clean rules
clean: clean-simple clean-linked clean-dict

clean-simple:
	rm -f $(SET_SIMPLE_EXE) $(SET_SIMPLE_RESULTS)/*.txt

clean-linked:
	rm -f $(SET_LINKED_EXE) $(SET_LINKED_RESULTS)/*.txt

clean-dict:
	rm -f $(DICT_SIMPLE_EXE) $(DICT_SIMPLE_RESULTS)/*.txt

clean-all: clean
	rm -f $(SET_SIMPLE_EXE) $(SET_LINKED_EXE) $(DICT_SIMPLE_EXE)
	rm -rf $(SET_SIMPLE_RESULTS) $(SET_LINKED_RESULTS) $(DICT_SIMPLE_RESULTS)

# Run tests
run-simple: $(SET_SIMPLE_EXE)
	./$(SET_SIMPLE_EXE)

run-linked: $(SET_LINKED_EXE)
	./$(SET_LINKED_EXE)

run-dict: $(DICT_SIMPLE_EXE)
	./$(DICT_SIMPLE_EXE)

run-all: run-simple run-linked run-dict

# Phony targets
.PHONY: all directories clean clean-simple clean-linked clean-dict clean-all run-simple run-linked run-dict run-all