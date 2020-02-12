OBJECTS = FibLFSR.o PhotoMagic.o
CFLAGS = -std=c++11 -g -Wall -Werror -pedantic
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
CC = g++

all : $(OBJECTS) PhotoMagic

FibLFSR.o : FibLFSR.hpp FibLFSR.cpp
	$(CC) $(CFLAGS) -c FibLFSR.cpp -o FibLFSR.o

PhotoMagic.o : PhotoMagic.cpp
	 $(CC) $(CFLAGS) -c PhotoMagic.cpp -o PhotoMagic.o

PhotoMagic: $(OBJECTS)
	 $(CC) $(CFLAGS) -o ps1b $(OBJECTS) -o PhotoMagic $(LFLAGS)

clean:
	rm PhotoMagic $(OBJECTS)
