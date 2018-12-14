#MAKEFILE

CC=g++
CFLAGS= -std=c++11 -pedantic -Wall -Wextra -g

# Links together files needed to create executables
skipbo: main.o SkipBoGame.o Player.o DrawPile.o Pile.o Card.o Hand.o FaceUpPile.o
	$(CC) -o skipbo main.o SkipBoGame.o Player.o DrawPile.o Pile.o Card.o Hand.o FaceUpPile.o

# Compiles main.cpp to create main.o
main.o: main.cpp SkipBoGame.h
	$(CC) $(CFLAGS) -c main.cpp

# Compiles SkipBoGame.cpp to create SkipBoGame.o
SkipBoGame.o: SkipBoGame.cpp Player.h DrawPile.h BuildPile.h
	$(CC) $(CFLAGS) -c SkipBoGame.cpp

# Compiles Player.cpp to create Player.o
Player.o: Player.cpp Player.h DrawPile.h FaceUpPile.h Hand.h
	$(CC) $(CFLAGS) -c Player.cpp

# Compiles DrawPile.cpp to create DrawPile.o
DrawPile.o: DrawPile.cpp DrawPile.h Pile.h Card.h
	$(CC) $(CFLAGS) -c DrawPile.cpp

# Compiles FaceUpPile.cpp to create FaceUpPile.o
FaceUpPile.o: FaceUpPile.cpp FaceUpPile.h DrawPile.h Pile.h
	$(CC) $(CFLAGS) -c FaceUpPile.cpp

# Compiles Pile.cpp to create Pile.o
Pile.o: Pile.cpp Pile.h Card.h
	$(CC) $(CFLAGS) -c Pile.cpp

# Compiles Hand.cpp to create Hand.o
Hand.o: Hand.cpp Hand.h Pile.h DrawPile.h
	$(CC) $(CFLAGS) -c Hand.cpp

# Compiles Card.cpp to create Card.o
Card.o: Card.cpp Card.h
	$(CC) $(CFLAGS) -c Card.cpp


# Removes all object files and the executables,
# so we can start fresh
clean:
	rm -f *.o skipbo
