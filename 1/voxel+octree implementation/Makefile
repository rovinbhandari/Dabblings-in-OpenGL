SRC=. 
OBJ=.
LIB_OBJ=.
BIN=.
DEFINES=
CFLAGS=-Wall -g -I./
OBJECTS= $(OBJ)/voxel_demo.o
#LIB_VOXEL= $(LIB_OBJ)/voxel.o
#OUTPUT_FILE=test.out
LIB_VOXEL= $(LIB_OBJ)/common.o $(LIB_OBJ)/voxel.o
OCTREE_TEST_OBJ= $(OBJ)/common.o $(OBJ)/octree.o $(OBJ)/octree_demo.o
OCTREE_TEST_BIN= $(BIN)/octree_demo.out
OUTPUT_FILE=voxel_demo.out
CC=gcc

# I am not very clear what is happening here, Rajat.

all: clean lib_voxel $(OBJECTS) octree_demo
	$(CC) $(CFLAGS) $(LIB_VOXEL) $(OBJECTS) -o $(BIN)/$(OUTPUT_FILE) -lGL -lglut -lGLU -lm -I/usr/X11R6/include -L/usr/X11R6/lib

lib_voxel: $(LIB_VOXEL)

octree_demo: $(LIB_VOXEL) $(OCTREE_TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $(OCTREE_TEST_BIN) -lGL -lglut -lGLU -lm -I/usr/X11R6/include -L/usr/X11R6/lib

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(DEFINES) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/*.out
