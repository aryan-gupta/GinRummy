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

#include ".\inc\main.h"

static const char* CARDS_SHEET = ".\\res\\sprites\\Spritesheets\\playingCards.png";

Resources::Resources() {
	
}

Resources::~Resources() {
	
}

SDL_Texture* Resources::load(const char* file) {
	SDL_Surface* tmpSurface = IMG_Load(file);
		
	if(tmpSurface == nullptr)
		EXIT("Could not load " << file << IMG_GetError(), -0x101)
	
	SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface ( // Set the Player's texture
		gWindow->getRenderer(),
		tmpSurface
	);
	
	SDL_FreeSurface(tmpSurface); tmpSurface = nullptr;
	
	return tmpTexture;
}