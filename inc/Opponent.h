/* 
 * Copyright (c) 2017 The Cool Group - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by:
 * Harrison Read <hread2@uncc.edu>
 * Pichsapa Kulapruk <pkulapru@uncc.edu>
 * Aryan Gupta <agupta40@uncc.edu>
 * 
 * =============================================================================
 * @author 			The Cool Group
 * @project 			GinRummy 		
 * @title 			
 * @date			(YYYY-MM-DD)
 * @fversion		1.0.0
 * @description 	
 * =============================================================================
 */

#ifndef OPPONENT_H_INC
#define OPPONENT_H_INC

#include "./Player.h"

class Opponent : public Player {
public:
	Opponent() { turnCounter = 0; };
	virtual ~Opponent() {};

	virtual void doTurn(); ///< Does a turn for the player
	virtual void render();

protected:
	virtual void renderCards();    ///< Render all the cards
	virtual void pickDeck();
	virtual void pickCard();
	virtual void renderLayoff();
	
private: /// @todo make next two functions virtual functions
	int turnCounter; 
	static bool testMeld(const std::vector<Card*>& cards);
	
};

#endif