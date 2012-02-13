SRC=. 
OBJ=.
LIB_OBJ=.
BIN=.
VOXEL_LIB_PATH = ../../1/voxel+octree\ implementation/
CFLAGS = -Wall -g -I./ -I$(VOXEL_LIB_PATH)/include/
OBJECTS = $(OBJ)/blockworld_voxel.o $(OBJ)/blockworld_complex_figures.o  $(OBJ)/tree.o $(OBJ)/character.o $(OBJ)/blockworld_demo.o
LIB_BW = $(LIB_OBJ)/blockworld.o
VOXEL_LIB_OBJ = $(VOXEL_LIB_PATH)/obj/common.o $(VOXEL_LIB_PATH)/obj/voxel.o
OUTPUT_FILE=demo.out
CC=gcc

all: $(VOXEL_LIB_OBJ) lib_bw $(OBJECTS) 
	$(CC) $(CFLAGS) $(VOXEL_LIB_OBJ) $(LIB_BW) $(OBJECTS) -o $(BIN)/$(OUTPUT_FILE) -lGL -lglut -lGLU -lm -I/usr/X11R6/include -L/usr/X11R6/lib

lib_bw: $(LIB_BW)

$(VOXEL_LIB_PATH)/obj/%.o:
	make -C $(VOXEL_LIB_PATH) lib_voxel

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -f $(OBJ)/*.o
	rm -f $(OUTPUT_FILE)
