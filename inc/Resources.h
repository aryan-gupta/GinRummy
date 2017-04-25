/* 
 * Copyright (c) 2017 The Cool Group - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by:
 * Harrison Read <hread2@uncc.edu>
 * Pichsapa Kulapruk <pkulapru@uncc.edu>
 * Aryan Gupta <agupta40@uncc.edu>
 * 
 * =============================================================================
 * @author 			The Cool Group
 * @project 			GinRummy 		
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

/// @brief The various help text texts indexes
enum HelpTextItems {
	HTI_PICK_DECK,
	HTI_PICK_DECK_ERR,
	HTI_PICK_CARD,
	HTI_PICK_CARD_ERR,
	HTI_NOT_YOUR_TURN,
	HTI_CANNOT_KNOCK1,
	HTI_CANNOT_KNOCK2, 
	HTI_SHOWMELD,
	
	HTI_TOTAL
};

extern const char* HELP_TEXT[]; ///< The actual help text

/// @brief Stores all of our assets
struct Resources {
	Resources();  ///< Load all of our assets
	~Resources(); ///< Destroy our assets
	
	SDL_Texture* cardsSheet;       ///< The texture for our cards
	SDL_Texture* cardsSheetT;      ///< The Texture of our cards with transparent card background
	SDL_Texture* cardBackSheet;    ///< The texture for our backs
	SDL_Rect*    cardClippings;    ///< The card clippings
	SDL_Rect     cardClippingBack; ///< The clippings for our backs
	
	SDL_Texture** uiSheets;    ///< Our array of UI buttons textures
	SDL_Rect*     uiClippings; ///< Our UI button clippings
	
	TTF_Font* buttonFont, ///< Our button font
	        * nFont;      ///< Our normal font
			
	SDL_Rect knockButton,   ///< Knock button position
	         sortButton,    ///< Sort button position
			 continueButton,
	         deadwoodPanel, ///< Deadwood Panel position
	         meldsPanel,    ///< Melds Panel position
	         helpPanel,     ///< Help panel position
			 knockPos,      ///< Knock text position
			 sortPos,       ///< Sort text position
			 continuePos,
			 meldTextPos,   ///< Meld text position
			 dwTextPos;     ///< Deadwood text position
			 
	SDL_Texture* knockTexture,    ///< Knock text texture
	           * knockTextureST,  ///< Crossed out Knock text texture
	           * sortTexture,     ///< Sort text texture
			   * meldTextTexture, ///< Meld text texture
			   * continueTexture,
			   * dwTextTexture;   ///< Deadwood text texture
			   
	SDL_Color textColor; ///< Text color
private:
	/// @brief loads an image into a texture
	/// @param [in] file `const char*` The file to load
	/// @return SDL_Texture* The pointer to our texture for the image
	SDL_Texture* load(const char* file);
};

#endif