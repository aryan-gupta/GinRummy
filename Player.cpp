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
#include <functional>

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
	typedef std::vector<Card*> CS; // Card Stack
	melds.clear(); /// @todo clean up dynamic memory
	/// @todo Fix multiple cards
	CS tmpHand = hand;
	
	std::sort(
		tmpHand.begin(), tmpHand.end(),
		[](Card* a, Card* b) {
			return (a->suit*RANK_TOTAL + a->rank) < (b->suit*RANK_TOTAL + b->rank);
		}
	);
	
	for(int i = 0; i < tmpHand.size(); ++i) {
		int j = i + 1;
		for(/*blank*/; j < tmpHand.size(); ++j) {
			if(tmpHand[i]->suit != tmpHand[j]->suit)
				break;
			
			if(tmpHand[i]->rank != (tmpHand[j]->rank - (j - i)))
				break;
		}
		//LOGL(j - i)
		if(j - i > 2) {
			melds.push_back( new Meld {
				MELD_RUN,
				CS(tmpHand.begin() + i, tmpHand.begin() + j)
			});
			i = j;
		}
	}
	
	bool (*checkMelds)(CS) = [](CS vec) { // Could use std::function<bool(CS)>
		for(Card* tmpCard : vec)
			if(tmpCard->rank != vec[0]->rank)
				return false;	
		return true;
	};
	
	tmpHand = hand;
	std::sort(
		tmpHand.begin(), tmpHand.end(),
		[](Card* a, Card* b) {
			return (a->rank*SUIT_TOTAL + a->suit) < (b->rank*SUIT_TOTAL + b->suit);
		}
	);
	
	for(int i = tmpHand.size() - 1; i > 1; --i) { // Go through the hand (There is no point of going backwards, but thats just the way we did it)
		if(    i > 2 // Make sure that we wont go out of bounds checking 4 card set
			&& checkMelds({tmpHand[i], tmpHand[i - 1], tmpHand[i - 2], tmpHand[i - 3]})
		) {
			melds.push_back( new Meld { // if so we have a meld
				MELD_SET,
				{tmpHand[i], tmpHand[i - 1], tmpHand[i - 2], tmpHand[i - 3]}
			});
			i -= 3; // move the pointer back 3 points so it isnt included in a meld again
		} else if(checkMelds({tmpHand[i], tmpHand[i - 1], tmpHand[i - 2]})) {
			melds.push_back( new Meld {
				MELD_SET,
				{tmpHand[i], tmpHand[i - 1], tmpHand[i - 2]}
			});
			i -= 2;
		}
	}
	
	// Sort by size
	// remove from the end if the cards repeat
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