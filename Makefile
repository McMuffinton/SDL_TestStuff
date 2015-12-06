# Files to compile
SRC = *.cpp
SRC_PATH = src/
# Compiler
CC = g++

# Compiler flags
# -w =  supress warnings
COMPILER_FLAGS = -w -std=c++11

# LINKER_FLAGS
# -lsSDL2 for SDL2
LINKER_FLAGS = -lSDL2

# Formatting stuff
FMT = clang-format-3.5
FORMATTER_FLAGS = -style=file -i
TO_FORMAT = $(SRC_PATH)*.cpp $(SRC_PATH)*.h

# Name of the resulting file
EXEC = build/vidya

# Compile stuff
all : $(SRC_PATH SRC)
	mkdir -p build
	@echo "Compiling vidya"
	$(CC) $(SRC_PATH)$(SRC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXEC)
	@echo "\nMoving resources to bin"
	cp -r res build
	cp SDL2.dll build

run : all
	$(EXEC)

format : $(SRC_PATH SRC)
	$(FMT) $(FORMATTER_FLAGS) $(TO_FORMAT)

# Kind cleaning lady
.PHONY: clean
clean:
	@echo "Hi, I'm here to clean up your project!"
	rm -rf $(SRC_PATH)*.o
	rm -rf build/*
