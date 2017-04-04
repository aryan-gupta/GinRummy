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
#include ".\inc\CardPile.h"
#include ".\inc\Player.h"


const int NUM_PLAYERS = 4;
const int NUM_CARDS_PER = 7;

CardPile* gDeck;
CardPile* gDiscard;

std::vector<CardPile*> melds;
std::vector<Player*> gPlayers;

int main(int argc, char* argv[]) {
	srand(time(0));
	
	gDeck = new CardPile(PILE_DECK);
	gDeck->shuffle();
	
	gDiscard = new CardPile(PILE_DISCARD);
	createPlayers();
	dealCards();
	
	do {
		for(Player* tmpPlayer : gPlayers)
			tmpPlayer->doTurn();
	} while(true);
	
	return 0;
}

void createPlayers() {
	gPlayers.push_back(new Player(true));
	for(int i = 1; i < NUM_PLAYERS; ++i) {
		gPlayers.push_back(new Player());
	}
}

void dealCards() {
	for(int i = 0; i < NUM_CARDS_PER; ++i) {
		for(Player* tmp : gPlayers) {
			tmp->takeCard(gDeck->getACard());
		}
	}
}