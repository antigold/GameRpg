CXX = g++
INCLUDES = -Iheaders -IC:/msys64/ucrt64/include/SDL2
CXXFLAGS = -g -Wall -std=c++17 -fdiagnostics-color=always $(INCLUDES)
LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -mwindows -lSDL2_ttf -lSDL2_image
LIBDIRS = -LC:/msys64/ucrt64/lib

SRCS = src/main.cpp src/game_function.cpp src/board.cpp src/classes.cpp src/entity_spawn.cpp src/player.cpp src/combat.cpp src/stats.cpp src/mob.cpp src/inventory.cpp src/entity.cpp src/algorithms.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = game.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LIBDIRS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q $(OBJS) $(TARGET)
