/* 
 * Copyright (c) 2017 The Cool Group - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by:
 * Harrison Read		<hread2@uncc.edu>
 * Pichsapa Kulapruk	<pkulapru@uncc.edu>
 * Aryan Gupta			<agupta40@uncc.edu>
 * 
 * =============================================================================
 * @author 			The Cool Group
 * @project 		GinRummy 		
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
	Opponent() : Player(), turnCounter(0) {};
	virtual ~Opponent() {};

	virtual void doTurn(); ///< Does a turn for the player
	virtual void render(); ///< Renders the Opponent

protected:
	virtual void renderCards();  ///< Render all the cards
	virtual void pickDeck();     ///< Pick a deck to choose from
	virtual void pickCard();     ///< Pick a card to discard
	virtual void renderLayoff(); ///< Render laying off cards
	
private: /// @todo make next two functions virtual functions
	int turnCounter; ///< DEPRECIATED
	
	/// @brief Tests if 3 cards can make a meld.
	/// @param [in] cards a vector containing the cards to test for melds
	/// @return if it is a meld or not
	/// \p cards was made const reference so we can use a brace initializer list as an rvalue
	/// other options would include using the rvalue (&&) in the new standard, but chose
	/// as it was easier to explain
	static bool testMeld(const std::vector<Card*>& cards);
	
};

#endif