SRC=. 
OBJ=.
LIB_OBJ=.
BIN=.
DEFINES=
CFLAGS=-Wall -g -I./
OBJECTS= $(OBJ)/main.o
LIB_VOXEL= $(LIB_OBJ)/voxel.o
OCTREE_TEST_OBJ= $(OBJ)/octree.o $(OBJ)/octree_test.o
OCTREE_TEST_BIN= $(BIN)/octree.test
OUTPUT_FILE=test
CC=gcc

all: lib_voxel $(OBJECTS) 
	$(CC) $(CFLAGS) $(LIB_VOXEL) $(OBJECTS) -o $(BIN)/$(OUTPUT_FILE) -lGL -lglut -lGLU -lm -I/usr/X11R6/include -L/usr/X11R6/lib

lib_voxel: $(OBJ)/voxel.o

octree_test: $(OCTREE_TEST_OBJ)
	$(CC) $(CFLAGS) $(OCTREE_TEST_OBJ) -lm -o $(OCTREE_TEST_BIN)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(DEFINES) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm $(OBJ)/*.o

