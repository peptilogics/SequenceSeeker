CC = g++
LD = g++
CFLAG = -Wall
CFLAGS= -fPIC -O0 -g -Wall -c -fpermissive
LDFLAGS = -shared
PROG_NAME = sequence_seeker
TARGET_LIB = seq_seq.a

SRC_DIR = ./src
BUILD_DIR = ./build
BIN_DIR = ./bin
LIB_DIR = ./lib
THIRD_PARTY_DIR = ./thirdparty
SRC_LIST = $(SRC_DIR)/gzstream.cpp $(SRC_DIR)/FastaConverter.cpp
OBJ_LIST = $(subst $(SRC_DIR),$(BUILD_DIR),$(SRC_LIST:.cpp=.o))
PROG_PATH = $(BIN_DIR)/$(PROG_NAME)

.PHONY: compile clean

compile: dirmake compile_lib
	@$(CC) -O2 -o $(PROG_PATH) -std=c++2a $(BUILD_DIR)/main.o $(OBJ_LIST) -lz -I"${CONDA_PREFIX}"/include -I"${THIRD_PARTY_DIR}"/hat-trie/include

compile_lib:
	@$(CC) -c $(SRC_DIR)/gzstream.cpp -O2 -o $(BUILD_DIR)/gzstream.o
	@$(CC) -c $(SRC_DIR)/FastaConverter.cpp -O2 -o $(BUILD_DIR)/FastaConverter.o -I"${THIRD_PARTY_DIR}"/hat-trie/include
	@$(CC) -c $(SRC_DIR)/main.cpp -O2 -o $(BUILD_DIR)/main.o -I"${THIRD_PARTY_DIR}"/hat-trie/include

dirmake: $(BUILD_DIR) $(BIN_DIR) $(LIB_DIR)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(LIB_DIR)

clean:
	rm -f $(BUILD_DIR)/*.o $(LIB_DIR)/$(TARGET_LIB) $(BIN_DIR)/$(PROG_NAME)
