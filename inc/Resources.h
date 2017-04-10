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

#include <SDL2/SDL.h>
#include <SDL2/SDL_TTF.h>

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

enum HelpTextItems {
	HTI_PICK_DECK,
	HTI_PICK_DECK_ERR,
	HTI_PICK_CARD,
	HTI_PICK_CARD_ERR,
	HTI_NOT_YOUR_TURN
};

const char* HELP_TEXT[] = {
	"Its your turn. Pick a deck to pick from...",
	"You MUST draw from either the discard or the stock",
	"Now you must discard a card, or knock if you can",
	"You MUST click on a card, or knock",
	"Its your Opponent's turn"	
};

/// @brief Stores all of our assets
struct Resources {
	Resources();  ///< Load all of our assets
	~Resources(); ///< Destroy our assets
	
	SDL_Texture* cardsSheet;       ///< The texture for our cards
	SDL_Texture* cardsSheetT;
	SDL_Texture* cardBackSheet;    ///< The texture for our backs
	SDL_Rect*    cardClippings;    ///< The card clippings
	SDL_Rect     cardClippingBack; ///< The clippings for our backs
	
	SDL_Texture** uiSheets;    ///< Our array of UI buttons textures
	SDL_Rect*     uiClippings; ///< Our UI button clippings
	
	TTF_Font* buttonFont, ///< Our button font
	        * nFont;      ///< Our normal font
			
	SDL_Texture** helpTexts;
	
	SDL_Rect knockButton, ///< Knock button position
	         sortButton,  ///< Sort button position
	         deadwoodPanel,
	         meldsPanel,
	         helpPanel,
			 knockPos,    ///< Knock text position
			 sortPos,     ///< Sort text position
			 meldTextPos, ///< Meld text position
			 dwTextPos;   ///< Deadwood text position
			 
	SDL_Texture* knockTexture,    ///< Knock text texture
	           * knockTextureST,  ///< 
	           * sortTexture,     ///< Sort text texture
			   * meldTextTexture, ///< Meld text texture
			   * dwTextTexture;   ///< Deadwood text texture
			   
	SDL_Color textColor; ///< Text color
private:
	/// @brief loads an image into a texture
	/// @param [in] file `const char*` The file to load
	/// @return SDL_Texture* The pointer to our texture for the image
	SDL_Texture* load(const char* file);
};

#endif