/* 
 * Copyright (c) 2017 The Gupta Empire - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by Aryan Gupta <me@theguptaempire.net>
 * 
 * =============================================================================
 * @author 			Aryan Gupta
 * @project 		
 * @title 			
 * @date			(YYYY-MM-DD)
 * @fversion		1.0.0
 * @description 	
 * =============================================================================
 */

#ifndef PLAYER_H_INC
#define PLAYER_H_INC

#include <vector>

/// @brief The different types of melds
enum MeldTypes {
	MELD_SETS,
	MELD_RUNS,
	
	MELD_TOTAL,
	MELD_NONE
};

/// @brief A complete meld
struct Meld {
	MeldTypes type;
	std::vector<Card*> cards;
};

/// @brief A player on the board
class Player {
public:
	Player(bool isUser = false);
	
	std::vector<Meld> getMelds();
	void takeCard(Card* card);
	void doTurn();
private:
	std::vector<Card*> hand;
	
	bool isUser;
};

#endif