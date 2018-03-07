#include "player.hpp"
#include <time.h>

#define DEPTH 2
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    board = new Board();
    playerside = side;
    if(playerside == BLACK){
        opside = WHITE;
    } else {
        opside = BLACK;
    }
    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete board;
}

std::vector<Move* > *Player::getMoves(Board* b, Side side) {
    std::vector<Move* > *validmoves = new std::vector<Move*>;
    for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			Move *possiblemove = new Move(x, y);
			if(b-> checkMove(possiblemove, side)){
				validmoves->push_back(possiblemove);
			}
		}
	}
    return validmoves;
}

void Player::setBoard(Board *b) {
    board = b;
}
/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
	time_t start;
    time(&start);
	std::vector<Move *> *validmoves;
	int bestmini = -64;
	int bestindex;

	if(opponentsMove != nullptr){
			board -> doMove(opponentsMove, opside);
	}
    validmoves = getMoves(board, playerside);
	if(validmoves->size() > 0){
		for(unsigned int i = 0; i < validmoves->size(); i++){
            time_t timer;
            time(&timer);
            if (difftime(timer, start) *1000.0 > msLeft - 15000.0 && msLeft > 0)
                return (*validmoves)[0];
			Move *aruberuto = (*validmoves)[i];
            Board *nextBoard = board->copy();
            nextBoard -> doMove(aruberuto, playerside);
            int minSc = minScore(nextBoard, 1);
            minSc *= nextBoard->bonusFactor(aruberuto);
            delete nextBoard;
			if(minSc > bestmini){
				bestmini = minSc;
				bestindex = i;
			}
		}
		Move *bestmove = (*validmoves)[bestindex];
		board -> doMove(bestmove, playerside);   
		return bestmove;
	}

    return nullptr;
}

int Player::minScore(Board *b, int currDepth) {
    std::vector<Move *> *opMoves = getMoves(b, opside);
    if (testingMinimax) {
        int min = 64;
        for(unsigned int i = 0; i < opMoves->size(); i++){
            Move *m = (*opMoves)[i];

            Board *opCopy = b->copy();
            opCopy->doMove(m, opside);
            int sc = opCopy->score(playerside);
            
            if (sc <= min) {
                min = sc;
            }
            delete opCopy;
            delete m;
        }

        return min;
    } else {
        if (opMoves->size() == 0) {
            return b->score(playerside);
        }   
        if (currDepth == DEPTH) {
            int min = 64;
            for(unsigned int i = 0; i < opMoves->size(); i++){
                Move *m = (*opMoves)[i];
                Board *opCopy = b->copy();
                opCopy->doMove(m, opside);
                int sc = opCopy->score(playerside);
                if (sc <= min) {
                    min = sc;
                }
                delete opCopy;
                delete m;
            }
            return min;
        } else {
            int min = 64;
            for(unsigned int i = 0; i < opMoves->size(); i++){
                Move *m = (*opMoves)[i];
                Board* opCopy = b->copy();
                opCopy->doMove(m, opside);
                int sc = -64;
                std::vector<Move* > *nextMoves = getMoves(opCopy, playerside);
                if (nextMoves->size() == 0)
                    sc = opCopy->score(playerside);
                for(unsigned int j = 0; j < nextMoves->size(); j++){
                    Board* nextCopy = opCopy->copy();
                    nextCopy->doMove((*nextMoves)[j], playerside);
                    int minSc = minScore(nextCopy, currDepth + 1);
                    if (minSc >= sc) 
                        sc = minSc;
                    delete nextCopy;
                    delete (*nextMoves)[j];
                }
                if (sc <= min) {
                    min = sc;
                }
                delete opCopy;
                delete m;
            }

            return min;
            
        }
        
    }

}



