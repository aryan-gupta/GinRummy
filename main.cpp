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

#include <SDL.h>
#include <SDL_Image.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

#include ".\inc\main.h"
#include ".\inc\CardPile.h"
#include ".\inc\Player.h"

const int NUM_CARDS_PER = 10;

CardPile* gDeck;
CardPile* gDiscard;

std::vector<Meld*> melds;
Player* P1;
Player* P2;

int main(int argc, char* argv[]) {
	srand(time(0));
	initSDL();
	
	gDeck = new CardPile(PILE_DECK);
	gDeck->shuffle();
	
	gDiscard = new CardPile(PILE_DISCARD);
	
	P1 = new Player(true);
	P2 = new Player(false);
	
	dealCards();
	
	for(Player* tmpPlayer : gPlayers)
		tmpPlayer->doTurn();
	
	system("pause");
	return 0;
}

void initSDL() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) // Init SDL with Video
		EXIT("SDL Init Failed! " << SDL_GetError(), -0x101);
	
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) // Set render scaling quality
		EXIT("SDL Scaling Failed! " << SDL_GetError(), -0x101);
		
	int flags = IMG_INIT_PNG | IMG_INIT_JPG; // Init png and jpg/jpeg loading
	if(!(IMG_Init(flags) & flags))
		EXIT("IMG SDL Init Failed! " << IMG_GetError(), -0x101);
	/*
	if(TTF_Init() < 0) // Init TTF and text rendering
		EXIT("TTF SDL Init Failed! " << TTF_GetError(), -0x101);
	
	if(Mix_Init(MIX_INIT_OGG) < 0)
		EXIT("Mixer Init Failed! " << Mix_GetError(), -0x101);
	
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) //Initialize SDL_mixer
		EXIT("Mixer Init Failed! " << Mix_GetError(), -0x101);
	*/
}

void dealCards() {
	for(int i = 0; i < NUM_CARDS_PER; ++i) {
		P1->takeCard(gDeck->getACard());
		P2->takeCard(gDeck->getACard());
	}
}