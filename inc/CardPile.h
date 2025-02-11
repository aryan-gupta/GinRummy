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

#ifndef CARDPILE_H_INC
#define CARDPILE_H_INC

#include <vector>

extern const int CARD_W;
extern const int CARD_H;
extern const int CARD_PAD;

/// @brief the Suits of a card
enum Suits {
	SUIT_CLUBS,
	SUIT_DIAMONDS,
	SUIT_HEARTS,
	SUIT_SPADES,
	
	SUIT_TOTAL
};

/// @brief The values of a card
enum Ranks {
	RANK_ACE,
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	RANK_9,
	RANK_10,
	RANK_JACK,
	RANK_QUEEN,
	RANK_KING,
	
	RANK_TOTAL
};

/// @brief A card
struct Card {
	const Suits suit; ///< The suit
	const Ranks rank; ///< The rank
};

/// @brief The card pile types
enum CardPileTypes {
	PILE_DECK,    ///< Stock Pile
	PILE_DISCARD, ///< Discard Pile
	
	PILE_TOTAL
};

/// @brief A card pile
class CardPile {
public:
	CardPile(CardPileTypes type);
	~CardPile();
	
	/// @brief Gets the size of the pile
	/// @return size_t The size of the pile
	size_t size();
	
	/// @brief peeks at the top of the deck. Only used by Computer
	/// @return Card at the top of the deck
	/// @sa getACard()
	Card* peek(); 
	
	void swapTypes(); ///< Swaps the type of CardPile it is
	void shuffle();   ///< Suffle the deck
	void render();    ///< Render the deck
	
	/// @brief Pulls a card from the deck
	/// @warning The card gets removed from the deck
	/// @return Card* The Card pointer
	Card* getACard();
	
	/// @brief Puts a card on the top of the deck
	/// @warning Does not check if \p is nullptr or NULL
	/// @param [in] card The Card pointer
	void takeACard(Card* card);
	
	/// @brief checks of our click was on this deck
	/// @param [in] x `int` The x coordinate of the click 
	/// @param [in] y `int` The y cordinate of the click
	bool checkClick(const int x, const int y);
	
private:
	std::vector<Card*> pile; ///< The deck/pile of cards
	CardPileTypes type;      ///< Type of CardPile
	
	SDL_Rect position; ///< Position of the deck on the screen
};

#endif