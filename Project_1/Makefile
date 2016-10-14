#Compiler Variables
CC = g++
CPPFLAGS = -Wall -g -std=c++11

#Location of files
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

#Update CPPFLAGS to include "include" directory
CPPFLAGS += -I $(INCLUDE_DIR)

all: twitter

twitter: $(OBJ_DIR)/twitter.o  $(OBJ_DIR)/user.o   $(OBJ_DIR)/tweet.o   $(OBJ_DIR)/datetime.o  $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -o $(BIN_DIR)/twitter  $(OBJ_DIR)/twitter.o  $(OBJ_DIR)/user.o   $(OBJ_DIR)/tweet.o   $(OBJ_DIR)/datetime.o

$(OBJ_DIR)/twitter.o: $(SRC_DIR)/twitter.cpp  $(OBJ_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/twitter.cpp -o $(OBJ_DIR)/twitter.o

$(OBJ_DIR)/user.o: $(SRC_DIR)/user.cpp  $(INCLUDE_DIR)/user.h  $(OBJ_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/user.cpp -o $(OBJ_DIR)/user.o

$(OBJ_DIR)/tweet.o: $(SRC_DIR)/tweet.cpp  $(INCLUDE_DIR)/tweet.h  $(OBJ_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/tweet.cpp -o $(OBJ_DIR)/tweet.o

$(OBJ_DIR)/datetime.o: $(SRC_DIR)/datetime.cpp  $(INCLUDE_DIR)/datetime.h  $(OBJ_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/datetime.cpp -o $(OBJ_DIR)/datetime.o

# Ensure the $(OBJ_DIR) directory exist or create it.
$(OBJ_DIR)/.dirstamp: 
	-@mkdir -p $(OBJ_DIR) && touch $(OBJ_DIR)/.dirstamp

# Ensure the $(OBJ_DIR) directory exist or create it.
$(BIN_DIR)/.dirstamp:
	-@mkdir -p $(BIN_DIR) && touch $(BIN_DIR)/.dirstamp



# Memory check rule. Depends on a fresh binary.
.PHONY: memcheck
memcheck: twitter
	valgrind --tool=memcheck --leak-check=yes ./$(BIN_DIR)/twitter

# The clean rule
.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR)/ $(BIN_DIR)/ *.feed




