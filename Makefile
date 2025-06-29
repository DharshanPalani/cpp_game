# Compiler
CXX = g++

# Project info
TARGET = game.exe
SRC = main.cpp

# Paths
RAYLIB_DIR = raylib
INCLUDE = -I$(RAYLIB_DIR)/include
LIBDIR = -L$(RAYLIB_DIR)/lib

# Libraries (static linking)
LIBS = $(LIBDIR) $(RAYLIB_DIR)/lib/libraylib.a -lopengl32 -lgdi32 -lwinmm

# Build rule
all:
	$(CXX) $(SRC) -o $(TARGET) $(INCLUDE) $(LIBS)

# Clean rule
clean:
	del $(TARGET)
