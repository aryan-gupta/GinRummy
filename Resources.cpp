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

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include <SDL2/SDL_TTF.h>
#include <iostream>

#include "./inc/main.h"
#include "./inc/Resources.h"
#include "./inc/CardPile.h"
#include "./inc/Window.h"

static const char* CARDS_SHEET      = "..//res//sprites//Spritesheets//playingCards.png";
static const char* CARDS_SHEET_BACK = "..//res//sprites//Spritesheets//playingCardBacks.png";
static const char* BRIEF_FONT       = "..//res//brief_font.ttf";
static const char* UI_SHEETS[] = {
	"..//res//sprites//Spritesheets//blueSheet.png",
	"..//res//sprites//Spritesheets//greenSheet.png",
	"..//res//sprites//Spritesheets//greySheet.png",
	"..//res//sprites//Spritesheets//redSheet.png",
	"..//res//sprites//Spritesheets//yellowSheet.png",
};

Resources::Resources() {
	cardClippingBack = SDL_Rect{280, 570, 140, 190};
	
	uiSheets = new SDL_Texture*[UIC_TOTAL];
	for(int i = 0; i < UIC_TOTAL; ++i)
		uiSheets[i] = load(UI_SHEETS[i]);
	
	uiClippings = new SDL_Rect[2];
	uiClippings[0] = SDL_Rect{0, 49, 190, 45};
	uiClippings[1] = SDL_Rect{190, 98, 100, 100}; //x="190" y="98" width="100" height="100"
	
	buttonFont = TTF_OpenFont(BRIEF_FONT, 25); // Load the font
	if(buttonFont == NULL)
		EXIT("Font Opening Failed" << TTF_GetError(), -0x20A);

	nFont = TTF_OpenFont(BRIEF_FONT, 12); // Load the font
	if(nFont == NULL)
		EXIT("Font Opening Failed" << TTF_GetError(), -0x20A);
	
	cardsSheet = load(CARDS_SHEET);
	cardBackSheet = load(CARDS_SHEET_BACK);
	
	cardClippings = new SDL_Rect[SUIT_TOTAL * RANK_TOTAL]; // 52 cards;
	cardClippings[GCI(SUIT_CLUBS,    RANK_ACE  )] = SDL_Rect{560,  570, 140, 190};
	cardClippings[GCI(SUIT_CLUBS,    RANK_2    )] = SDL_Rect{280, 1140, 140, 190};
	cardClippings[GCI(SUIT_CLUBS,    RANK_3    )] = SDL_Rect{700,  190, 140, 190};
	cardClippings[GCI(SUIT_CLUBS,    RANK_4    )] = SDL_Rect{700,    0, 140, 190};
	cardClippings[GCI(SUIT_CLUBS,    RANK_5    )] = SDL_Rect{560, 1710, 140, 190};
	cardClippings[GCI(SUIT_CLUBS,    RANK_6    )] = SDL_Rect{560, 1520, 140, 190};
	cardClippings[GCI(SUIT_CLUBS,    RANK_7    )] = SDL_Rect{560, 1330, 140, 190};
	cardClippings[GCI(SUIT_CLUBS,    RANK_8    )] = SDL_Rect{560, 1140, 140, 190};
	cardClippings[GCI(SUIT_CLUBS,    RANK_9    )] = SDL_Rect{560,  950, 140, 190};
	cardClippings[GCI(SUIT_CLUBS,    RANK_10   )] = SDL_Rect{560,  760, 140, 190};
	cardClippings[GCI(SUIT_CLUBS,    RANK_JACK )] = SDL_Rect{560,  380, 140, 190};
	cardClippings[GCI(SUIT_CLUBS,    RANK_QUEEN)] = SDL_Rect{560,  190, 140, 190};
	cardClippings[GCI(SUIT_CLUBS,    RANK_KING )] = SDL_Rect{560,    0, 140, 190};

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
	
	cardClippings[GCI(SUIT_HEARTS,   RANK_ACE  )] = SDL_Rect{140, 1330, 140, 190};
	cardClippings[GCI(SUIT_HEARTS,   RANK_2    )] = SDL_Rect{700,  380, 140, 190};
	cardClippings[GCI(SUIT_HEARTS,   RANK_3    )] = SDL_Rect{280,  950, 140, 190};
	cardClippings[GCI(SUIT_HEARTS,   RANK_4    )] = SDL_Rect{280,  760, 140, 190};
	cardClippings[GCI(SUIT_HEARTS,   RANK_5    )] = SDL_Rect{280,  570, 140, 190};
	cardClippings[GCI(SUIT_HEARTS,   RANK_6    )] = SDL_Rect{280,  380, 140, 190};
	cardClippings[GCI(SUIT_HEARTS,   RANK_7    )] = SDL_Rect{280,  190, 140, 190};
	cardClippings[GCI(SUIT_HEARTS,   RANK_8    )] = SDL_Rect{280,    0, 140, 190};
	cardClippings[GCI(SUIT_HEARTS,   RANK_9    )] = SDL_Rect{140, 1710, 140, 190};
	cardClippings[GCI(SUIT_HEARTS,   RANK_10   )] = SDL_Rect{140, 1520, 140, 190};
	cardClippings[GCI(SUIT_HEARTS,   RANK_JACK )] = SDL_Rect{140, 1140, 140, 190};
	cardClippings[GCI(SUIT_HEARTS,   RANK_QUEEN)] = SDL_Rect{140,  950, 140, 190};
	cardClippings[GCI(SUIT_HEARTS,   RANK_KING )] = SDL_Rect{140,  760, 140, 190};
	
	cardClippings[GCI(SUIT_SPADES,   RANK_ACE  )] = SDL_Rect{  0,  570, 140, 190};
	cardClippings[GCI(SUIT_SPADES,   RANK_2    )] = SDL_Rect{140,  380, 140, 190};
	cardClippings[GCI(SUIT_SPADES,   RANK_3    )] = SDL_Rect{140,  190, 140, 190};
	cardClippings[GCI(SUIT_SPADES,   RANK_4    )] = SDL_Rect{140,    0, 140, 190};
	cardClippings[GCI(SUIT_SPADES,   RANK_5    )] = SDL_Rect{  0, 1710, 140, 190};
	cardClippings[GCI(SUIT_SPADES,   RANK_6    )] = SDL_Rect{  0, 1520, 140, 190};
	cardClippings[GCI(SUIT_SPADES,   RANK_7    )] = SDL_Rect{  0, 1330, 140, 190};
	cardClippings[GCI(SUIT_SPADES,   RANK_8    )] = SDL_Rect{  0, 1140, 140, 190};
	cardClippings[GCI(SUIT_SPADES,   RANK_9    )] = SDL_Rect{  0,  950, 140, 190};
	cardClippings[GCI(SUIT_SPADES,   RANK_10   )] = SDL_Rect{  0,  760, 140, 190};
	cardClippings[GCI(SUIT_SPADES,   RANK_JACK )] = SDL_Rect{  0,  380, 140, 190};
	cardClippings[GCI(SUIT_SPADES,   RANK_QUEEN)] = SDL_Rect{  0,  190, 140, 190};
	cardClippings[GCI(SUIT_SPADES,   RANK_KING )] = SDL_Rect{  0,    0, 140, 190};

	SDL_Surface* tmpSurface = IMG_Load(CARDS_SHEET);
	if(tmpSurface == nullptr)
		EXIT("Could not load " << CARDS_SHEET << IMG_GetError(), -0x101)
	
	SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0xFF, 0xFF, 0xFF));
	
	cardsSheetT = SDL_CreateTextureFromSurface ( // Set the Player's texture
		gWindow->getRenderer(),
		tmpSurface
	);
	
	SDL_FreeSurface(tmpSurface); tmpSurface = nullptr;
}

Resources::~Resources() {
	SDL_DestroyTexture(cardsSheet); cardsSheet = nullptr;
	SDL_DestroyTexture(cardBackSheet); cardBackSheet = nullptr;
	
	delete[] cardClippings;
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