all:
	g++ -o mancala main.cpp board.cpp game.cpp player.cpp
	./mancala

install:
	g++ -o mancala main.cpp board.cpp # game.cpp player.cpp
