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
#include <algorithm>

#include ".\inc\main.h"
#include ".\inc\Card.h"

const int SHUFFLE_TIMES = 50;

std::vector<Card*> gDeck;

int main(int argc, char* argv[]) {
	srand(time(0));
	
	create52Cards();
	shuffleCards();
	
	
	return 0;
}

void create52Cards() {
	for(Suits i = 0; i < SUIT_TOTAL; ++i) {
		for(Suits j = 0; j < CARDS_TOTAL; ++j) {
			gDeck.push_back(new Card(i, j)); // create cards with combinations of Suits and Cards
		}
	}
}

void shuffleCards() {
	int shuffle = SHUFFLE_TIMES;
	while(shuffle) {
		int first = rand() % 52, second = rand() % 52; // Pick 2 random numbers
		
		std::swap(gDeck[first], gDeck[second]); // Swap those two cards
		
		suffle--;
	}
}