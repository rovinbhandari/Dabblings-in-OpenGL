SRC=. 
OBJ=.
LIB_OBJ=.
BIN=.
CFLAGS=-Wall -g -I./
OBJECTS= $(OBJ)/main.o
LIB_VOXEL= $(LIB_OBJ)/voxel.o
OUTPUT_FILE=test.out
CC=gcc

all: lib_voxel $(OBJECTS) 
	$(CC) $(CFLAGS) $(LIB_VOXEL) $(OBJECTS) -o $(BIN)/$(OUTPUT_FILE) -lGL -lglut -lGLU -lm -I/usr/X11R6/include -L/usr/X11R6/lib

lib_voxel: $(OBJ)/voxel.o

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm $(OBJ)/*.o

