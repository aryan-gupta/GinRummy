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

// forward declaration
struct Card;

/// @brief The different types of melds
enum MeldTypes {
	MELD_SET, ///< A set type of meld (3 or 4 cards with the same rank/value)
	MELD_RUN  ///< A run type of meld (3 cards in the same suit that go in order)
};

/// @brief A complete meld
struct Meld {
	MeldTypes type;           ///< Type of meld /sa MeldTypes
	std::vector<Card*> cards; ///< The cards that are part of the meld
};

extern const int MCARD_W;
extern const int MCARD_H;

/// @brief A player on the board
class Player {
public: 

	Player() {};
	virtual ~Player(); /// Default destructor
	
	/// @brief Take a specific card
	/// @param[in] card `Card*` The card that user should take
	void takeCard(Card* card);
	
	unsigned getPoints();
	
	bool canWeKnock();
	
	virtual void doTurn() = 0;
	virtual void render() = 0;
	
protected:
	std::vector<Card*> hand;  ///< Stores the cards in the Player's hand
	std::vector<Meld*> melds; ///< Stores the melds
	std::vector<Card*> deadwood; ///< Stores the melds
	
	Card* getCard(Card* card); 
	/// @brief Finds meld in player's hand
	void getMelds();
	void getDeadwood();
	unsigned getNumDeadwood();
	
	virtual void renderCards() = 0;
	virtual void pickDeck() = 0;
	virtual void pickCard() = 0;
private:
	unsigned getGin();
	unsigned getBigGin();
};

#endif