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

#ifndef RESOURCES_H_INC
#define RESOURCES_H_INC

#include <SDL.h>
#include <SDL_TTF.h>

#define GCI(s, r) (s*RANK_TOTAL)+r

enum UI_Colors {
	UIC_BLUE,
	UIC_GREEN,
	UIC_GREY,
	UIC_RED,
	UIC_YELLOW,
	
	UIC_TOTAL
};

struct Resources {
	Resources();
	~Resources();
	
	SDL_Texture* cardsSheet;
	SDL_Texture* cardBackSheet;
	SDL_Rect*    cardClippings;
	SDL_Rect     cardClippingBack;
	
	SDL_Texture** uiSheets;
	SDL_Rect*     uiClippings;
	
	TTF_Font* buttonFont, * nFont;
private:
	SDL_Texture* load(const char* file);
};

#endif