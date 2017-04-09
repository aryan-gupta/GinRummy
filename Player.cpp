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
#include <SDL.h>
#include <string.h>

#include ".\inc\main.h"
#include ".\inc\Player.h"
#include ".\inc\CardPile.h"
#include ".\inc\Window.h"
#include ".\inc\Resources.h"

/// @brief labels for the suits (for debugging)
static const char* Suits_Label[] {
	"SUIT_CLUBS",
	"SUIT_DIAMONDS",
	"SUIT_HEARTS",
	"SUIT_SPADES",
	
	"SUIT_TOTAL"
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

/// @brief Labels for the melds
static const char* Meld_Label[] {
	"MELD_SET",
	"MELD_RUN"
};

const int MCARD_W = 35 *5/8;
const int MCARD_H = 55 *5/8;


Player::Player(bool isUser) {
	this->isUser = isUser;
}


Player::~Player() {
	for(Card* tmpCard : hand)
		delete tmpCard; // Delete the cards in our hands
}


void Player::getMelds() {
	// FIND SETS (3 or 4 cards with the same rank/value)
	for(unsigned i = 0; i < hand.size(); ++i) {
		for(unsigned j = i + 1; j < hand.size(); ++j) {
			for(unsigned k = j + 1; k < hand.size(); ++k) {
				if(    (hand[i]->rank == hand[j]->rank) // see if the ranks are the same
					&& (hand[j]->rank == hand[k]->rank)
				) {
					melds.push_back( new Meld{
						MELD_SET,
						{hand[i], hand[j], hand[k]}
					});
				}
			}
		}
	}
	///@todo Check for a 4 card set
	
	// FIND RUNS (3 cards in the same suit that go in order)
	for(unsigned i = 0; i < hand.size(); ++i) {
		for(unsigned j = i + 1; j < hand.size(); ++j) {
			for(unsigned k = j + 1; k < hand.size(); ++k) { // go through sets of 3 cards
				if(    hand[i]->suit == hand[j]->suit // if the suits are all the same, we may have a run
					&& hand[j]->suit == hand[k]->suit
				) {
					vector<Card*> tmpCards{hand[i], hand[j], hand[k]}; // create vector to sort 
					sort( // sort the 3 cards by rank
						tmpCards.begin(), tmpCards.end(),
						[](Card* a, Card* b) { return a->rank < b->rank; }
					);
					
					// for(Card* tmpCard : tmpCards)
						// cout << "\t" << Suits_Label[tmpCard->suit] << " " << Ranks_Label[tmpCard->rank] << " " << endl;
					
					if(    tmpCards[0]->rank == tmpCards[1]->rank - 1 // see if the ranks are incrementing
						&& tmpCards[1]->rank == tmpCards[2]->rank - 1
					) { melds.push_back( new Meld{MELD_RUN, tmpCards} ); }
				}
			}
		}
	}
}


void Player::takeCard(Card* card) {
	hand.push_back(card);
}


unsigned Player::getNumDeadwood() {
	return 0;
}


void Player::doTurn() {
	getMelds();
	printHand();
	
	pickDeck();
	pickCard();

}


void Player::pickDeck() {
	/// @todo First we want to ask the user to pick a deck to pull cards from
	bool finished = false, isMovingCard = false;
	Card* selectedCard = nullptr;
	SDL_Event event;
	
	while(!finished) {
		
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
					/// @todo If next event is mouse movement then THEN move the card. 
					/// @todo get card that the user selected
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
						/// @todo if one of the decks of cards is selected then mark finished to true
						int x, y;
						SDL_GetMouseState(&x, &y);
						
						if(gDeck->checkClick(x, y)) {
							LOGL("DECK") // WE CLICKED ON THE DECK
						}
						
						if(gDiscard->checkClick(x, y)) {
							LOGL("DISCARD") // WE CLICKED ON THE DISCARD
						}
					}
				} break;
			}
		}
	}
}


void Player::pickCard() {
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
						for(unsigned i = 0; i < hand.size(); ++i)
							if(selectedCard == hand[i])
								LOGL("CLICKED ON " << i << " Card")
						selectedCard = nullptr;
						
						int x, y;
						SDL_GetMouseState(&x, &y);
						if(gWindow->checkKnockClick(x, y))
							LOGL("WE KNOCKED")
						if(gWindow->checkSortClick(x, y))
							LOGL("WE SORTED")
					}
				} break;
			}
		}
	}
}


void Player::moveCard(Card* c, int idx) {
	for(unsigned i = 0; i < hand.size(); ++i) {
		if(c == hand[i])
			hand.erase(hand.begin() + i); // remove the selected card
	}
	
	hand.insert(hand.begin() + idx, c); // move it to the new location
}

// WILL BE REMOVED IN FINAL GAME
void Player::printHand() {
	for(Card* tmpCard : hand)
		cout << Suits_Label[tmpCard->suit] << " " << Ranks_Label[tmpCard->rank] << " " << endl;
	
	if(melds.size() == 0) {
		cout << "NO MELDS FOUND" << endl;
	} else {
		for(auto tmpMeld : melds) {
			cout << Meld_Label[tmpMeld->type] << " " << endl;
			for(auto tmpCard : tmpMeld->cards) {
				cout << "\t" << Suits_Label[tmpCard->suit] << " " << Ranks_Label[tmpCard->rank] << " " << endl;
			}
		}
	}
	
	if(isUser) {} else {}
	cout << endl;
}


void Player::render() {
	renderCards();
	renderDeadwood();
	renderMelds();
}


void Player::renderCards() {
	// The entire card lay is going to be 140px for the top card and 40px for each
	// card behind, But we are shrinking the card by a factor of 0.25 so its 35px
	// for the top card and 10px for the sequential cards. Total of 125px
	if(isUser) {
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
	} else {
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
}


void Player::renderDeadwood() {
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
	
	vector<Card*> tmpHand(hand);
	sort(
		tmpHand.begin(), tmpHand.end(),
		[](Card* a, Card* b) {
			return GCI(a->suit, a->rank) < GCI(b->suit, b->rank);
		}
	);
	if(isUser) {		
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
}


void Player::renderMelds() {
	/// @todo Dude I really need to do some clean up on this. It is terrible,
	/// but it works, I dont know why, but it does. Dont mess with it
	if(isUser) {
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
}
