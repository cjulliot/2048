CC = g++
CFLAGS = -Wall
LIBS = -lncurses

C_FILES = src/2048.cpp src/Game.cpp

all: 2048

2048: $(C_FILES)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(LIBS) $^ -o bin/$@

clean:
	@$(RM) -r bin/
	
