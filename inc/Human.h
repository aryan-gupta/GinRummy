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

#ifndef HUMAN_H_INC
#define HUMAN_H_INC

#include "./Player.h"

class Human : public Player {
public:
	Human() {};
	virtual ~Human() {};
	
	virtual void doTurn(); ///< Does a turn for the player
	virtual void render(); ///< Render the Player
	
protected:
	virtual void renderCards();  ///< Render all the cards
	virtual void pickDeck();     ///< Pick a deck to draw from
	virtual void pickCard();     ///< Pick a card to put into discard
	virtual void renderLayoff(); ///< Render the cards as layoff
	
private:	
	void renderDeadwood(); ///< Render deadwood
	void renderMelds();    ///< Render melds
	
	void moveCard(Card* c, int idx); /// Move a card in your hand
};

#endif