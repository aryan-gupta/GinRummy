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

enum Players {
	PLAYER_1, ///< Player 1
	PLAYER_2, ///< Player 2
	
	PLAYER_TOTAL ///< Total Players
};

/// @brief A complete meld
struct Meld {
	MeldTypes type;           ///< Type of meld /sa MeldTypes
	std::vector<Card*> cards; ///< The cards that are part of the meld
};

extern const int MCARD_W; ///< Width of the mini cards
extern const int MCARD_H; ///< Height of the mini cards

/// @brief A abstract class for each player on the board
class Player {
public: 
	Player() : hand({}), deadwood({}), melds({}) {};
	virtual ~Player(); /// Default destructor
	
	/// @brief Take a specific card
	/// @param [in] card - The card that user will take
	void takeCard(Card* card);
	
	/// @brief Gets the number of points we have at the end of the game
	/// @return unsigned the number of points
	unsigned getPoints();
	
	/// @brief checks if we can knock
	/// @return bool if we can knock
	bool canWeKnock();
	
	/// @brief Get the amount of deadwood we have
	/// @return unsigned the number of deadwood
	unsigned getNumDeadwood();
	
	virtual void doTurn()       = 0; ///< Does a turn
	virtual void render()       = 0; ///< Renders the Player on the screen
	virtual void renderLayoff() = 0; ///< Render Layoff
	
protected:
	std::vector<Card*> hand;     ///< Stores the cards in the Player's hand
	std::vector<Card*> deadwood; ///< Stores the melds
	std::vector<Meld*> melds;    ///< Stores the melds
	
	/// @brief gets a specific card from the hand
	/// @warning removes the card from the hand
	/// @param [in] card - The card pointer to remove
	/// @return The card pointer we removed
	Card* getCard(Card* card); 
	
	void getMelds();    ///< Finds meld in player's hand
	void getDeadwood(); ///< Finds the deadwood in the hand

	
	virtual void renderCards() = 0; ///< Render the cards
	virtual void pickDeck()    = 0; ///< Pick a deck to pick a Card from
	virtual void pickCard()    = 0; ///< Pick a Card to put back in the discard
	
private:
	/// @brief Check if we have a Gin
	/// @return unsigned the points from a Gin
	unsigned getGin();
	
	/// @brief Check if we have Big Gin
	/// @return unsigned the points from a Big Gin
	unsigned getBigGin();
};

#endif