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

/// @brief The different UI colors
enum UI_Colors {
	UIC_BLUE,
	UIC_GREEN,
	UIC_GREY,
	UIC_RED,
	UIC_YELLOW,
	
	UIC_TOTAL
};

/// @brief Stores all of our assets
struct Resources {
	Resources();  ///< Load all of our assets
	~Resources(); ///< Destroy our assets
	
	SDL_Texture* cardsSheet;       ///< The texture for our cards
	SDL_Texture* cardBackSheet;    ///< The texture for our backs
	SDL_Rect*    cardClippings;    ///< The card clippings
	SDL_Rect     cardClippingBack; ///< The clippings for our backs
	
	SDL_Texture** uiSheets;    ///< Our array of UI buttons textures
	SDL_Rect*     uiClippings; ///< Our UI button clippings
	
	TTF_Font* buttonFont, ///< Our button font
	        * nFont;      ///< Our normal font
private:
	/// @brief loads an image into a texture
	/// @param [in] file `const char*` The file to load
	/// @return SDL_Texture* The pointer to our texture for the image
	SDL_Texture* load(const char* file);
};

#endif