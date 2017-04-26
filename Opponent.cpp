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
#include "info.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;
#include <SDL2/SDL.h>
#include <string.h>

#include "./inc/main.h"
#include "./inc/Opponent.h"
#include "./inc/CardPile.h"
#include "./inc/Window.h"
#include "./inc/Resources.h"

void Opponent::doTurn() {
	turnCounter++; 
	getMelds();    // update our melds
	getDeadwood(); // update our deadwood
	pickDeck();    // pick a deack to pick from
	
	getMelds();    // update our melds
	getDeadwood(); // update our deadwood
	pickCard();    // pick a card to discard
}


void Opponent::pickDeck() {
	Card* topcard = gDiscard->peek(); 
	bool canMeld = false; 
	
	for(unsigned i = 0; i < hand.size(); i++) { 
		for(unsigned j = i + 1; j < hand.size(); j++) { 
			// check melds i, j, and topcard 
			// if those three cards meld then turn canMeld to true 
			if(testMeld({hand[i],hand[j],topcard})) 
				canMeld = true; 				
		}
	}	
	
	if(canMeld) {
		takeCard(gDiscard->getACard()); 
	} else { 
		takeCard(gDeck->getACard()); 	
	}	
}

void Opponent::pickCard() {
	if(canWeKnock()) { // If we can knock
		// go ahead and knock 		
		gWindow->knock(PLAYER_2); 	
	}
	
	// iterator function 
	auto it = std::max_element(deadwood.begin(), deadwood.end(), 
		[](Card* a, Card* b) {
			return (a->rank*SUIT_TOTAL + a->suit) < (b->rank*SUIT_TOTAL + b->suit);
		}
	); 

	gDiscard->takeACard(getCard(*it)); 	
}


void Opponent::render() {
	renderCards();
}

void Opponent::renderCards() {
	SDL_Rect currCardPos = { // Get the first card loaction
		SCRN_W/2 - (CARD_PAD*((int)hand.size() - 1) + CARD_W)/2,
		WIN_PAD,
		CARD_W,
		CARD_H
	};
	
	for(unsigned i = 0; i < hand.size(); ++i) {
		SDL_RenderCopy( // render it
			gWindow->getRenderer(),
			gAssets->cardBackSheet,
			&gAssets->cardClippingBack,
			&currCardPos
		);
		
		currCardPos.x += CARD_PAD; // move the pos to the next card
	}
}

void Opponent::renderLayoff() {
	int cardsTWidth = 0;
	for(Meld* m : melds) cardsTWidth += m->cards.size();
	cardsTWidth -= melds.size();
	
	cardsTWidth += deadwood.size() - 1;
	
	SDL_Rect currCardPos = { // get the first card location
		SCRN_W/2 - (((int)melds.size() * (CARD_W + WIN_PAD)) + CARD_PAD*cardsTWidth + CARD_W)/2,
		WIN_PAD,
		CARD_W,
		CARD_H
	};
	
	for(Meld* m : melds) {
		for(Card* tmpCard : m->cards) {
			SDL_RenderCopy( // render it
				gWindow->getRenderer(),
				gAssets->cardsSheet,
				&gAssets->cardClippings[GCI(tmpCard->suit, tmpCard->rank)],
				&currCardPos
			);
			
			currCardPos.x += CARD_PAD; // move to the next card
		}
		
		currCardPos.x += CARD_W;
	}
	
	for(Card* tmpCard : deadwood) {
		SDL_RenderCopy( // render it
			gWindow->getRenderer(),
			gAssets->cardsSheet,
			&gAssets->cardClippings[GCI(tmpCard->suit, tmpCard->rank)],
			&currCardPos
		);
		
		currCardPos.x += CARD_PAD; // move to the next card
	}
}


bool Opponent::testMeld(const vector<Card*>& cards) {
	bool isSet = true, isRun = true;
	for(size_t i = 1; i < cards.size(); ++i) {
		if(cards[0]->rank != cards[i]->rank) 
			isSet = false;
		if(cards[0]->rank != cards[i]->rank - i)
			isRun = false;
		if(cards[0]->suit != cards[i]->suit)
			isRun = false;
	}
	
	return isSet || isRun; // mabe use xor(^) ?
}