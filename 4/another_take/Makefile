SRC=. 
OBJ=.
BIN=.
CFLAGS= -I./
LFLAGS=-lm -lGL -lglut -lGLU -I/usr/X11R6/include -L/usr/X11R6/lib
OBJECTS= $(OBJ)/renderingfunctions.o $(OBJ)/Triangle.o $(OBJ)/matrixmanipulation.o $(OBJ)/Vertex.o $(OBJ)/driver.o
OUTPUT_FILE=demo.out
CC=gcc

all: $(OBJECTS) 
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJECTS) -o $(BIN)/$(OUTPUT_FILE)

${OBJ}/%.o : ${SRC}/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)/*.o
	rm -f $(OUTPUT_FILE)
