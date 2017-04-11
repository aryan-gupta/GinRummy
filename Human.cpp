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
#include "./inc/Human.h"
#include "./inc/CardPile.h"
#include "./inc/Window.h"
#include "./inc/Resources.h"


void Human::doTurn() {
	getMelds();
	getDeadwood();
	pickDeck();
	
	getMelds();
	getDeadwood();
	pickCard();
}


void Human::pickDeck() {
	gWindow->changeHelp(HTI_PICK_DECK); // Change help text
	
	bool finished = false, isMovingCard = false;
	Card* selectedCard = nullptr;
	SDL_Event event;
	
	while(!finished) { // RENDER LOOP
		gWindow->renderAll(); // render everything
		
		while(SDL_PollEvent(&event)) {
			if(isMovingCard) { // if we are moving a card
				int x, y;
				SDL_GetMouseState(&x, &y);
				
				int cardx = x - (SCRN_W/2 - (CARD_PAD*(hand.size() - 1) + CARD_W)/2); // get the x coordinate offset from the start of the cards
				int cardi = cardx / CARD_PAD; // get the index of the card we clicked
				
				// Make sure the card doesn't leave the hand
				if(cardi > (int)hand.size() - 1)
					cardi = hand.size() - 1;
				if(cardi < 0)
					cardi = 0;
				
				moveCard(selectedCard, cardi); // move the card
			}
			
			switch(event.type) {
				case SDL_QUIT:
					quit(0x01);
				break;
				
				case SDL_MOUSEBUTTONDOWN: {
					int x, y;
					SDL_GetMouseState(&x, &y);
					
					if(    x > SCRN_W/2 - (CARD_PAD*((int)hand.size() - 1) + CARD_W)/2
						&& x < SCRN_W/2 + (CARD_PAD*((int)hand.size() - 1) + CARD_W)/2
						&& y > SCRN_H - WIN_PAD - CARD_H
						&& y < SCRN_H - WIN_PAD
					)  {
						isMovingCard = true;
						int cardx = x - (SCRN_W/2 - (CARD_PAD*(hand.size() - 1) + CARD_W)/2); // get the x coordinate offset from the start of the cards
						int cardi = cardx / CARD_PAD; // get the index of the card we clicked
						
						if(cardi >= (int)hand.size()) // correct for the last card being the top card
							cardi = hand.size() - 1;
						
						selectedCard = hand[cardi];
					}
				} break;
				
				case SDL_MOUSEBUTTONUP: {
					if(isMovingCard) {
						isMovingCard = false;
						selectedCard = nullptr;
					} else {
						int x, y;
						SDL_GetMouseState(&x, &y);
						
						if(gWindow->checkKnockClick(x, y)) {
							LOGL("WE KNOCKED") /// @todo change help text
						}
						
						if(gDeck->checkClick(x, y)) {
							takeCard(gDeck->getACard()); // WE CLICKED ON THE DECK 
							finished = true; 				
						}
						
						if(gDiscard->checkClick(x, y)) {
							takeCard(gDiscard->getACard()); // WE CLICKED ON THE DISCARD
							finished = true; 
						}
						
						gWindow->changeHelp(HTI_PICK_DECK_ERR);
					}
				} break;
			}
		}
	}
}


void Human::pickCard() {
	gWindow->changeHelp(HTI_PICK_CARD);
	
	/// @todo Then we want to get the melds and organize our cards and pick a card to discard
	bool finished = false, isMovingCard = false;
	Card* selectedCard = nullptr;
	SDL_Event event;
	
	while(!finished) {
		// finished stores if we have completed the step of not,
		// in this case it is picking a deck to draw from. After we have chosen
		// a deck to draw from, finished is set true and the loop ends
		
		gWindow->renderAll(); // render everything
		
		while(SDL_PollEvent(&event)) {   // get all the events from the window
		
			if(isMovingCard) { // If we have clicked on a card and we are moving it
				int x, y;
				SDL_GetMouseState(&x, &y);
				
				int cardx = x - (SCRN_W/2 - (CARD_PAD*((int)hand.size() - 1) + CARD_W)/2); // get the x coordinate offset from the start of the cards
				int cardi = cardx / CARD_PAD; // get the index of the card we clicked
				
				// Make sure the card doesn't leave the hand
				if(cardi > (int)hand.size() - 1)
					cardi = hand.size() - 1;
				if(cardi < 0)
					cardi = 0;
				
				moveCard(selectedCard, cardi);
			}
			
			switch(event.type) {
				case SDL_QUIT: // quit if we hit the 'x' button
					quit(0x01);
				break;
				
				case SDL_MOUSEBUTTONDOWN: { // If we clicked down (Only thing here is moving the card)
					/// @todo get card that the user selected
					int x, y;
					SDL_GetMouseState( &x, &y );
					
					if(    x > SCRN_W/2 - (CARD_PAD*((int)hand.size() - 1) + CARD_W)/2
						&& x < SCRN_W/2 + (CARD_PAD*((int)hand.size() - 1) + CARD_W)/2
						&& y > SCRN_H - WIN_PAD - CARD_H
						&& y < SCRN_H - WIN_PAD
					)  {
						int cardx = x - (SCRN_W/2 - (CARD_PAD*(hand.size() - 1) + CARD_W)/2); // get the x coordinate offset from the start of the cards
						int cardi = cardx / CARD_PAD; // get the index of the card we clicked
						
						if(cardi >= (int)hand.size()) // correct for the last card being the top card
							cardi = hand.size() - 1;
						
						selectedCard = hand[cardi];
					}
				} break;
				
				case SDL_MOUSEMOTION:
					if(selectedCard != nullptr) isMovingCard = true;
				break;
				
				case SDL_MOUSEBUTTONUP: { // we clicked up, here is where we want to select the decks and what not
					/// @todo check for released the card
					if(isMovingCard) {
						isMovingCard = false;
						selectedCard = nullptr;
					} else {
						/// @todo check for button presses or picking a card, that will mean we are finished
						if( selectedCard != nullptr ) { 
							gDiscard->takeACard(getCard(selectedCard)); 
							finished = true; 
						}
					
						selectedCard = nullptr;
						
						int x, y;
						SDL_GetMouseState(&x, &y);
						
						if(gWindow->checkKnockClick(x, y)) {
							LOGL("WE KNOCKED")
						}
						
						if(gWindow->checkSortClick(x, y)) { ///@todo Swap sorting algorithms
							sort(
								hand.begin(), hand.end(),
								[](Card* a, Card* b) {
									return GCI(a->suit, a->rank) < GCI(b->suit, b->rank); // GCI convert rank and suit to number 
							}); 
						}	
						
						gWindow->changeHelp(HTI_PICK_CARD_ERR);
					}
				} break;
			}
		}
	}
}


