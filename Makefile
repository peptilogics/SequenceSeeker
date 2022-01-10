CC = g++
LD = g++
CFLAG = -Wall
CFLAGS= -fPIC -O0 -g -Wall -c -fpermissive
LDFLAGS = -shared
SEQUENCE_DB_BUILDER = sequence_db_builder
SEQUENCE_SEEKER = sequence_seeker
TARGET_LIB = seq_seq.a

SRC_DIR = ./src
BUILD_DIR = ./build
BIN_DIR = ./bin
LIB_DIR = ./lib
THIRD_PARTY_DIR = ./thirdparty
SRC_LIST = $(SRC_DIR)/gzstream.cpp $(SRC_DIR)/FastaConverter.cpp $(SRC_DIR)/SequenceLookup.cpp
OBJ_LIST = $(subst $(SRC_DIR),$(BUILD_DIR),$(SRC_LIST:.cpp=.o))
SEQUENCE_DB_BUILDER_PATH = $(BIN_DIR)/$(SEQUENCE_DB_BUILDER)
SEQUENCE_SEEKER_PATH = $(BIN_DIR)/$(SEQUENCE_SEEKER)

.PHONY: compile clean

compile: dirmake compile_lib
	@$(CC) -O2 -o $(SEQUENCE_DB_BUILDER_PATH) -std=c++2a $(BUILD_DIR)/sequence_db_builder.o $(OBJ_LIST) -lz -I"${CONDA_PREFIX}"/include -I"${THIRD_PARTY_DIR}"/hat-trie/include
	@$(CC) -O2 -o $(SEQUENCE_SEEKER_PATH) -std=c++2a $(BUILD_DIR)/sequence_seeker.o $(OBJ_LIST) -lz -I"${CONDA_PREFIX}"/include -I"${THIRD_PARTY_DIR}"/hat-trie/include

compile_lib:
	@$(CC) -c $(SRC_DIR)/gzstream.cpp -O2 -o $(BUILD_DIR)/gzstream.o
	@$(CC) -c $(SRC_DIR)/FastaConverter.cpp -O2 -o $(BUILD_DIR)/FastaConverter.o -I"${THIRD_PARTY_DIR}"/hat-trie/include
	@$(CC) -c $(SRC_DIR)/SequenceLookup.cpp -O2 -o $(BUILD_DIR)/SequenceLookup.o -I"${THIRD_PARTY_DIR}"/hat-trie/include
	@$(CC) -c $(SRC_DIR)/sequence_db_builder.cpp -O2 -o $(BUILD_DIR)/sequence_db_builder.o -I"${THIRD_PARTY_DIR}"/hat-trie/include -I"${THIRD_PARTY_DIR}"/cxxopts/include/
	@$(CC) -c $(SRC_DIR)/sequence_seeker.cpp -O2 -o $(BUILD_DIR)/sequence_seeker.o -I"${THIRD_PARTY_DIR}"/hat-trie/include -I"${THIRD_PARTY_DIR}"/cxxopts/include/

dirmake: $(BUILD_DIR) $(BIN_DIR) $(LIB_DIR)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(LIB_DIR)

clean:
	rm -f $(BUILD_DIR)/*.o $(LIB_DIR)/$(TARGET_LIB) $(BIN_DIR)/*
