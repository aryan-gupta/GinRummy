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

void Player::getMelds(vector<Meld*>& foundMelds) {
	// FIND SETS (3 or 4 cards with the same rank/value)
	for(unsigned i = 0; i < hand.size(); ++i) {
		for(unsigned j = i + 1; j < hand.size(); ++j) {
			for(unsigned k = j + 1; k < hand.size(); ++k) {
				if(    (hand[i]->rank == hand[j]->rank) // see if the ranks are the same
					&& (hand[j]->rank == hand[k]->rank)
				) {
					foundMelds.push_back( new Meld{
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
					) { foundMelds.push_back( new Meld{MELD_RUN, tmpCards} ); }
				}
			}
		}
	}
}

void Player::takeCard(Card* card) {
	hand.push_back(card);
}

void Player::doTurn() {
	printHand();
	
	vector<Meld*> foundMelds;
	getMelds(foundMelds);
	
	if(foundMelds.size() == 0) {
		cout << "NO MELDS FOUND" << endl;
	} else {
		for(auto tmpMeld : foundMelds) {
			cout << tmpMeld->type << " " << endl;
			for(auto tmpCard : tmpMeld->cards) {
				cout << "\t" << Suits_Label[tmpCard->suit] << " " << Ranks_Label[tmpCard->rank] << " " << endl;
			}
		}
	}
	
	if(isUser) {} else {}
	cout << endl;
}

void Player::printHand() {
	for(Card* tmpCard : hand)
		cout << Suits_Label[tmpCard->suit] << " " << Ranks_Label[tmpCard->rank] << " " << endl;
}

void Player::render() {
	
}