void Human::moveCard(Card* c, int idx) {
	for(unsigned i = 0; i < hand.size(); ++i) {
		if(c == hand[i])
			hand.erase(hand.begin() + i); // remove the selected card
	}
	
	hand.insert(hand.begin() + idx, c); // move it to the new location
}


void Human::render() {
	renderCards();
	renderDeadwood();
	renderMelds();
}


void Human::renderCards() {
	// The entire card lay is going to be 140px for the top card and 40px for each
	// card behind, But we are shrinking the card by a factor of 0.25 so its 35px
	// for the top card and 10px for the sequential cards. Total of 125px
	SDL_Rect currCardPos = { // get the first card location
		SCRN_W/2 - (CARD_PAD*((int)hand.size() - 1) + CARD_W)/2,
		SCRN_H - WIN_PAD - CARD_H,
		CARD_W,
		CARD_H
	};
	
	for(Card* tmpCard : hand) {
		SDL_RenderCopy( // render it
			gWindow->getRenderer(),
			gAssets->cardsSheet,
			&gAssets->cardClippings[GCI(tmpCard->suit, tmpCard->rank)],
			&currCardPos
		);
		
		currCardPos.x += CARD_PAD; // move to the next card
	}
}


void Human::renderDeadwood() {
	/// @todo Dude I really need to do some clean up on this. It is terrible,
	/// but it works. Dont mess with it
	
	// First render the number of deadwood
	SDL_Surface* textSurface = TTF_RenderText_Blended( // Create temp Surface for text
		gAssets->nFont,
		("(" + std::to_string(getNumDeadwood()) + ")").c_str(), 
		SDL_Color{0x00, 0x00, 0x00, 0xFF}
	);
	SDL_Texture* dwTextTexture = SDL_CreateTextureFromSurface( // Convert it to a texture
		gWindow->getRenderer(),
		textSurface
	);
	SDL_Rect dwTextPos = SDL_Rect{
		WIN_PAD + 76,
		SCRN_H - MCARD_H*2 - WIN_PAD*3,
		textSurface->w, 
		textSurface->h
	}; // Text position
	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(gWindow->getRenderer(), dwTextTexture, NULL, &dwTextPos);
	SDL_DestroyTexture(dwTextTexture);
	
	vector<Card*> tmpHand(deadwood);
	sort(
		tmpHand.begin(), tmpHand.end(),
		[](Card* a, Card* b) {
			return GCI(a->suit, a->rank) < GCI(b->suit, b->rank);
		}
	);
	
	SDL_Rect clipping = SDL_Rect{0, 0, 30, 55};
	
	SDL_Rect pos = SDL_Rect{
		WIN_PAD,
		SCRN_H - MCARD_H*2 - WIN_PAD*2,
		MCARD_W,
		MCARD_H
	};
	
	for(Card* tmpCard : tmpHand) {
		clipping.x = gAssets->cardClippings[GCI(tmpCard->suit, tmpCard->rank)].x + 5;
		clipping.y = gAssets->cardClippings[GCI(tmpCard->suit, tmpCard->rank)].y + 5;
		
		SDL_RenderCopy(
			gWindow->getRenderer(),
			gAssets->cardsSheetT,
			&clipping,
			&pos
		);
		
		pos.x += pos.w;
		if(pos.x + pos.w > (SCRN_W/2 - (CARD_PAD*((int)hand.size() - 1) + CARD_W)/2 - WIN_PAD*3 + 5)) {
			pos.x = WIN_PAD;
			pos.y += pos.h + WIN_PAD/2;
		}
	}

}


void Human::renderMelds() {
	/// @todo Dude I really need to do some clean up on this. It is terrible,
	/// but it works, I dont know why, but it does. Dont mess with it
	SDL_Rect clipping = SDL_Rect{0, 0, 30, 55};
	
	SDL_Rect pos = SDL_Rect{
		WIN_PAD,
		SCRN_H - MCARD_H*5 - WIN_PAD*6,
		MCARD_W,
		MCARD_H
	};
	
	for(Meld* tmpMeld : melds) {
		for(Card* tmpCard : tmpMeld->cards) {
			clipping.x = gAssets->cardClippings[GCI(tmpCard->suit, tmpCard->rank)].x + 5;
			clipping.y = gAssets->cardClippings[GCI(tmpCard->suit, tmpCard->rank)].y + 5;
			
			SDL_RenderCopy(
				gWindow->getRenderer(),
				gAssets->cardsSheetT,
				&clipping,
				&pos
			);
			
			pos.x += pos.w;
		}
		
		pos.x = WIN_PAD;
		pos.y += pos.h + WIN_PAD/2;
	}
}
