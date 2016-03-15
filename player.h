#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <ctime>
#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;
#include <vector>

#define DEPTH (2)

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMoveHeuristic(Move *opponentsMove, vector<Move *> moves);
    Move *doMoveMinMax(Move *opponentsMove, vector<Move *> moves);
    Move *doMove(Move *opponentsMove, int msLeft);
    Move *doMoveRandom(Move *opponentsMove, int msLeft);
    double heuristicScore(Move *move, Board *b, Side sde);
    double negaAB(int depth, int alpha, int beta);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Side opponentSide;
    Board * board;
    Side side;
};

#endif
