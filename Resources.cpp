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

#define GCI(s, r) (s*RANK_TOTAL)+r

static const char* CARDS_SHEET = ".\\res\\sprites\\Spritesheets\\playingCards.png";

Resources::Resources() {
	cardsSheet = load(CARDS_SHEET);
	
	cardClippings = new SDL_Rect(SUIT_TOTAL * RANL_TOTAL); // 52 cards;
	cardClippings[GCI(SUIT_CLUBS   , RANK_ACE  )] = SDL_Rect{560,  570, 140, 190};
	cardClippings[GCI(SUIT_CLUBS   , RANK_2    )] = SDL_Rect{280, 1140, 140, 190};
	cardClippings[GCI(SUIT_CLUBS   , RANK_3    )] = SDL_Rect{700,  190, 140, 190};
	cardClippings[GCI(SUIT_CLUBS   , RANK_4    )] = SDL_Rect{700,    0, 140, 190};
	cardClippings[GCI(SUIT_CLUBS   , RANK_5    )] = SDL_Rect{560, 1710, 140, 190};
	cardClippings[GCI(SUIT_CLUBS   , RANK_6    )] = SDL_Rect{560, 1520, 140, 190};
	cardClippings[GCI(SUIT_CLUBS   , RANK_7    )] = SDL_Rect{560, 1330, 140, 190};
	cardClippings[GCI(SUIT_CLUBS   , RANK_8    )] = SDL_Rect{560, 1140, 140, 190};
	cardClippings[GCI(SUIT_CLUBS   , RANK_9    )] = SDL_Rect{560,  950, 140, 190};
	cardClippings[GCI(SUIT_CLUBS   , RANK_10   )] = SDL_Rect{560,  760, 140, 190};
	cardClippings[GCI(SUIT_CLUBS   , RANK_JACK )] = SDL_Rect{560,  380, 140, 190};
	cardClippings[GCI(SUIT_CLUBS   , RANK_QUEEN)] = SDL_Rect{560,  190, 140, 190};
	cardClippings[GCI(SUIT_CLUBS   , RANK_KING )] = SDL_Rect{560,    0, 140, 190};

	cardClippings[GCI(SUIT_DIAMONDS, RANK_ACE  )] = SDL_Rect{420,    0, 140, 190};
	cardClippings[GCI(SUIT_DIAMONDS, RANK_2    )] = SDL_Rect{420, 1710, 140, 190};
	cardClippings[GCI(SUIT_DIAMONDS, RANK_3    )] = SDL_Rect{420, 1520, 140, 190};
	cardClippings[GCI(SUIT_DIAMONDS, RANK_4    )] = SDL_Rect{420, 1330, 140, 190};
	cardClippings[GCI(SUIT_DIAMONDS, RANK_5    )] = SDL_Rect{420, 1140, 140, 190};
	cardClippings[GCI(SUIT_DIAMONDS, RANK_6    )] = SDL_Rect{420,  950, 140, 190};
	cardClippings[GCI(SUIT_DIAMONDS, RANK_7    )] = SDL_Rect{420,  760, 140, 190};
	cardClippings[GCI(SUIT_DIAMONDS, RANK_8    )] = SDL_Rect{420,  570, 140, 190};
	cardClippings[GCI(SUIT_DIAMONDS, RANK_9    )] = SDL_Rect{420,  380, 140, 190};
	cardClippings[GCI(SUIT_DIAMONDS, RANK_10   )] = SDL_Rect{420,  190, 140, 190};
	cardClippings[GCI(SUIT_DIAMONDS, RANK_JACK )] = SDL_Rect{280, 1710, 140, 190};
	cardClippings[GCI(SUIT_DIAMONDS, RANK_QUEEN)] = SDL_Rect{280, 1520, 140, 190};
	cardClippings[GCI(SUIT_DIAMONDS, RANK_KING )] = SDL_Rect{280, 1330, 140, 190};
	
	cardClippings[GCI(SUIT_HEARTS  , RANK_ACE  )] = SDL_Rect{140, 1330, 140, 190};
	cardClippings[GCI(SUIT_HEARTS  , RANK_2    )] = SDL_Rect{700,  380, 140, 190};
	cardClippings[GCI(SUIT_HEARTS  , RANK_3    )] = SDL_Rect{280,  950, 140, 190};
	cardClippings[GCI(SUIT_HEARTS  , RANK_4    )] = SDL_Rect{280,  760, 140, 190};
	cardClippings[GCI(SUIT_HEARTS  , RANK_5    )] = SDL_Rect{280,  570, 140, 190};
	cardClippings[GCI(SUIT_HEARTS  , RANK_6    )] = SDL_Rect{280,  380, 140, 190};
	cardClippings[GCI(SUIT_HEARTS  , RANK_7    )] = SDL_Rect{280,  190, 140, 190};
	cardClippings[GCI(SUIT_HEARTS  , RANK_8    )] = SDL_Rect{280,    0, 140, 190};
	cardClippings[GCI(SUIT_HEARTS  , RANK_9    )] = SDL_Rect{140, 1710, 140, 190};
	cardClippings[GCI(SUIT_HEARTS  , RANK_10   )] = SDL_Rect{140, 1520, 140, 190};
	cardClippings[GCI(SUIT_HEARTS  , RANK_JACK )] = SDL_Rect{140, 1140, 140, 190};
	cardClippings[GCI(SUIT_HEARTS  , RANK_QUEEN)] = SDL_Rect{140,  950, 140, 190};
	cardClippings[GCI(SUIT_HEARTS  , RANK_KING )] = SDL_Rect{140,  760, 140, 190};
	
	cardClippings[GCI(SUIT_SPADES  , RANK_ACE  )] = SDL_Rect{  0,  570, 140, 190};
	cardClippings[GCI(SUIT_SPADES  , RANK_2    )] = SDL_Rect{140,  380, 140, 190};
	cardClippings[GCI(SUIT_SPADES  , RANK_3    )] = SDL_Rect{140,  190, 140, 190};
	cardClippings[GCI(SUIT_SPADES  , RANK_4    )] = SDL_Rect{140,    0, 140, 190};
	cardClippings[GCI(SUIT_SPADES  , RANK_5    )] = SDL_Rect{  0, 1710, 140, 190};
	cardClippings[GCI(SUIT_SPADES  , RANK_6    )] = SDL_Rect{  0, 1520, 140, 190};
	cardClippings[GCI(SUIT_SPADES  , RANK_7    )] = SDL_Rect{  0, 1330, 140, 190};
	cardClippings[GCI(SUIT_SPADES  , RANK_8    )] = SDL_Rect{  0, 1140, 140, 190};
	cardClippings[GCI(SUIT_SPADES  , RANK_9    )] = SDL_Rect{  0,  950, 140, 190};
	cardClippings[GCI(SUIT_SPADES  , RANK_10   )] = SDL_Rect{  0,  760, 140, 190};
	cardClippings[GCI(SUIT_SPADES  , RANK_JACK )] = SDL_Rect{  0,  380, 140, 190};
	cardClippings[GCI(SUIT_SPADES  , RANK_QUEEN)] = SDL_Rect{  0,  190, 140, 190};
	cardClippings[GCI(SUIT_SPADES  , RANK_KING )] = SDL_Rect{  0,    0, 140, 190};

	//cardJoker.png" x="140" y="570" width="140" height="190"/>
	
}

Resources::~Resources() {
	/// @todo Destroy texture and memory leak stuffs
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