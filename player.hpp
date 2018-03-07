#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    void setBoard(Board *b);
    Move *doMove(Move *opponentsMove, int msLeft);
    int minScore(Board *b, int currDepth);
    std::vector<Move* > *getMoves(Board* b, Side side);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    // the board
private:
    Board *board;
    Side playerside;
    Side opside;
};

#endif
