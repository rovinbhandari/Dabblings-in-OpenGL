SRC=. 
OBJ=.
LIB_OBJ=.
BIN=.
CFLAGS=-Wall -g -I./
OBJECTS= $(OBJ)/Cuboid.opp $(OBJ)/GouraudShading.opp $(OBJ)/driver.opp
OUTPUT_FILE=driver.outpp
CC=g++

all: clean $(OBJECTS) 
	$(CC) $(CFLAGS) $(LIB_BW) $(OBJECTS) -o $(BIN)/$(OUTPUT_FILE)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -f $(OBJ)/*.opp
	rm -f $(OUTPUT_FILE)
