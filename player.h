#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include "side.h"

const int MAX_DEPTH = 7;
const int INF = INT_MAX;

class Player {
public:    
    Player(std::string name);
    std::string name() const;
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const = 0;
    virtual ~Player();

private:
    std::string m_name;
};

class HumanPlayer : public Player {
public:
    HumanPlayer(std::string name);
    int chooseMove(const Board& b, Side s) const;
    inline bool isInteractive() const { return true; }
};

class BadPlayer : public Player {
public:
    BadPlayer(std::string name);
    int chooseMove(const Board& b, Side s) const;
};

class SmartPlayer : public Player {
public:
    SmartPlayer(std::string name);
    int chooseMove(const Board& b, Side s) const;
    void chooseMoveHelper(const Board& b, Side s, bool maximizing, int depth, int& bestMove, int& value) const;
    int evaluateBoard(const Board& b, Side s) const;
};
#endif