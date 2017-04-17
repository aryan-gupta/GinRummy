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

#include <SDL2/SDL.h>
#include <algorithm>
#include <vector>
using std::vector;
#include <random>

#include "./inc/main.h"
#include "./inc/CardPile.h"
#include "./inc/Window.h"
#include "./inc/Resources.h"

const int CARD_W   = 140 *5/8;
const int CARD_H   = 190 *5/8;
const int CARD_PAD = 35  *5/8;

CardPile::CardPile(CardPileTypes type) {
	if(type == PILE_DECK) {
		for(int i = 0; i < SUIT_TOTAL; ++i)
			for(int j = 0; j < RANK_TOTAL; ++j)
				pile.push_back( new Card{(Suits)i, (Ranks)j} ); // create cards with combinations of Suits and Cards
	
		position = SDL_Rect { // position of the card pile
			SCRN_W/2 - CARD_W - 20,
			SCRN_H/2 - CARD_H/2 - WIN_PAD*3,
			CARD_W,
			CARD_H
		};
		
	} else {
		position = SDL_Rect { // position
			SCRN_W/2 + 20,
			SCRN_H/2 - CARD_H/2 - WIN_PAD*3,
			CARD_W,
			CARD_H
		};
	}
	
	this->type = type;
}


CardPile::~CardPile() {
	for(Card* tmpCard : pile)
		delete tmpCard; // delete all the cards in the deck
}


size_t CardPile::size() {
	return pile.size();
}


void CardPile::takeACard(Card* card) {  // each player put card face up after get card from cardpile gdeck 
	pile.insert(pile.begin(), card); 
} 


void CardPile::shuffle() {
	std::random_shuffle(pile.begin(), pile.end());
}


Card* CardPile::getACard() {
	if(pile.size() == 0) // If pile is empty, return null
		return nullptr;
	
	Card* tmpCard = pile[0]; // get first card
	pile.erase(pile.begin()); // erase it
	return tmpCard; // return the card
}


void CardPile::render() {
	if(pile.size() == 0)
		return;
	
	if(type == PILE_DECK) {
		SDL_RenderCopy(
			gWindow->getRenderer(),
			gAssets->cardBackSheet,
			&gAssets->cardClippingBack, // render the back
			&position
		);
	} else {
		SDL_RenderCopy(
			gWindow->getRenderer(),
			gAssets->cardsSheet,
			&gAssets->cardClippings[GCI(pile[0]->suit, pile[0]->rank)], // render the top card
			&position
		);
	}
}


bool CardPile::checkClick(const int x, const int y) {
	// Check if we clicked on this card pile
	if(    x > position.x
		&& x < position.x + position.w
		&& y > position.y
		&& y < position.y + position.h
	) return true;
	
	return false;
}



Card* CardPile::peek() { 

	if(pile.size() == 0) { 
		return nullptr; 

	}
	
	return pile[0]; // return first card  
 

} 
