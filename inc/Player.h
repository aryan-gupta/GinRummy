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
	MeldTypes type;           ///< Type of meld \sa MeldTypes
	std::vector<Card*> cards; ///< The cards that are part of the meld
};

extern const int MCARD_W;
extern const int MCARD_H;

/// @brief A player on the board
class Player {
public:
	Player(bool isUser = false);
	~Player(); /// Default destructor
	
	/// @brief Finds meld in player's hand
	void getMelds();
	
	/// @brief Take a specific card
	/// @param[in] card `Card*` The card that user should take
	void takeCard(Card* card);
	
	void doTurn(); ///< Does a turn for the player
	void render();
private:
	std::vector<Card*> hand;  ///< Stores the cards in the Player's hand
	std::vector<Meld*> melds; ///< Stores the melds
	bool isUser; ///> Is the Player a user
	
	void printHand();      ///< Print the hand out
	void renderCards();    ///< Render all the cards
	void renderDeadwood(); ///< Render deadwood
	void renderMelds();    ///< Render melds
	
	void moveCard(Card* c, int idx); /// Move a card in your hand
	
	void pickDeck(); ///< Pick a deck to draw from
	void pickCard(); ///< Pick a card to put into discard
};

#endif