#include <iostream>
#include "player.h"

/*
Create a Player with the indicated name. 
*/
Player::Player(std::string name) : m_name(name) {}

/*
Return the name of the player. 
*/
std::string Player::name() const {
    return m_name;    
}

/*
    Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players. 
*/
bool Player::isInteractive() const { return false; }

/*
    Since this class is designed as a base class, it should have a virtual destructor. 
*/
Player::~Player() {}

HumanPlayer::HumanPlayer(std::string name): Player(name) { }

int HumanPlayer::chooseMove(const Board& b, Side s) const {
    int tot_holes = b.holes();
    while (true) {
        std::cout << name() << "'s turn to move. Please enter a number from 1 to " << tot_holes << std::endl;
        std::string temp;
        getline(std::cin, temp);
        int hole = stoi(temp);
        if (s == NORTH) {
            hole = tot_holes - hole + 1;
            std::cout << hole << std::endl;
        }
        if (0 < hole && hole <= tot_holes && b.beans(s, hole) > 0) 
            return hole;
    }
}

BadPlayer::BadPlayer(std::string name): Player(name) { }

int BadPlayer::chooseMove(const Board& b, Side s) const {
    for (int i = 0; i < b.holes(); i++) {
        if (b.beans(s, i) > 0) return i;
    }
    return 1;
}

SmartPlayer::SmartPlayer(std::string name): Player(name) { }

int SmartPlayer::chooseMove(const Board& b, Side s) const{
    int bestMove = -1, bestValue = -INF;
    chooseMoveHelper(b, s, true, 0, bestMove, bestValue);
    std::cout << bestMove << std::endl;
    return bestMove;
}

void SmartPlayer::chooseMoveHelper(const Board& b, Side s, bool maximizing, int depth, int& bestMove, int& value) const {
    if (b.totalBeans() == 0) {
        bool side_win = b.beans(s, 0) == b.beans(opponent(s), 0);
        if (b.beans(s, 0) == b.beans(opponent(s), 0)) {
            value = 0;
        }
        else if (side_win ^ maximizing) {
            value = -INF;
        }
        else {
            value = INF;
        }
        bestMove = -1;
        return;
    }

    if  (depth >= MAX_DEPTH) {
        bestMove = -1;
        value = evaluateBoard(b, s);
        return;
    }

    for (int i = 1; i <= b.holes(); i++) {
        if (b.beans(s, i) == 0)
            continue;
        
        Board copy(b);
        int eh, h2, v2;
        Side es;
        copy.sow(s, i, es, eh);
        chooseMoveHelper(copy, opponent(s), ~maximizing, depth + 1, h2, v2);
        if (maximizing && v2 > value || !maximizing && v2 < value) {
            bestMove = i;
            value = v2;
        }
    }
    return;
}

int SmartPlayer::evaluateBoard(const Board& b, Side s) const {
    return b.beans(s, 0) - b.beans(opponent(s), 0);
}