#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "player.h"
#include "side.h"

class Game {
public:
    Game(const Board& b, Player* south, Player* north);
    void display() const;
    void status(bool& over, bool& hasWinner, Side& winner) const;
    bool move(Side s);
    void play();
    int beans(Side s, int hole) const;
private:
    Board board;
    Player* p_south;
    Player* p_north;
    Side to_move;
};

/*
Game(const Board& b, Player* south, Player* north);
void display() const;
void status(bool& over, bool& hasWinner, Side& winner) const;
bool move(Side s);
void play();
int beans(Side s, int hole) const;
*/
#endif