#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "side.h"

class Board {
public:
    Board(int nHoles, int nInitialBeansPerHole);
    int holes() const;
    int beans(Side s, int hole) const;
    int beansInPlay(Side s) const;
    int totalBeans() const;
    bool sow(Side s, int hole, Side& endSide, int& endHole);
    bool moveToPot(Side s, int hole, Side potOwner);
    bool setBeans(Side s, int hole, int beans);
private:
    std::vector<int> northSide, southSide;
    int numHoles;
    void printBeans() const;
    std::vector<int> getSide(Side s) const;
};

#endif

/*
Board(int nHoles, int nInitialBeansPerHole);
int holes() const;
int beans(Side s, int hole) const;
int beansInPlay(Side s) const;
int totalBeans() const;
bool sow(Side s, int hole, Side& endSide, int& endHole);
bool moveToPot(Side s, int hole, Side potOwner);
bool setBeans(Side s, int hole, int beans);
*/