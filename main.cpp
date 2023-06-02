#include <iostream>
#include "board.h"
#include "game.h"
#include "player.h"
#include "side.h"

using namespace std;
void testBoard() {
    Board mBoard1(3, 1);
    assert(mBoard1.holes() == 3);
    assert(mBoard1.beans(NORTH, 0) == 0);
    assert(mBoard1.beans(NORTH, -1) == -1);
    assert(mBoard1.beans(NORTH, 3) == 1);
    assert(mBoard1.beans(NORTH, 4) == -1);
    assert(mBoard1.beansInPlay(NORTH) == 3);
    assert(mBoard1.totalBeans() == 6);

    Side endSide;
    int endHole;
    Board mBoard2(3, 1);
    // check bounds on the hole
    assert(!mBoard2.sow(NORTH, -1, endSide, endHole) && !mBoard2.sow(NORTH, 4, endSide, endHole));
    // check sow over your pot to opponent side
    assert(mBoard2.sow(NORTH, 2, endSide, endHole));
    assert(endHole == 3 && endSide == NORTH);
    assert(mBoard2.beans(NORTH, endHole) == 2);
    assert(mBoard2.sow(NORTH, 3, endSide, endHole));
    assert(endHole == 1 && endSide == SOUTH);
    assert(mBoard2.beans(NORTH, 0) == 1 && mBoard2.beans(SOUTH, 1) == 2);
    
    Board mBoard3(3, 1);
    // check sow ending in pot
    assert(mBoard3.sow(NORTH, 3, endSide, endHole));
    assert(endHole == 0 && endSide == NORTH);
    assert(mBoard3.beans(NORTH, endHole) == 1);

    Board mBoard4(3, 5);
    // check sow going over opponent side and back
    assert(mBoard4.sow(NORTH, 3, endSide, endHole));
    assert(endHole == 1 && endSide == NORTH);
    assert(mBoard4.beans(NORTH, 1) == 6 && mBoard4.beans(NORTH, 0) == 1 && mBoard4.beans(SOUTH, 0) == 0 && mBoard4.beans(SOUTH, 1) == 6);
    // check moveToPot
    assert(!mBoard4.moveToPot(NORTH, 0, SOUTH) && !mBoard4.moveToPot(NORTH, 4, SOUTH));
    assert(mBoard4.moveToPot(NORTH, 1, SOUTH));
    assert(mBoard4.beans(NORTH, 1) == 0 && mBoard4.beans(SOUTH, 0) == 6);
    assert(mBoard4.moveToPot(SOUTH, 1, NORTH));
    assert(mBoard4.beans(SOUTH, 1) == 0 && mBoard4.beans(NORTH, 0) == 7);
}

void testGame() {

}

void testPlayer() {

}

int main(void) {
    testBoard();
    Board board(2, 1);
    Player* p1 = new HumanPlayer("A");
    Player* p2 = new SmartPlayer("B");
    Game game(board, p1, p2);
    game.play();
    return 0;
}