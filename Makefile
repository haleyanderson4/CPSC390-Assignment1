BUILD_FLAGS = -W -Wall -pedantic
CC = g++
RM = rm
EXES = *.out
OBJECTS = *.o

all: main.out clean

Bacteria.o: Makefile Square.cpp
	$(CC) $(BUILD_FLAGS) -c Square.cpp -o Square.o

World.o: Makefile Game.cpp
	$(CC) $(BUILD_FLAGS) -c Game.cpp -o Game.o

main.out: Makefile Game.o Square.o main.cpp
	$(CC) $(BUILD_FLAGS) Game.o Square.o main.cpp -o main.out

clean:
	$(RM) $(OBJECTS)
