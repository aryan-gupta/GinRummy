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

#include "./inc/main.h"
#include "./inc/Resources.h"
#include "./inc/CardPile.h"
#include "./inc/Player.h"
#include "./inc/Window.h"

static const char* CARDS_SHEET      = "..\\res\\sprites\\Spritesheets\\playingCards.png";
static const char* CARDS_SHEET_BACK = "..\\res\\sprites\\Spritesheets\\playingCardBacks.png";
static const char* BRIEF_FONT       = "..\\res\\brief_font.ttf";
static const char* UI_SHEETS[] = {
	"..\\res\\sprites\\Spritesheets\\blueSheet.png",
	"..\\res\\sprites\\Spritesheets\\greenSheet.png",
	"..\\res\\sprites\\Spritesheets\\greySheet.png",
	"..\\res\\sprites\\Spritesheets\\redSheet.png",
	"..\\res\\sprites\\Spritesheets\\yellowSheet.png"
};



Resources::Resources() {
	cardClippingBack = SDL_Rect{280, 570, 140, 190}; // Clipping for the back of the card
	cardsSheet = load(CARDS_SHEET); // the sheet for the card fronts
	cardBackSheet = load(CARDS_SHEET_BACK); // the sheet for the card backs
	
	{ // UI elements
		uiSheets = new SDL_Texture*[UIC_TOTAL]; // the sheets for the UI buttons and such
		for(int i = 0; i < UIC_TOTAL; ++i)
			uiSheets[i] = load(UI_SHEETS[i]); // load all of them
		
		uiClippings = new SDL_Rect[2]; // clipping for the UI elements we are using
		uiClippings[0] = SDL_Rect{0, 49, 190, 45}; // Blue buttons
		uiClippings[1] = SDL_Rect{190, 98, 100, 100}; //Grey panels
	}
	
	{ // fonts
		buttonFont = TTF_OpenFont(BRIEF_FONT, 25); // Load the font for the buttons
		if(buttonFont == NULL)
			EXIT("Font Opening Failed" << TTF_GetError(), -0x20A);

		nFont = TTF_OpenFont(BRIEF_FONT, 12); // Load the font for the text and stuff
		if(nFont == NULL)
			EXIT("Font Opening Failed" << TTF_GetError(), -0x20A);
	}
	
	{ // The clippings for all the cards
		cardClippings = new SDL_Rect[SUIT_TOTAL * RANK_TOTAL]; // 52 cards clippings
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
		cardClippings[GCI(SUIT_CLUBS,    RANK_QUEEN)] = SDL_Rect{560,    0, 140, 190};
		cardClippings[GCI(SUIT_CLUBS,    RANK_KING )] = SDL_Rect{560,  190, 140, 190};

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
		cardClippings[GCI(SUIT_DIAMONDS, RANK_QUEEN)] = SDL_Rect{280, 1330, 140, 190};
		cardClippings[GCI(SUIT_DIAMONDS, RANK_KING )] = SDL_Rect{280, 1520, 140, 190};
		
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
		cardClippings[GCI(SUIT_HEARTS,   RANK_QUEEN)] = SDL_Rect{140,  760, 140, 190};
		cardClippings[GCI(SUIT_HEARTS,   RANK_KING )] = SDL_Rect{140,  950, 140, 190};
		
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
		cardClippings[GCI(SUIT_SPADES,   RANK_QUEEN)] = SDL_Rect{  0,    0, 140, 190};
		cardClippings[GCI(SUIT_SPADES,   RANK_KING )] = SDL_Rect{  0,  190, 140, 190};
	}
	
	{ // Load the cards and set the white as transparent
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
	
	{ // Button positions
		knockButton = SDL_Rect{ // location of our knock button
			SCRN_W - 120 - 45,
			SCRN_H - 45*2 - 45,
			120,
			45
		};
		
		sortButton = SDL_Rect{ // location of our sort button
			knockButton.x,
			knockButton.y + knockButton.h + 30,
			knockButton.w,
			knockButton.h
		};
		
		deadwoodPanel = SDL_Rect{
			WIN_PAD - 5,
			SCRN_H - MCARD_H*2 - WIN_PAD*3 - 5,
			SCRN_W/2 - (CARD_PAD*(NUM_CARDS_PER - 1) + CARD_W)/2 - WIN_PAD*3 + 5,
			MCARD_H*2 + WIN_PAD*2 + 5
		};
		meldsPanel = SDL_Rect{
			WIN_PAD - 5,
			SCRN_H - MCARD_H*5 - WIN_PAD*7 - 5,
			SCRN_W/2 - (CARD_PAD*(NUM_CARDS_PER - 1) + CARD_W)/2 - WIN_PAD*3 + 5,
			MCARD_H*3 + WIN_PAD*5/2 + 5
		};
		
		helpPanel = SDL_Rect{
			SCRN_W/2 - (CARD_PAD*(NUM_CARDS_PER - 1) + CARD_W)/2,
			SCRN_H/2 + WIN_PAD*3/2,
			CARD_PAD*(NUM_CARDS_PER - 1) + CARD_W,
			MCARD_H*5/2
		};
		
		continueButton = SDL_Rect{
			SCRN_W/2 - knockButton.w*3/4,
			CARD_H + WIN_PAD*4,
			knockButton.w*3/2,
			knockButton.h*3/2
		};
	}
	
	{ // Textures for the text used in the game
		textColor = SDL_Color{0x00, 0x00, 0x00, 0xFF}; // black text color
		SDL_Surface* textSurface;
	
		{ // knock texture
			textSurface = TTF_RenderText_Blended( // Create temp Surface for text
				buttonFont,
				"knock", 
				textColor
			);
			knockTexture = SDL_CreateTextureFromSurface( // Convert it to a texture
				gWindow->getRenderer(),
				textSurface
			);
			knockPos = SDL_Rect{ // Text position
				knockButton.x - textSurface->w/2 + knockButton.w/2,
				knockButton.y - textSurface->h/2 + knockButton.h/2,
				textSurface->w, 
				textSurface->h
			};
			
			SDL_FreeSurface(textSurface); // free the memory
		}
		
		{ // sort texture
			textSurface = TTF_RenderText_Blended( // Create temp Surface for text
				buttonFont,
				"sort", 
				textColor
			);
			sortTexture = SDL_CreateTextureFromSurface( // Convert it to a texture
				gWindow->getRenderer(),
				textSurface
			);
			sortPos = SDL_Rect{
				sortButton.x - textSurface->w/2 + sortButton.w/2,
				sortButton.y - textSurface->h/2 + sortButton.h/2,
				textSurface->w, 
				textSurface->h
			}; // Text position
			
			SDL_FreeSurface(textSurface);
		}
		
		{ // melds texture
			textSurface = TTF_RenderText_Blended( // Create temp Surface for text
				nFont,
				"Melds:", 
				textColor
			);
			meldTextTexture = SDL_CreateTextureFromSurface( // Convert it to a texture
				gWindow->getRenderer(),
				textSurface
			);
			meldTextPos = SDL_Rect{
				WIN_PAD + 5,
				SCRN_H - MCARD_H*5 - WIN_PAD*7,
				textSurface->w, 
				textSurface->h
			}; // Text position
			
			SDL_FreeSurface(textSurface);
		}
		
		{ // deadwood texture
			textSurface = TTF_RenderText_Blended( // Create temp Surface for text
				nFont,
				"Deadwood:", 
				textColor
			);
			dwTextTexture = SDL_CreateTextureFromSurface( // Convert it to a texture
				gWindow->getRenderer(),
				textSurface
			);
			dwTextPos = SDL_Rect{
				WIN_PAD + 5,
				SCRN_H - MCARD_H*2 - WIN_PAD*3,
				textSurface->w, 
				textSurface->h
			}; // Text position
			
			SDL_FreeSurface(textSurface);
		}
		
		{ // Continue texture
			textSurface = TTF_RenderText_Blended( // Create temp Surface for text
				buttonFont,
				"Continue", 
				textColor
			);
			continueTexture = SDL_CreateTextureFromSurface( // Convert it to a texture
				gWindow->getRenderer(),
				textSurface
			);
			continuePos = SDL_Rect{
				continueButton.x - textSurface->w/2 + continueButton.w/2,
				continueButton.y - textSurface->h/2 + continueButton.h/2,
				textSurface->w, 
				textSurface->h
			}; // Text position
			
			SDL_FreeSurface(textSurface);
		}
		
		TTF_SetFontStyle(buttonFont, TTF_STYLE_STRIKETHROUGH);
		textColor = SDL_Color{0xFF, 0x00, 0x00, 0xFF}; // black text color
		{ // knock crossed out texture
			textSurface = TTF_RenderText_Blended( // Create temp Surface for text
				buttonFont,
				"knock", 
				textColor
			);
			knockTextureST = SDL_CreateTextureFromSurface( // Convert it to a texture
				gWindow->getRenderer(),
				textSurface
			);
			
			SDL_FreeSurface(textSurface); // free the memory	
		}
		
		TTF_SetFontStyle(buttonFont, TTF_STYLE_NORMAL);
		textColor = SDL_Color{0x00, 0x00, 0x00, 0xFF}; // black text color
	}
}


Resources::~Resources() {
	SDL_DestroyTexture(cardsSheet);
	SDL_DestroyTexture(cardsSheetT);
	SDL_DestroyTexture(cardBackSheet); 
	delete[] cardClippings;
	for(int i = 0; i < UIC_TOTAL; ++i) SDL_DestroyTexture(uiSheets[i]);
	delete[] uiSheets;
	delete[] uiClippings;
	TTF_CloseFont(buttonFont);
	TTF_CloseFont(nFont);
	SDL_DestroyTexture(knockTexture);
	SDL_DestroyTexture(knockTextureST);
	SDL_DestroyTexture(sortTexture);
	SDL_DestroyTexture(meldTextTexture);
	SDL_DestroyTexture(dwTextTexture);
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