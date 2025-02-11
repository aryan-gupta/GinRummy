/* 
 * Copyright (c) 2017 The Cool Group - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by:
 * Harrison Read		<hread2@uncc.edu>
 * Pichsapa Kulapruk	<pkulapru@uncc.edu>
 * Aryan Gupta			<agupta40@uncc.edu>
 * 
 * =============================================================================
 * @author 			The Cool Group
 * @project 		GinRummy 		
 * @title 			
 * @date			(YYYY-MM-DD)
 * @fversion		1.0.0
 * @description 	
 * =============================================================================
 */
#include "info.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include <SDL2/SDL_TTF.h>
#include <iostream>
#include <vector>
using std::vector;
#include <algorithm>
#include <time.h>

#include "./inc/main.h"
#include "./inc/CardPile.h"
#include "./inc/Player.h"
#include "./inc/Human.h"
#include "./inc/Opponent.h"
#include "./inc/Window.h"
#include "./inc/Resources.h"

const int NUM_CARDS_PER = 10;
const int MAX_FPS = 45;

CardPile* gDeck;
CardPile* gDiscard;

Player* P1;
Player* P2;

Window* gWindow;
const Resources* gAssets;

int main(int argc, char* argv[]) {
	srand(time(0));
	initSDL();
	
	// Create our variables
	gWindow  = new Window();
	gAssets  = new Resources();
	gWindow->initWindow(); // Init our window class
	
	gDeck    = new CardPile(PILE_DECK);
	gDiscard = new CardPile(PILE_DISCARD);
	P1       = new Human();
	P2       = new Opponent();
	
	gDeck->shuffle(); // Shuffle our main deck
	
	dealCards(); // Deal the cards
	
	//while(true) {
		gWindow->getKnockStatus() = false;
		while(!gWindow->getKnockStatus()) { // Loop through turns (Will change as we progress through our game)
			if(gDeck->size() == 0) swap();
			P1->doTurn();
			
			if(gDeck->size() == 0) swap();
			P2->doTurn();
		}
		
		gWindow->finalizeRound(); // getting the point and all the melds 
		
	//}
	
	return 0x00;
}


void initSDL() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) // Init SDL with Video
		EXIT("SDL Init Failed! " << SDL_GetError(), -0x101);
	
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) // Set render scaling quality
		EXIT("SDL Scaling Failed! " << SDL_GetError(), -0x101);
		
	int flags = IMG_INIT_PNG | IMG_INIT_JPG; // Init png and jpg/jpeg loading
	if(!(IMG_Init(flags) & flags))
		EXIT("IMG SDL Init Failed! " << IMG_GetError(), -0x101);
	
	if(TTF_Init() < 0) // Init TTF and text rendering
		EXIT("TTF SDL Init Failed! " << TTF_GetError(), -0x101);
	/*
	if(Mix_Init(MIX_INIT_OGG) < 0)
		EXIT("Mixer Init Failed! " << Mix_GetError(), -0x101);
	
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) //Initialize SDL_mixer
		EXIT("Mixer Init Failed! " << Mix_GetError(), -0x101);
	*/
}


void dealCards() {
	for(int i = 0; i < NUM_CARDS_PER; ++i) { // Give each player 10 cards
		P1->takeCard(gDeck->getACard());
		P2->takeCard(gDeck->getACard());
	}
}

void swap(){
	std::swap(gDiscard, gDeck);
	gDiscard->swapTypes();
	gDeck->swapTypes();
}

void quit(int code) {
	// Delete all of our global variables
	delete gWindow;
	delete gAssets;
	delete gDeck;
	delete gDiscard;
	delete P1;
	delete P2;
	
	// exit
	exit(code);
}