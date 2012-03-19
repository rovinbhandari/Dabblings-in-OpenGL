# vi: autoindent:nu:ts=8:noexpandtab
SRC = .
OBJ = .
BIN = .
CFLAGS = -Wall -I./
OBJECTS = $(OBJ)/Cuboid.opp $(OBJ)/VectorCalculation.opp $(OBJ)/GouraudShading.opp $(OBJ)/driver.opp
OUTPUT = driver.outpp
CC = g++

all: clean $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(BIN)/$(OUTPUT) -lGL -lglut -lGLU -lm -I/usr/X11R6/include -L/usr/X11R6/lib

$(OBJ)/%.opp: $(SRC)/%.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -f $(OBJ)/*.opp
	rm -f $(OUTPUT)
