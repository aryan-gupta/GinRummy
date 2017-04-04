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
#include "info.h"

#include <algorithm>

#include ".\inc\main.h"
#include ".\inc\CardPile.h"


CardPile::CardPile(CardPileTypes type) {
	if(type == PILE_DECK) {
		for(Suits i = 0; i < SUIT_TOTAL; ++i)
			for(Suits j = 0; j < CARDS_TOTAL; ++j)
				pile.push_back( new Card{i, j} ); // create cards with combinations of Suits and Cards
	}
	
	this->type = type;
}

void CardPile::shuffle() {
	std::random_suffle(pile.begin(), pile.end());
}

Card* getACard() {
	if(pile.size() == 0) // If pile is empty, return null
		return nullptr;
	
	Card* tmpCard = pile[0]; // get first card
	pile.erase(pile.begin()); // erase it
	return tmpCard; // return the card
}