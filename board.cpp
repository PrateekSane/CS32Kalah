#include <iostream>
#include "board.h"
#include "side.h"
using namespace std;

/*
Construct a Board with the indicated number of holes per side (not counting the pot) and 
initial number of beans per hole. If nHoles is not positive, act as if it were 1;
if nInitialBeansPerHole is negative, act as if it were 0. 
*/
Board::Board(int nHoles, int nInitialBeansPerHole) { 
    // if nHoles or nInitialBeansPerHole are negative reset value 
    nInitialBeansPerHole = max(nInitialBeansPerHole, 0);
    nHoles = max(nHoles, 1);

    // make the vectors of size 1 (pot) + nHoles
    southSide.resize(nHoles + 1, nInitialBeansPerHole);
    northSide.resize(nHoles + 1, nInitialBeansPerHole); 

    // initialize pots to 0
    southSide[0] = 0;
    northSide[0] = 0;

    numHoles = nHoles;
}

/*
Return the number of holes on a side (not counting the pot). 
*/
int Board::holes() const {
    return numHoles;
}

/*
Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid. 
*/
int Board::beans(Side s, int hole) const {
    if (hole < 0 || hole > numHoles)
        return -1; 

    return getSide(s)[hole];
}

/*
Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot. 
*/
int Board::beansInPlay(Side s) const {
    vector<int> cur_side = getSide(s);
    int sum = 0;
    for (int i = 1; i < cur_side.size(); i++) {
        sum += cur_side[i];
    }

    return sum;
}


/*
Return the total number of beans in the game, including any in the pots. 
*/
int Board::totalBeans() const {
    return beansInPlay(NORTH) + beansInPlay(SOUTH);
}

/*
If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. 
Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise,
including s's pot if encountered, but skipping s's opponent's pot.
The function sets the parameters endSide and endHole to the side and hole where the last bean was placed.
*/
bool Board::sow(Side s, int hole, Side& endSide, int& endHole) {
    Side cur_side = s;
    if (beans(s, hole) < 0)
        return false;

    int beanCount = beans(s, hole);

    if (s == NORTH) northSide[hole] = 0;
    else southSide[hole] = 0; 

    int i = hole + 1;
    while (beanCount > 0) {
        if (cur_side == NORTH) {
            for (; i <= numHoles + 1; i++) {
                if (beanCount == 0) 
                {
                    endSide = cur_side;
                    endHole = i - 1;
                    break;
                } 
                else if (i == numHoles + 1) {
                    if (s != NORTH) break;

                    northSide[0] += 1;
                    if (beanCount == 1) {
                        endHole = 0;
                        endSide = s;
                    }
                }
                else {
                    northSide[i] += 1;
                }
                beanCount--;
            }
        }
        else {
            for (; i <= numHoles + 1; i++) {
                if (beanCount == 0) 
                {
                    endSide = cur_side;
                    endHole = i - 1;
                    break;
                } 
                else if (i == numHoles + 1) {
                    if (s != SOUTH) break;

                    southSide[0] += 1;
                    if (beanCount == 1) {
                        endHole = 0;
                        endSide = s;
                    }
                }
                else {
                    southSide[i] += 1;
                }
                beanCount--;
            }
        }

        if (beanCount > 0) {
            cur_side = opponent(cur_side);
            i = 1;
        }
    }

    return true;
}

void Board::printBeans() const {
    for (int i = 0; i < northSide.size(); i++)
        cout << northSide[i] << " ";
    cout << "s: ";
    for (int i = 1; i < southSide.size(); i++)
        cout << southSide[i] << " ";
    cout << southSide[0] << endl;
    
}

/*
If the indicated hole is invalid or a pot, return false without changing anything.
Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true. 
*/
bool Board::moveToPot(Side s, int hole, Side potOwner) {
    if (hole <= 0 || hole > numHoles) return false;
    
    if (s == NORTH) {
        if (potOwner == NORTH) 
            northSide[0] += northSide[hole];
        else
            southSide[0] += northSide[hole];
        northSide[hole] = 0;
    }
    else {
        if (potOwner == NORTH) 
            northSide[0] += southSide[hole];
        else
            southSide[0] += southSide[hole];
        southSide[hole] = 0;
    }
    return true;
}

/*
If the indicated hole is invalid or beans is negative, this function returns false without changing anything.
Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. 
This function exists solely so that we and you can more easily test your program: 
    None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. 
*/
bool Board::setBeans(Side s, int hole, int beans) {
    if (this->beans(s, hole) < 0) return false;

    if (s == NORTH)
        northSide[hole] = beans;
    else 
        southSide[hole] = beans;

    return true;
}

vector<int> Board::getSide(Side s) const {
    if (s == NORTH) {
        return northSide;
    }
    return southSide;
}