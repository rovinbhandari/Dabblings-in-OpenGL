SRC         = ./src
OBJ         = ./obj
LIB_OBJ     = ./obj
BIN         = ./bin
DEFINES     =
CFLAGS      = -Wall -c -g -I./include
VOXEL_OBJ   = $(OBJ)/voxel_demo.o
LIB_VOXEL   = $(LIB_OBJ)/common.o $(LIB_OBJ)/voxel.o
OCTREE_OBJ  = $(OBJ)/octree.o $(OBJ)/octree_demo.o
OCTREE_BIN  = $(BIN)/octree_demo.out
VOXEL_BIN   = $(BIN)/voxel_demo.out
CC          = gcc

all: lib_voxel voxel_demo octree_demo

lib_voxel: $(LIB_VOXEL)

voxel_demo: $(LIB_VOXEL) $(VOXEL_OBJ)
	$(CC) $^ -o $(VOXEL_BIN) -lGL -lglut -lGLU -lm -I/usr/X11R6/include -L/usr/X11R6/lib

octree_demo: $(LIB_VOXEL) $(OCTREE_OBJ)
	$(CC) $^ -o $(OCTREE_BIN) -lGL -lglut -lGLU -lm -I/usr/X11R6/include -L/usr/X11R6/lib

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(DEFINES) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/*.out
