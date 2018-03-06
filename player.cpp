#include "player.hpp"
#include <vector>

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
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

	// TODO: ADD TIMER
	std::vector<Move *> validmoves;
	int bestmovevalue = -64;
	int bestindex;

	if(opponentsMove != nullptr){
		if(playerside == BLACK){
			board -> doMove(opponentsMove, WHITE);
		}
		else
			board -> doMove(opponentsMove, BLACK);
	}

	for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			Move *possiblemove = new Move(x, y);
			if(board -> checkMove(possiblemove, playerside)){
				validmoves.push_back(possiblemove);
			}
		}
	}

	if(validmoves.size() > 0){
		for(unsigned int i = 0; i < validmoves.size(); i++){
			Move *aruberuto = validmoves[i];
			if(board -> score(playerside, aruberuto) > bestmovevalue){
				bestmovevalue = board -> score(playerside, aruberuto);
				bestindex = i;
			}
		}
		Move *bestmove = validmoves[bestindex];
		board -> doMove(bestmove, playerside);
		return bestmove;
	}

    return nullptr;
}


/* Minimax outline:
 * max = -99999
 * bestMove = null;
 * for move in posibMoves:
 *     minSc = minScore(move, 99999, 1)
 *     if max < minSc:
 *          max = minSc
 *          bestMove = move
 * return bestMove
 * 
 * minScore(move, min, depth):
 * depth = 0
 * min = 99999
 * if depth < maxDepth:
 *     for pmove in posibMoves:
 *         return minScore(pmove, min, depth+1)
 * else:
 *     if score < min:
 *         return score
 * 
