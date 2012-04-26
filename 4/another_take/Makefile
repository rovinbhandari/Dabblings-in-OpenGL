SRC=. 
OBJ=.
BIN=./bin
CFLAGS=-Wall -g -I./
LFLAGS=-lm -lGL -lglut -lGLU -I/usr/X11R6/include -L/usr/X11R6/lib
OBJECTS= $(OBJ)/draw.o $(OBJ)/triangle.o $(OBJ)/matrix.o $(OBJ)/general.o $(OBJ)/view.o $(OBJ)/main.o
OUTPUT_FILE=demo.out
CC=gcc

all: $(OBJECTS) 
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJECTS) -o $(BIN)/$(OUTPUT_FILE)

${OBJ}/%.o : ${SRC}/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)/*.o
	rm -f $(OUTPUT_FILE)
