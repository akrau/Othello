#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side ourSide) {
    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */

    // use clock to time the constructor
    //clock_t t = clock();
    
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    side = ourSide;
    opponentSide = ((side == BLACK)? WHITE : BLACK);
    board = new Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete board;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 * 
 */
 Move *Player::doMove(Move *opponentsMove, int msLeft) 
    {
        clock_t t = clock();
        if (msLeft < 0 || (clock() - t) / CLOCKS_PER_SEC < msLeft / 1000.0)
        {

            if (opponentsMove != NULL)
            {
                board->doMove(opponentsMove, opponentSide); 
            }
            vector<Move *> moves = board->listMoves(side); //defined in board.cpp
            if(!(moves.empty()))
            {
                if(!testingMinimax)
                    return doMoveHeuristic(opponentsMove, moves);
                else
                    return doMoveMinMax(opponentsMove, moves);
            }
            else
                return NULL;
        }
        return NULL;
        
    }

/*
* This runs a simple two ply min max utilizing the naive heuristic score 
*   calculations on othello.
*/

Move *Player::doMoveMinMax(Move *opponentsMove, vector<Move *> moves)
{
    double lowestscore = -500000;
    Move * bestmove;
    vector<Move *> children;
    for(unsigned int i = 0; i < moves.size(); i++)
    {
        Board * b = board->copy();
        double lowscore = 100000;
        b->doMove(moves[i], side);
        children = b->listMoves(opponentSide);
        for(unsigned int j = 0; j < children.size(); j++)
        {
            double score = heuristicScore(children[j], b->copy(), opponentSide);
            if(score < lowscore)
                    lowscore = score;
        }
        if(lowscore > lowestscore)
        {        
            bestmove = moves[i]; 
            lowestscore = lowscore; 
        }
    }
	    board->doMove(bestmove, side);
        return bestmove;
}

/*
* This runs an alpha-beta negamax utilizing the naive heuristic score 
*   calculations on othello.
* Still a work in progress; might not use as the algorithm for tournament
*/

double Player::negaAB(int depth, int alpha, int beta)
{
    vector<Move *> moves = board->listMoves(side);

    if (depth == 0)
    {
        // "evaluate"?
        return heuristicScore(moves[0], board->copy(), side);
    }

    for (unsigned int i = 0; i < moves.size(); i++)
    {
        double score = -negaAB(depth - 1, -beta, -alpha);

        if (score > alpha)
        {
            alpha = score;
        }
        if (score >= beta)
        {
            break;
        }
    }

    return alpha;
}



/* 
* This runs a heuristic AI on Othello
*/
 Move *Player::doMoveHeuristic(Move *opponentsMove, vector<Move *> moves) {
            Move * bestmove = moves[0];
            double bestScore = heuristicScore(moves[0], board->copy(), side);
            for(unsigned int i = 1; i < moves.size(); i++)
            {
                double score = heuristicScore(moves[i], board->copy(), side);
                if(score > bestScore)
                {
                    bestmove = moves[i];
                    bestScore = score;
                }
            }
            board->doMove(bestmove, side);
            return bestmove;  
}

/*
* Naive heuristic function. 
*@param move = move we want to find score for
*@param b = copy of board to test moves on
*
* Function runs move on copy of board, and calculates score based on difference btwn our and 
* opponents number of pieces. There are multipliers to weight cases when a move is on
* an edge or corner, and if a move allows the opponent access to a corner, which is
* detrimental.
*
*/
double Player::heuristicScore(Move *move, Board *b, Side sde)
{
    double sum;
    b->doMove(move, sde);
    sum = b->count(side) - b->count(opponentSide);
    if(!testingMinimax) {
        if((move->getX() == 0 && move->getY() == 0) || (move->getX() == 0 && move->getY() == 7) || (move->getX() == 7 && move->getY() == 0) || (move->getX() == 7 && move->getY() == 7))
            sum += 3;
        else if(move->getX() == 0 || move->getX() == 7 || move->getY() == 0 || move->getY() == 7)
            sum += 1.5;
        Move one(0, 0);
        Move two(7, 0);
        Move three(0, 7);
        Move four(7, 7);
        if(board->checkMove(&one, opponentSide)|| board->checkMove(&two, opponentSide) || board->checkMove(&three, opponentSide) || board->checkMove(&four, opponentSide))
            sum += -3;

    }
    return sum;

}

/*
* This was the initial random AI that ran valid moves
*
*/
Move *Player::doMoveRandom(Move *opponentsMove, int msLeft) {
    
    clock_t t = clock();
    if (msLeft < 0 || (clock() - t) / CLOCKS_PER_SEC < msLeft / 1000.0)
    {
        if (opponentsMove != NULL)
        {
            board->doMove(opponentsMove, opponentSide); 
        }
        Move * move = board->findMoves(side); //defined in board.cpp
        if(move != NULL)
        {
            board->doMove(move, side);
            return move;
        }
        else
            return NULL;
    }
    return NULL;

}
