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
SRC_LIST = $(SRC_DIR)/FastaConverter.cpp
OBJ_LIST = $(subst $(SRC_DIR),$(BUILD_DIR),$(SRC_LIST:.cpp=.o))

.PHONY: compile clean

compile: $(TARGET_LIB)
	@$(CC) $(CFLAG) -o $(BIN_DIR)/$(PROG_NAME) src/main.cpp $(LIB_DIR)/$(TARGET_LIB)

# Enumerating of every *.cpp as *.o and using that as dependency
$(TARGET_LIB): $(OBJ_LIST)
	@ar -r -o $(LIB_DIR)/$@ $^

#Compiling every *.cpp to *.o
$(OBJ_LIST): $(SRC_LIST) dirmake
	@$(CC) -c $(CFLAGS) -o $@  $<

dirmake:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(LIB_DIR)

clean:
	rm -f $(BUILD_DIR)/*.o $(LIB_DIR)/$(TARGET_LIB) $(BIN_DIR)/$(PROG_NAME)
