SRC = .
OBJ = obj
BIN = bin
CC = g++
CFLAGS = -Wall -I./
OBJECTS = $(OBJ)/Vector.o $(OBJ)/Polygon.o $(OBJ)/main.o

all: $(OBJECTS)
	${CC} $^ -g -o ${BIN}/demo.out

# This is a general rule
${OBJ}/%.o : ${SRC}/%.cpp
	${CC} -c -g ${DEFINES} ${CFLAGS} $< -o $@

clean:
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/*.out

tags:
	ctags -R *
