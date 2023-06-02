#include <iostream>
#include <string>
#include "game.h"

/*
Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first. 
*/
Game::Game(const Board& b, Player* south, Player* north): board(b), to_move(SOUTH) {
    p_north = north;
    p_south = south;
}

/*
Display the game's board in a manner of your choosing, provided you show the names of the players and a
reasonable representation of the state of the board. 
*/
void Game::display() const {
    int north_pot = board.beans(NORTH, 0);
    std::cout <<  north_pot << ' ';
    for (int i = board.holes(); i > 0; i--) {
        std::cout << board.beans(NORTH, i) << ' ';
    }
    std::string spaces(std::to_string(north_pot).length(), ' ');
    std::cout << "\n " << spaces;

    for (int i = 0; i < board.holes(); i++) {
        std::cout << board.beans(SOUTH, i + 1) << ' ';
    }
    std::cout << board.beans(SOUTH, 0) << '\n' <<  std::endl;
}

/*
If the game is over (i.e., the move member function has been called and returned false), set over to true; 
otherwise, set over to false and do not change anything else. If the game is over, 
set hasWinner to true if the game has a winner, or false if it resulted in a tie. 
If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side. 
*/
void Game::status(bool& over, bool& hasWinner, Side& winner) const {
    if (board.beansInPlay(NORTH) != 0 || board.beansInPlay(SOUTH) != 0) {
        over = false;
        return;
    }
    over = true;

    int north_pot = board.beans(NORTH, 0);
    int south_pot = board.beans(SOUTH, 0);
    if (north_pot == south_pot) {
        hasWinner = false;        
    }
    else {
        hasWinner = true;
        winner = north_pot > south_pot ? NORTH : SOUTH;
    }
}

/*
Attempt to make a complete move for the player playing side s. 
"Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. 
Whenever the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening. 
If the move can be completed, return true; if not, because the move is not yet completed but side s has no holes with beans to pick up and sow,
sweep any beans in s's opponent's holes into that opponent's pot and return false. 
*/
bool Game::move(Side s) {
    bool complete = false;
    bool redisplay = false;
    while (!complete) {
        if (board.beansInPlay(s) == 0) {
            int count = 0;
            Side op = opponent(s);
            for (int i = 0; i < board.holes(); i++) {
                board.moveToPot(op, i, op);    
            }
            return false;
        }
        if (redisplay) 
            display();

        Side end_side;
        int end_hole;
        int next_move = to_move == NORTH ? p_north->chooseMove(board, to_move) : p_south->chooseMove(board, to_move);
        if (!board.sow(s, next_move, end_side, end_hole))
            continue;

        if (end_hole == 0 && board.beansInPlay(s) > 0) {
            redisplay = true;
            continue;
        }

        if (end_side == s && board.beans(s, end_hole) == 1 && board.beans(opponent(s), end_hole) > 0) {
            board.moveToPot(s, end_hole, s);
            board.moveToPot(opponent(s), end_hole, s);
        }

        complete = true;
    } 

    return true;
}

/*
Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. 
If neither player is interactive, then to keep the display from quickly scrolling through the whole game, 
it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. 
(The ignore function for input streams is useful here.) Announce the winner at the end of the game. 
You can apportion to your liking the responsibility for displaying the board between this function and the move function. 
*/
void Game::play() {
    bool over, hasWinner;
    Side winner;
    status(over, hasWinner, winner);
    while (!over) {
        display();        
        move(to_move);
        to_move = opponent(to_move);
        status(over, hasWinner, winner);
    }
    std::cout << "\nEnding Board: " << std::endl;
    display();
    if (hasWinner) {
        if (winner == NORTH)
            std::cout << "North Won!" << std::endl;
        else
            std::cout << "South Won!" << std::endl;
    }
    else {
        std::cout << "Game Tied" << std::endl;
    }
}

/*
Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. 
This function exists so that we and you can more easily test your program. 
*/
int Game::beans(Side s, int hole) const {
    return board.beans(s, hole);
}