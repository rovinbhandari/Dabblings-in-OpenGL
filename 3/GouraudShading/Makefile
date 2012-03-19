# vi: autoindent:nu:ts=8:noexpandtab
SRC=. 
OBJ=.
BIN=.
CFLAGS=-Wall -g -I./
OBJECTS= $(OBJ)/Cuboid.opp $(OBJ)/VectorCalculus.opp $(OBJ)/GouraudShading.opp $(OBJ)/driver.opp
OUTPUT_FILE=driver.outpp
CC=g++

all: $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o $(BIN)/$(OUTPUT_FILE)

$(OBJ)/%.opp: $(SRC)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -f $(OBJ)/*.opp
	rm -f $(OUTPUT_FILE)
