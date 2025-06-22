CXX = g++
INCLUDES = -Iheaders -IC:/msys64/ucrt64/include/SDL2
CXXFLAGS = -g -Wall -std=c++17 -fdiagnostics-color=always $(INCLUDES)
LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -mwindows -lSDL2_ttf
LIBDIRS = -LC:/msys64/ucrt64/lib

SRCS = src/Main.cpp src/GameFunction.cpp src/GameBoard.cpp src/Entity.cpp src/EntitySpawn.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = game.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LIBDIRS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q $(OBJS) $(TARGET)
