CC = g++
CFLAGS = -Iinclude -std=c++17 -Wall -Wextra
SRC = src/main.cpp \
      src/game/Board.cpp \
      src/game/Game.cpp \
      src/game/Player.cpp \
      src/network/Server.cpp \
      src/network/Client.cpp \
      src/network/NetworkManager.cpp \
      src/ui/ConsoleUI.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = tic-tac-toe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean