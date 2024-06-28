# Source files
SOURCES := $(wildcard *.cpp)

# Object files
OBJECTS := $(SOURCES:.cpp=.o)

# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -Wall -g


build: main.o
	g++ main.o -o main -lgtest -lgmock -pthread
	

run: build
	./main
	


# Memory check step
memory: build
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

test: build	
	./main
# Clean up
clean:
	rm -f $(OBJECTS) main

.PHONY: all build run memory clean