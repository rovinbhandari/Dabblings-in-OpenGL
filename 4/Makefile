SRC = .
OBJ = obj
BIN = bin
CC = g++
CFLAGS = -Wall -I./
OBJECTS = $(OBJ)/Vector.o $(OBJ)/Polygon.o $(OBJ)/pipelineFunctions.o $(OBJ)/main.o
OBJECTS_BRESENHAM = ${OBJ}/Vector.o ${OBJ}/Polygon.o ${OBJ}/BresenhamAlgorithm.o ${OBJ}/bresenhamdriver.o
LINK_BRESENHAM = -lGLU -lGL -lglut -lm

all: $(OBJECTS)
	${CC} $^ -g -o ${BIN}/demo.out -lm

bresenham: ${OBJECTS_BRESENHAM}
	${CC} $^ ${LINK_BRESENHAM} -o ${BIN}/bresenhamdriver.out

# This is a general rule
${OBJ}/%.o : ${SRC}/%.cpp
	${CC} -c -g ${DEFINES} ${CFLAGS} $< -o $@

clean:
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/*.out

tags:
	ctags -R *
