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
};/// @brief The values of a card

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

enum CardPileTypes {
	PILE_DECK,
	PILE_DISCARD,
	
	PILE_TOTAL
};

class CardPile {
public:
	CardPile(CardPileTypes type);
	~CardPile();
	
	void shuffle();
	
	Card* getACard();
private:
	std::vector<Card*> pile;
	CardPileTypes type;
};

#endif