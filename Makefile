# Files to compile
SRC = *.cpp
SRC_PATH = src/
SRC_FILES = $(wildcard $(SRC_PATH)$(SRC))
# Compiler
CC = g++

# Compiler flags
# -w =  supress warnings
COMPILER_FLAGS = -w -std=c++11

# LINKER_FLAGS
# -lsSDL2 for SDL2
LINKER_FLAGS = -lSDL2

# Formatting stuff
FMT = clang-format-3.6
FORMATTER_FLAGS = -style=file -i
TO_FORMAT = $(SRC_FILES) $(SRC_PATH)*.h $(wildcard $(TEST_PATH)*.cc)

# Name of the resulting file
EXEC = build/vidya

# googletest
GTEST_PATH = lib/googletest
GTEST_INCLUDE = $(GTEST_PATH)/include
GTEST_LIB = lib/libgtest.a

# Unittesting
TEST_PATH = test/
TEST_EXEC = $(TEST_PATH)unittest
TEST_MAIN = $(TEST_PATH)gtest_main.cc
TEST_FILES = $(filter-out $(SRC_PATH)main.cpp, $(SRC_FILES)) $(TEST_MAIN)
TEST_COMPILER_FLAGS = $(COMPILER_FLAGS) -isystem $(GTEST_INCLUDE) -isystem $(SRC_PATH) -pthread
TEST_LINKER_FLAGS = $(GTEST_LIB) $(LINKER_FLAGS)

# Compile stuff
all : $(SRC_PATH SRC)
	mkdir -p build
	@echo "Compiling vidya"
	$(CC) $(SRC_FILES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXEC)
	@echo "\nMoving resources to bin"
	cp -r res build
	cp lib/SDL2.dll build

run : all
	$(EXEC)

test : format
	@echo "Compiling tests"
	$(CC) $(TEST_FILES) $(TEST_COMPILER_FLAGS) $(TEST_LINKER_FLAGS) -o $(TEST_EXEC)
	@echo "running tests"
	$(TEST_EXEC)

format : $(SRC_PATH SRC)
	$(FMT) $(FORMATTER_FLAGS) $(TO_FORMAT)

# Kind cleaning lady
.PHONY: clean
clean:
	@echo "Hi, I'm here to clean up your project!"
	rm -rf $(SRC_PATH)*.o
	rm -rf build/*
