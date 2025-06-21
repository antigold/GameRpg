# Makefile pour MSYS2 + SDL2

CXX = g++
CXXFLAGS = -g -Wall -std=c++17 -fdiagnostics-color=always
LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -mwindows -lSDL2_ttf
INCLUDES = -IC:/msys64/ucrt64/include/SDL2
LIBDIRS = -LC:/msys64/ucrt64/lib

SRCS = src/Main.cpp src/GameFunction.cpp src/GameBoard.cpp src/Entity.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = game.exe

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(INCLUDES) $(LIBDIRS) $(LDFLAGS)

clean:
	del /Q $(TARGET)
