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

#ifndef CARDPILE_H_INC
#define CARDPILE_H_INC

#include <vector>

/// @brief the Suits of a card
enum Suits {
	SUIT_CLUBS,
	SUIT_DIAMONDS,
	SUIT_HEARTS,
	SUIT_SPADES,
	
	SUIT_TOTAL
};

/// @brief labels for the suits (for debugging)
static const char* Suits_Label[] {
	"SUIT_CLUBS",
	"SUIT_DIAMONDS",
	"SUIT_HEARTS",
	"SUIT_SPADES",
	
	"SUIT_TOTAL"
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

/// @brief Labels for the ranks
static const char* Ranks_Label[] {
	"RANK_ACE",
	"RANK_2",
	"RANK_3",
	"RANK_4",
	"RANK_5",
	"RANK_6",
	"RANK_7",
	"RANK_8",
	"RANK_9",
	"RANK_10",
	"RANK_JACK",
	"RANK_QUEEN",
	"RANK_KING",
	
	"RANK_TOTAL"
};

/// @brief A card
struct Card {
	Suits suit;
	Ranks rank;
};

/// @brief The card pile types
enum CardPileTypes {
	PILE_DECK,
	PILE_DISCARD,
	
	PILE_TOTAL
};

/// @brief A card pile
class CardPile {
public:
	CardPile(CardPileTypes type);
	~CardPile();
	
	void shuffle(); ///< Suffle the deck
	
	Card* getACard(); ///< Pulls a card from the deck
private:
	std::vector<Card*> pile; ///< the deck/pile of cards
	CardPileTypes type;      ///< type of CardPile
};

#endif