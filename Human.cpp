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
	getMelds();    // update our melds
	getDeadwood(); // update our deadwood
	pickDeck();    // pick a deack to pick from
	
	getMelds();    // update our melds
	getDeadwood(); // update our deadwood
	pickCard();    // pick a card to discard
}


void Human::pickDeck() {
	gWindow->changeHelp(HTI_PICK_DECK); // Change help text
	
	bool finished = false, isMovingCard = false, sortByRank = false;
	Card* selectedCard = nullptr;
	SDL_Event event;
	uint32_t FPS_Timer = 0;
	int xDown, yDown;
	
	while(!finished) { // RENDER LOOP
		FPS_Timer = SDL_GetTicks();
		
		gWindow->renderAll(); // render everything
		
		while(SDL_PollEvent(&event)) { // EVENT LOOP
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
					SDL_GetMouseState(&xDown, &yDown);
					
					if(    xDown > SCRN_W/2 - (CARD_PAD*((int)hand.size() - 1) + CARD_W)/2
						&& xDown < SCRN_W/2 + (CARD_PAD*((int)hand.size() - 1) + CARD_W)/2
						&& yDown > SCRN_H - WIN_PAD - CARD_H
						&& yDown < SCRN_H - WIN_PAD
					)  {
						//isMovingCard = true;
						int cardx = xDown - (SCRN_W/2 - (CARD_PAD*(hand.size() - 1) + CARD_W)/2); // get the x coordinate offset from the start of the cards
						int cardi = cardx / CARD_PAD; // get the index of the card we clicked
						
						if(cardi >= (int)hand.size()) // correct for the last card being the top card
							cardi = hand.size() - 1;
						
						selectedCard = hand[cardi];
					}
				} break;
				
				case SDL_MOUSEMOTION: {
					int x, y;
					SDL_GetMouseState(&x, &y);
					
					if(selectedCard != nullptr) {
						if(abs(x - xDown) > 3 || abs(y - yDown) > 3)
							isMovingCard = true;
					}
				} break;
				
				case SDL_MOUSEBUTTONUP: {
					if(isMovingCard) {
						isMovingCard = false;
						selectedCard = nullptr;
						gWindow->changeHelp(HTI_PICK_DECK); // Change help text
					} else {
						gWindow->changeHelp(HTI_PICK_DECK_ERR);
						
						int x, y;
						SDL_GetMouseState(&x, &y);
						
						if(gWindow->checkKnockClick(x, y)) {
							LOGL("WE KNOCKED") /// @todo change help text
							gWindow->changeHelp(HTI_CANNOT_KNOCK);
						}
						
						if(gDeck->checkClick(x, y)) {
							takeCard(gDeck->getACard()); // WE CLICKED ON THE DECK 
							finished = true; 				
						}
						
						if(gDiscard->checkClick(x, y)) {
							takeCard(gDiscard->getACard()); // WE CLICKED ON THE DISCARD
							finished = true; 
						}
						
						if(gWindow->checkSortClick(x, y)) { ///@todo Swap sorting algorithms
							if(sortByRank) {
								sort(
									hand.begin(), hand.end(),
									[](Card* a, Card* b) {
										return a->rank*SUIT_TOTAL + a->suit < b->rank*SUIT_TOTAL + b->suit; // GCI convert rank and suit to number 
								}); 
								sortByRank = !sortByRank;
							} else {
								sort(
									hand.begin(), hand.end(),
									[](Card* a, Card* b) {
										return a->suit*RANK_TOTAL + a->rank < b->suit*RANK_TOTAL + b->rank; // GCI convert rank and suit to number 
								}); 
								sortByRank = !sortByRank;
							}
							gWindow->changeHelp(HTI_PICK_DECK);
						}
						
						selectedCard = nullptr;
					}
				} break;
			}
		}
		
		uint32_t frameTicks = SDL_GetTicks() - FPS_Timer; // Get time it took to render frame
		if( frameTicks < 1000.0/MAX_FPS ) // If this was too big
			SDL_Delay( 1000.0/MAX_FPS - frameTicks ); // Wait remainging time
	}
}


