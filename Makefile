CC = g++
CFLAGS = -Iinclude -Isrc -std=c++17 -Wall -Wextra
SRC = src/main.cpp \
      src/game/Board.cpp \
      src/game/Game.cpp \
      src/game/Player.cpp \
      src/network/NetworkManager.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean