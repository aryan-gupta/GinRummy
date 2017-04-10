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
#include <SDL.h>
#include <string.h>

#include ".\inc\main.h"
#include ".\inc\Opponent.h"
#include ".\inc\CardPile.h"
#include ".\inc\Window.h"
#include ".\inc\Resources.h"

void Opponent::doTurn() {

}


void Opponent::render() {
	renderCards();
}

void Opponent::renderCards() {
	SDL_Rect currCardPos = { // Get the first card loaction
		SCRN_W/2 - (CARD_PAD*((int)hand.size() - 1) + CARD_W)/2,
		WIN_PAD,
		CARD_W,
		CARD_H
	};
	
	for(unsigned i = 0; i < hand.size(); ++i) {
		SDL_RenderCopy( // render it
			gWindow->getRenderer(),
			gAssets->cardBackSheet,
			&gAssets->cardClippingBack,
			&currCardPos
		);
		
		currCardPos.x += CARD_PAD; // move the pos to the next card
	}
}