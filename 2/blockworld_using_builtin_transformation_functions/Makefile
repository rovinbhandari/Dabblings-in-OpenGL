SRC=. 
OBJ=.
LIB_OBJ=.
BIN=.
CFLAGS=-Wall -g -I./
OBJECTS= $(OBJ)/blockworld_complex_figures.o  $(OBJ)/tree.o $(OBJ)/character.o $(OBJ)/blockworld_demo.o
LIB_BW= $(LIB_OBJ)/blockworld.o
OUTPUT_FILE=demo.out
CC=gcc

all: clean lib_bw $(OBJECTS) 
	$(CC) $(CFLAGS) $(LIB_BW) $(OBJECTS) -o $(BIN)/$(OUTPUT_FILE) -lGL -lglut -lGLU -lm -I/usr/X11R6/include -L/usr/X11R6/lib

lib_bw: $(LIB_BW)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -f $(OBJ)/*.o
	rm -f $(OUTPUT_FILE)
