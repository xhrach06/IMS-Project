# Makefile for a program using SDL and SDL_image with source file in /src

# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++11 -Wall

# SDL flags
SDL_FLAGS := $(shell sdl2-config --cflags --libs)
SDL_IMAGE_FLAGS := -lSDL2_image

# Source file and directory
SRC_DIR := src
SOURCE := $(SRC_DIR)/main.cpp

# Output binary
OUTPUT := oil-spill

all: $(OUTPUT)

$(OUTPUT): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(SOURCE) $(SDL_FLAGS) $(SDL_IMAGE_FLAGS)

run: $(OUTPUT)
	./$(OUTPUT)

clean:
	rm -f $(OUTPUT)