void Human::pickCard() {
	gWindow->changeHelp(HTI_PICK_CARD);
	
	/// @todo Then we want to get the melds and organize our cards and pick a card to discard
	bool finished = false, isMovingCard = false, sortByRank = false;
	Card* selectedCard = nullptr;
	SDL_Event event;
	uint32_t FPS_Timer = 0;
	int xDown, yDown;
	
	while(!finished) {
		FPS_Timer = SDL_GetTicks();
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
					SDL_GetMouseState(&xDown, &yDown);
					
					if(    xDown > SCRN_W/2 - (CARD_PAD*((int)hand.size() - 1) + CARD_W)/2
						&& xDown < SCRN_W/2 + (CARD_PAD*((int)hand.size() - 1) + CARD_W)/2
						&& yDown > SCRN_H - WIN_PAD - CARD_H
						&& yDown < SCRN_H - WIN_PAD
					)  {
						int cardx = xDown - (SCRN_W/2 - (CARD_PAD*(hand.size() - 1) + CARD_W)/2); // get the x coordinate offset from the start of the cards
						int cardi = cardx / CARD_PAD; // get the index of the card we clicked
						
						if(cardi >= (int)hand.size()) // correct for the last card being the top card
							cardi = hand.size() - 1;
						
						selectedCard = hand[cardi];
					}
				} break;
				
				case SDL_MOUSEMOTION: {
					int x, y;
					SDL_GetMouseState(&x, &y);
					
					if(selectedCard != nullptr) {
						if(abs(x - xDown) > 3 || abs(y - yDown) > 3) // make sure the user moves at least 3 px before moving card
							isMovingCard = true;
					}
				} break;
				
				case SDL_MOUSEBUTTONUP: { // we clicked up, here is where we want to select the decks and what not
					if(isMovingCard) { // if we were moving the card, release the card
						isMovingCard = false;
						selectedCard = nullptr;
					} else {
						gWindow->changeHelp(HTI_PICK_CARD_ERR); // change help text to ERROR
						/// @todo warn the user if we are discarding a meld card
						if(selectedCard != nullptr) { // if we have selected a card and not moving it
							gDiscard->takeACard(getCard(selectedCard)); // discard it
							finished = true; // we are finished with this step
						}
						
						int x, y;
						SDL_GetMouseState(&x, &y);
						
						if(gWindow->checkKnockClick(x, y)) { // we clicked on the knock button
							//if(canWeKnock()) { 
								gWindow->knock(PLAYER_1);  // 1 means player1 
							//} else { 
								//gWindow->changeHelp(HTI_CANNOT_KNOCK);
							//}
							finished = true;
						}
						
						if(gWindow->checkSortClick(x, y)) { ///@todo Swap sorting algorithms
							if(sortByRank) {
								sort(
									hand.begin(), hand.end(),
									[](Card* a, Card* b) {
										return a->rank*SUIT_TOTAL + a->suit < b->rank*SUIT_TOTAL + b->suit; // GCI convert rank and suit to number 
								}); 
								sortByRank = !sortByRank;
							} else {
								sort(
									hand.begin(), hand.end(),
									[](Card* a, Card* b) {
										return a->suit*RANK_TOTAL + a->rank < b->suit*RANK_TOTAL + b->rank; // GCI convert rank and suit to number 
								}); 
								sortByRank = !sortByRank;
							}
							
							gWindow->changeHelp(HTI_PICK_CARD);
						}
						
						selectedCard = nullptr; // unselected any card we clicked on (not needed but not adding bugs me)
					}
				} break;
			}
		}
		
		uint32_t frameTicks = SDL_GetTicks() - FPS_Timer; // Get time it took to render frame
		if( frameTicks < 1000.0/MAX_FPS ) // If this was too big
			SDL_Delay( 1000.0/MAX_FPS - frameTicks ); // Wait remainging time
	}
}


