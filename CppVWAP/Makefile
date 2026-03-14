# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -O3 -Wall -Iinclude -pthread -lzmq

# Debug flags
DEBUGFLAGS := -DDEBUG -std=c++17 -ggdb3 -Wall -Iinclude -pthread -lzmq

# Directories
SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
BIN_DIR := bin

# Target binary name
TARGET := $(BIN_DIR)/cppvwap
DEBUG_TARGET := $(BIN_DIR)/cppvwap_debug

# Find all .cpp files under src/
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)

# Generate corresponding .o file paths in OBJ/
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
DEBUG_OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.debug.o, $(SRC_FILES))

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $@  $(CXXFLAGS) 

# Compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Debug target
debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(DEBUG_OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $@ $(DEBUGFLAGS) -lpthread

$(OBJ_DIR)/%.debug.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(DEBUGFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/*.debug.o $(TARGET) $(DEBUG_TARGET)

# Phony targets
.PHONY: all clean debug

