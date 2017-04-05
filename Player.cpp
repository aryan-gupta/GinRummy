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

#include ".\inc\main.h"
#include ".\inc\Player.h"
#include ".\inc\CardPile.h"

Player::Player(bool isUser) {
	this->isUser = isUser;
}

vector<Meld*> Player::getMelds() {
	vector<Meld*> foundMelds;
	
	for(unsigned i = 0; i < hand.size(); ++i) {
		for(unsigned j = i + 1; j < hand.size(); ++j) {
			for(unsigned k = j + 1; k < hand.size(); ++k) {
				if(    (hand[i]->rank == hand[j]->rank)
					&& (hand[j]->rank == hand[k]->rank)
				) {
					foundMelds.push_back( new Meld {
						MELD_SET,
						{hand[i], hand[j], hand[k]}
					});
				}
			}
		}
	}
	///@todo Check for a 4 card set
	
	for(unsigned i = 0; i < hand.size(); ++i) {
		for(unsigned j = i + 1; j < hand.size(); ++j) {
			for(unsigned k = j + 1; k < hand.size(); ++k) { // go through sets of 3 cards
				if(    hand[i]->suit == hand[j]->suit // if the suits are all the same, we may have a run
					&& hand[j]->suit == hand[k]->suit
				) {
					vector<Card*> tmpCards{hand[i], hand[j], hand[k]}; // create vector to sort 
					std::sort( // sort the 3 cards 
						tmpCards.begin(), tmpCards.end(),
						[](Card* a, Card* b) { return a->rank < b->rank; }
					);
					
					if(    tmpCards[0]->rank == tmpCards[1]->rank + 1 // see if the ranks are incrementing
						&& tmpCards[1]->rank == tmpCards[2]->rank + 1
					) {
						foundMelds.push_back( new Meld {MELD_RUN, tmpCards} );
					}
				}
			}
		}
	}
	
	return foundMelds;
}

void Player::takeCard(Card* rank) {
	hand.push_back(rank);
}

void Player::doTurn() {
	if(isUser) {
		//cout << "I have this many ranks: " << hand.size() << endl;
		
	} else {
		
	}
}