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

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

class CardPile;
class Player;
struct Meld;

extern const int NUM_PLAYERS;
extern const int NUM_CARDS_PER;

extern CardPile* gDeck;
extern CardPile* gDiscard;

extern std::vector<Meld*> melds;
extern std::vector<Player*> gPlayers;

// =========================

int main(int argc, char* argv[]);

void initSDL();

void createPlayers();

void dealCards();

#endif // MAIN_H_INCLUDED