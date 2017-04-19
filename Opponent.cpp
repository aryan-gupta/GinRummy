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
	// for now we are picking the deck
	//takeCard(gDeck->getACard());
	
	Card* topcard = gDiscard->peek(); 
	bool canMeld = false; 
	
	for(unsigned i = 0; i < hand.size(); i++) { 
		for(unsigned j = i + 1; j < hand.size(); j++) { 
				// check melds i, j, and topcard 
				// if those three cards meld then turn canMeld to true 
				
		}
	}	
	
	if(canMeld) {
		takeCard(gDiscard->getACard()); 
	}
	else { 
		takeCard(gDeck->getACard()); 	
	}

	
}

void Opponent::pickCard() {
	// We are going to put back a random card, cause why not1
	
	if(canWeKnock()) { //  
		// go ahead and knock 
		
	}
	
	Card* topcard = gDiscard->peek(); 	
	// we have 52 cards 
	// 10 for player1 
	// 10 for computer 
	// leave 32 cards in play 
	// that's mean 16 turn that will happen until the end of the deck 
	// player has 8 turn and computer has 8 turn 
	// if turnCounter is greater than 4, then pass half of the game 
 
	if(turnCounter < 2) { 
		// put down any cards that is ranking 1 or 2 away in different suit 
		// if that is not possible then we want to discard equal rank to the top card 
	
	} 
	
	if(turnCounter < 4) { 
		// do something 
	}
	else { // we want to start dumping high card and pulling low card 
	
	}

	gDiscard->takeACard(getCard(hand[rand() % hand.size()]));
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
		SCRN_W/2 - ((melds.size() * (CARD_W + WIN_PAD)) + CARD_PAD*cardsTWidth + CARD_W)/2,
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