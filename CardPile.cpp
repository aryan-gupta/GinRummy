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

#include <SDL.h>
#include <algorithm>
#include <vector>
using std::vector;
#include <random>

#include ".\inc\main.h"
#include ".\inc\CardPile.h"
#include ".\inc\Window.h"
#include ".\inc\Resources.h"

const int CARD_W   = 140 *5/8;
const int CARD_H   = 190 *5/8;
const int CARD_PAD = 35  *5/8;

CardPile::CardPile(CardPileTypes type) {
	if(type == PILE_DECK) {
		for(int i = 0; i < SUIT_TOTAL; ++i)
			for(int j = 0; j < RANK_TOTAL; ++j)
				pile.push_back( new Card{(Suits)i, (Ranks)j} ); // create cards with combinations of Suits and Cards
	}
	
	this->type = type;
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
	if(type == PILE_DECK) {
		SDL_Rect pos = SDL_Rect {
			SCRN_W/2 - CARD_W - 20,
			SCRN_H/2 - CARD_H/2,
			CARD_W,
			CARD_H
		};
		
		SDL_RenderCopy(
			gWindow->getRenderer(),
			gAssets->cardBackSheet,
			&gAssets->cardClippingBack,
			&pos
		);
	} else {
		if(pile.size() != 0) {
			SDL_Rect pos = SDL_Rect {
				SCRN_W/2 + 20,
				SCRN_H/2 - CARD_H/2,
				CARD_W,
				CARD_H
			};
			
			SDL_RenderCopy(
				gWindow->getRenderer(),
				gAssets->cardsSheet,
				&gAssets->cardClippings[GCI(pile[0]->suit, pile[0]->rank)],
				&pos
			);
		}
	}
}