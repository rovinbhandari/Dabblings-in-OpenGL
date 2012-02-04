SRC=. 
OBJ=.
LIB_OBJ=.
BIN=.
DEFINES=
CFLAGS=-Wall -g -I./
OBJECTS= $(OBJ)/main.o
#<<<<<<< HEAD
#LIB_VOXEL= $(LIB_OBJ)/voxel.o
#OUTPUT_FILE=test.out
#=======
LIB_VOXEL= $(LIB_OBJ)/common.o $(LIB_OBJ)/voxel.o
OCTREE_TEST_OBJ= $(OBJ)/common.o $(OBJ)/octree.o $(OBJ)/octree_test.o
OCTREE_TEST_BIN= $(BIN)/octree.test.out
OUTPUT_FILE=test.out
#>>>>>>> d6796934bb151d9f848c359d93cdb5030ffaf5ea
CC=gcc

# I am not very clear what is happening here, Rajat.

all: lib_voxel $(OBJECTS) 
	$(CC) $(CFLAGS) $(LIB_VOXEL) $(OBJECTS) -o $(BIN)/$(OUTPUT_FILE) -lGL -lglut -lGLU -lm -I/usr/X11R6/include -L/usr/X11R6/lib

lib_voxel: $(LIB_VOXEL)

octree_test: $(LIB_VOXEL) $(OCTREE_TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $(OCTREE_TEST_BIN) -lGL -lglut -lGLU -lm -I/usr/X11R6/include -L/usr/X11R6/lib

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(DEFINES) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm $(OBJ)/*.o

