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

#define GCI(s, r) (s*RANK_TOTAL)+r

struct Resources {
	Resources();
	~Resources();
	
	SDL_Texture* cardsSheet;
	SDL_Texture* cardBackSheet;
	SDL_Rect*    cardClippings;
	SDL_Rect     cardClippingBack;
	
private:
	SDL_Texture* load(const char* file);
};

#endif