void Human::moveCard(Card* c, int idx) {
	for(unsigned i = 0; i < hand.size(); ++i) {
		if(c == hand[i])
			hand.erase(hand.begin() + i); // remove the selected card from the hand
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
		("(" + std::to_string(getNumDeadwood()) + ")").c_str(), // convert num of deadwood into a string
		gAssets->textColor
	);
	SDL_Texture* dwTextTexture = SDL_CreateTextureFromSurface( // Convert it to a texture
		gWindow->getRenderer(),
		textSurface
	);
	SDL_Rect dwTextPos = SDL_Rect{ // get the position
		WIN_PAD + 76,
		SCRN_H - MCARD_H*2 - WIN_PAD*3, // 2 lines of cards plus 3 paddings from the bottom
		textSurface->w, 
		textSurface->h
	};
	
	SDL_FreeSurface(textSurface); // render and free memory
	SDL_RenderCopy(gWindow->getRenderer(), dwTextTexture, NULL, &dwTextPos);
	SDL_DestroyTexture(dwTextTexture);
	
	sort( // sort our deadwood
		deadwood.begin(), deadwood.end(),
		[](Card* a, Card* b) {
			return GCI(a->suit, a->rank) < GCI(b->suit, b->rank);
		}
	);
	
	SDL_Rect clipping = SDL_Rect{0, 0, 30, 55}; // set the w/h of the clippings clippings
	
	SDL_Rect pos = SDL_Rect{ // position of where to render each card
		WIN_PAD,
		SCRN_H - MCARD_H*2 - WIN_PAD*2,
		MCARD_W,
		MCARD_H
	};
	
	for(Card* tmpCard : deadwood) {
		clipping.x = gAssets->cardClippings[GCI(tmpCard->suit, tmpCard->rank)].x + 5; // find each card
		clipping.y = gAssets->cardClippings[GCI(tmpCard->suit, tmpCard->rank)].y + 5;
		
		SDL_RenderCopy( // render
			gWindow->getRenderer(),
			gAssets->cardsSheetT,
			&clipping,
			&pos
		);
		
		pos.x += pos.w;
		if(pos.x + pos.w > (SCRN_W/2 - (CARD_PAD*((int)hand.size() - 1) + CARD_W)/2 - WIN_PAD*2)) { ///@ @todo make this gAssets->deadwood-panel dependent
			pos.x = WIN_PAD; // CRLF
			pos.y += pos.h + WIN_PAD/2;
		}
	}

}


void Human::renderMelds() {
	/// @todo Dude I really need to do some clean up on this. It is terrible,
	/// but it works, I dont know why, but it does. Dont mess with it
	SDL_Rect clipping = SDL_Rect{0, 0, 30, 55}; // Card clipping for mini card
	
	SDL_Rect pos = SDL_Rect{ // position of the meld cards
		WIN_PAD,
		SCRN_H - MCARD_H*5 - WIN_PAD*6, // 5 lines of cards and 6 lines of padding from the bottom
		MCARD_W,
		MCARD_H
	};
	
	for(Meld* tmpMeld : melds) {
		for(Card* tmpCard : tmpMeld->cards) {
			clipping.x = gAssets->cardClippings[GCI(tmpCard->suit, tmpCard->rank)].x + 5; // get card clippings and remove 5px from the top and left
			clipping.y = gAssets->cardClippings[GCI(tmpCard->suit, tmpCard->rank)].y + 5;
			
			SDL_RenderCopy( // render
				gWindow->getRenderer(),
				gAssets->cardsSheetT,
				&clipping,
				&pos
			);
			
			pos.x += pos.w; // move to next 'character'
		}
		
		pos.x = WIN_PAD; // CRLF
		pos.y += pos.h + WIN_PAD/2;
	}
}


void Human::renderLayoff() {
	int auxMeldSize = 0;
	for(Meld* m : melds) auxMeldSize += m->cards.size();
	auxMeldSize -= melds.size();
	
	SDL_Rect currCardPos = { // get the first card location
		SCRN_W/2 - ((melds.size() * CARD_W) + CARD_PAD*auxMeldSize)/2,
		SCRN_H - WIN_PAD - CARD_H,
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
	
}