# Files to compile
SRC = animatedSprite.cpp main.cpp Keyboard.cpp Player.cpp Sprite.cpp Game.cpp

# Compiler
CC = g++

# Compiler flags
# -w =  supress warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS
# -lsSDL2 for SDL2
LINKER_FLAGS = -lSDL2

# Name of the resulting file
EXEC = bin/vidya

# Compile stuff
all : $(SRC)
	@echo "Compiling vidya"
	$(CC) $(SRC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXEC)
	@echo "\nMoving resources to bin"
	cp -r res bin
	cp SDL2.dll bin

# Kind cleaning lady
.PHONY: clean
clean:
	@echo "Hi, I'm here to clean up your project!"
	rm -rf *.o
	rm -rf bin/*
