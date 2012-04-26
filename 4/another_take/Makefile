SRC=. 
OBJ=.
OBJ=.
BIN=.
CFLAGS=-Wall -g -I./
LFLAGS=-lm -lGL -lglut -lGLU -I/usr/X11R6/include -L/usr/X11R6/lib
OBJECTS=$(OBJ)/main.o
OUTPUT_FILE=demo.out
CC=gcc

all: clean $(OBJECTS) 
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJECTS) -o $(BIN)/$(OUTPUT_FILE)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)/*.o
	rm -f $(OUTPUT_FILE)
