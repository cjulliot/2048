CC = g++
CFLAGS = -Wall -std=c++11
LIBS = -lncurses

C_FILES = src/2048.cpp src/Game.cpp

all: 2048

2048: $(C_FILES)
	@mkdir -p bin
	$(CC) $(CFLAGS) $^ -o bin/$@ $(LIBS)

clean:
	@$(RM) -r bin/
	
