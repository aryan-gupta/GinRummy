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
#include "./inc/Player.h"
#include "./inc/CardPile.h"
#include "./inc/Window.h"
#include "./inc/Resources.h"

const int MCARD_W = 35 *5/8;
const int MCARD_H = 55 *5/8;

Player::~Player() {
	for(Card* tmpCard : hand)
		delete tmpCard; // Delete the cards in our hands
}


void Player::takeCard(Card* card) {
	hand.push_back(card);
}


void Player::getMelds() {
	melds.clear();
	
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


void Player::getDeadwood() {
	// FIND anycard in our hand that not part of meld 
	deadwood = hand; // first copy the hand into deadwood
	
	for(Meld* tmpMeld : melds) {
		for(Card* tmpCard : tmpMeld->cards) {
			auto idx = std::remove(deadwood.begin(), deadwood.end(), tmpCard);
			deadwood.erase(idx, deadwood.end());
		}
	}
}


unsigned Player::getNumDeadwood() {
	// FIND how many deadwood do we have in our hand  
	int sum = 0; 
	
	for(unsigned i = 0; i < deadwood.size(); i++) { 
		if(deadwood[i]->rank > RANK_JACK) { 
			sum = sum + 10;
		}	
		else { sum = sum + deadwood[i]->rank + 1; } 
	}
	return sum;
	
}


bool Player::canWeKnock() {
	return getNumDeadwood() < 10;
}


unsigned Player::getPoints() {
	unsigned sum = 0;
	
	sum += getGin();
	sum += getBigGin();
	
	return sum;
}


Card* Player::getCard(Card* card) { 
	for(unsigned i = 0; i < hand.size(); ++i) // find the card in our hand
		if(card == hand[i]) 
			hand.erase(hand.begin() + i);     // remove card from hand  
	return card; // return the card
}		

/*
unsigned Player::getKnockPoints() {
	
	
	
	
	// return 0; 
}
*/

unsigned Player::getGin() {
	// when all 10 cards in our hand are parts of melds also have no deadwood 
	
	if(deadwood.size() == 1) 
		
	return 25;
}


unsigned Player::getBigGin() {
	// When all 10 cards in our hand are parts of melds and the card we just drew are parts of melds - 11 cards total
	if(deadwood.size() == 0) 
	
	return 30;
}