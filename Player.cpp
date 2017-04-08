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
#include <SDL.h>

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

static const char* Meld_Label[] {
	"MELD_SET",
	"MELD_RUN"
};


Player::Player(bool isUser) {
	this->isUser = isUser;
}


Player::~Player() {
	for(Card* test : hand)
		delete test;
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
					std::sort( // sort the 3 cards by rank
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


void Player::doTurn() {
	getMelds();
	printHand();
	
	//pickDeck();
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
			if(isMovingCard) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				
				int cardx = x - (SCRN_W/2 - (CARD_PAD*9 + CARD_W)/2); // get the x coordinate offset from the start of the cards
				int cardi = cardx / CARD_PAD; // get the index of the card we clicked
				
				// Make sure the card doesn't leave the hand
				if(cardi > (int)hand.size() - 1)
					cardi = hand.size() - 1;
				if(cardi < 0)
					cardi = 0;
				
				moveCard(selectedCard, cardi);
			}
			
			int x, y; // you have to declare variables outside the switch, annoying, i know
			switch(event.type) {
				case SDL_QUIT:
					quit(0x01);
				break;
				
				case SDL_MOUSEBUTTONDOWN:
					/// @todo If next event is mouse movement then THEN move the card. 
					/// @todo get card that the user selected
					SDL_GetMouseState(&x, &y);
					
					if(    x > SCRN_W/2 - (CARD_PAD*9 + CARD_W)/2
						&& x < SCRN_W/2 + (CARD_PAD*9 + CARD_W)/2
						&& y > SCRN_H - WIN_PAD - CARD_H
						&& y < SCRN_H - WIN_PAD
					)  {
						isMovingCard = true;
						int cardx = x - (SCRN_W/2 - (CARD_PAD*9 + CARD_W)/2); // get the x coordinate offset from the start of the cards
						int cardi = cardx / CARD_PAD; // get the index of the card we clicked
						
						if(cardi >= (int)hand.size()) // correct for the last card being the top card
							cardi = hand.size() - 1;
						
						selectedCard = hand[cardi];
					}
				break;
				
				case SDL_MOUSEBUTTONUP:
					/// @todo check for button presses or released the card
					if(isMovingCard) {
						isMovingCard = false;
						selectedCard = nullptr;
					} else {
						/// @todo if one of the decks of cards is selected then mark finished to true
						SDL_GetMouseState(&x, &y);
						
						if(gDeck->checkClick(x, y)) {
							LOGL("DECK") // WE CLICKED ON THE DECK
						}
						
						if(gDiscard->checkClick(x, y)) {
							LOGL("DISCARD") // WE CLICKED ON THE DISCARD
						}
					}
				break;
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
				
				int cardx = x - (SCRN_W/2 - (CARD_PAD*9 + CARD_W)/2); // get the x coordinate offset from the start of the cards
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
				
				case SDL_MOUSEBUTTONDOWN: // If we clicked down (Only thing here is moving the card)
					/// @todo get card that the user selected
					int x, y;
					SDL_GetMouseState( &x, &y );
					
					if(    x > SCRN_W/2 - (CARD_PAD*9 + CARD_W)/2
						&& x < SCRN_W/2 + (CARD_PAD*9 + CARD_W)/2
						&& y > SCRN_H - WIN_PAD - CARD_H
						&& y < SCRN_H - WIN_PAD
					)  {
						int cardx = x - (SCRN_W/2 - (CARD_PAD*9 + CARD_W)/2); // get the x coordinate offset from the start of the cards
						int cardi = cardx / CARD_PAD; // get the index of the card we clicked
						
						if(cardi >= (int)hand.size()) // correct for the last card being the top card
							cardi = hand.size() - 1;
						
						selectedCard = hand[cardi];
					}
				break;
				
				case SDL_MOUSEMOTION:
					if(selectedCard != nullptr) isMovingCard = true;
				break;
				
				case SDL_MOUSEBUTTONUP: // we clicked up, here is where we want to select the decks and what not
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
					}
				break;
			}
		}
	}
}


void Player::moveCard(Card* c, int idx) {
	for(unsigned i = 0; i < hand.size(); ++i) {
		if(c == hand[i])
			hand.erase(hand.begin() + i);
	}
	
	hand.insert(hand.begin() + idx, c);
}


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
	renderButtons();
}


void Player::renderCards() {
	// The entire card lay is going to be 140px for the top card and 40px for each
	// card behind, But we are shrinking the card by a factor of 0.25 so its 35px
	// for the top card and 10px for the sequential cards. Total of 125px
	
	if(isUser) {
		SDL_Rect currCardPos = {
			SCRN_W/2 - (CARD_PAD*9 + CARD_W)/2,
			SCRN_H - WIN_PAD - CARD_H,
			CARD_W,
			CARD_H
		};
		
		for(Card* tmpCard : hand) {
			SDL_RenderCopy(
				gWindow->getRenderer(),
				gAssets->cardsSheet,
				&gAssets->cardClippings[GCI(tmpCard->suit, tmpCard->rank)],
				&currCardPos
			);
			
			currCardPos.x += CARD_PAD;
		}
	} else {
		SDL_Rect currCardPos = {
			SCRN_W/2 - (CARD_PAD*9 + CARD_W)/2,
			WIN_PAD,
			CARD_W,
			CARD_H
		};
		
		for(unsigned i = 0; i < hand.size(); ++i) {
			SDL_RenderCopy(
				gWindow->getRenderer(),
				gAssets->cardBackSheet,
				&gAssets->cardClippingBack,
				&currCardPos
			);
			
			currCardPos.x += CARD_PAD;
		}
	}
}


void Player::renderDeadwood() {
	
}


void Player::renderMelds() {
	
}


void Player::renderButtons() {
	
}