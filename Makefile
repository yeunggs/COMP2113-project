# Makefile for the Buckshot Roulette game

# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Source files
SOURCES = main.cpp Declared_functions.cpp Double_Player.cpp Single_Player.cpp
# Output executable name
OUTPUT = game

# Object files derived from source files
OBJECTS = $(SOURCES:.cpp=.o)

# Compile all source files
all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(OBJECTS)

# Rule to compile each .cpp file to .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OUTPUT) $(OBJECTS)
