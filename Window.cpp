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
#include <SDL.h>
#include <SDL_Image.h>
//#include <SDL_TTF.h>

#include ".\inc\main.h"
#include ".\inc\Window.h"
#include ".\inc\Player.h"
#include ".\inc\CardPile.h"
#include ".\inc\Resources.h"

const int SCRN_W = 680; /// @todo Make sure that this is a good ratio
const int SCRN_H = 510;

const int WIN_PAD = 15;

Window::Window() {
	if( NULL ==
		(window = SDL_CreateWindow(  // Create our Window
			R_PRGMNAME,  // Window name
			SDL_WINDOWPOS_UNDEFINED,  // Window position (x)
			SDL_WINDOWPOS_UNDEFINED,  // Window position (y)
			SCRN_W, SCRN_H,  // Screen size
			SDL_WINDOW_SHOWN //| SDL_WINDOW_INPUT_GRABBED // | SDL_WINDOW_FULLSCREEN // Window flags
		))
	) EXIT("SDL Create Window Failed! " << SDL_GetError(), -0x102);
	
	if( NULL ==
		(renderer = SDL_CreateRenderer( // Create our main renderer
			window, -1,
			SDL_RENDERER_ACCELERATED // Renderer flags
		))
	) EXIT("SDL Create Renderer Failed! " << SDL_GetError(), -0x102);
	
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}


Window::~Window() {
	SDL_DestroyRenderer(renderer); renderer = nullptr; // Destroy our main renderer
	SDL_DestroyWindow(window); window = nullptr; // Destroy our main window
	
	SDL_DestroyTexture(background);
}


void Window::initWindow() {
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
		MCARD_H*3 + WIN_PAD*2 + 5
	};
	
	helpPanel = SDL_Rect{
		SCRN_W/2 - (CARD_PAD*(NUM_CARDS_PER - 1) + CARD_W)/2,
		SCRN_H/2 + WIN_PAD*3/2,
		CARD_PAD*(NUM_CARDS_PER - 1) + CARD_W,
		MCARD_H*5/2
	};
	
	textColor = SDL_Color{0x00, 0x00, 0x00, 0xFF}; // black text color
	SDL_Surface* textSurface = TTF_RenderText_Blended( // Create temp Surface for text
		gAssets->buttonFont,
		"knock", 
		textColor
	);
	knockTexture = SDL_CreateTextureFromSurface( // Convert it to a texture
		renderer,
		textSurface
	);
	knockPos = SDL_Rect{ // Text position
		knockButton.x - textSurface->w/2 + knockButton.w/2,
		knockButton.y - textSurface->h/2 + knockButton.h/2 + 4,
		textSurface->w, 
		textSurface->h
	};
	
	SDL_FreeSurface(textSurface); // free the memory
	
	textSurface = TTF_RenderText_Blended( // Create temp Surface for text
		gAssets->buttonFont,
		"sort", 
		textColor
	);
	sortTexture = SDL_CreateTextureFromSurface( // Convert it to a texture
		renderer,
		textSurface
	);
	sortPos = SDL_Rect{
		sortButton.x - textSurface->w/2 + sortButton.w/2,
		sortButton.y - textSurface->h/2 + sortButton.h/2 + 4,
		textSurface->w, 
		textSurface->h
	}; // Text position
	
	SDL_FreeSurface(textSurface);
	
	textSurface = TTF_RenderText_Blended( // Create temp Surface for text
		gAssets->nFont,
		"Melds:", 
		textColor
	);
	meldTextTexture = SDL_CreateTextureFromSurface( // Convert it to a texture
		renderer,
		textSurface
	);
	meldTextPos = SDL_Rect{
		WIN_PAD + 5,
		SCRN_H - MCARD_H*5 - WIN_PAD*7, /// @todo Make this y pos relative, It works for now tho
		textSurface->w, 
		textSurface->h
	}; // Text position
	
	SDL_FreeSurface(textSurface);
	
	textSurface = TTF_RenderText_Blended( // Create temp Surface for text
		gAssets->nFont,
		"Deadwood:", 
		textColor
	);
	dwTextTexture = SDL_CreateTextureFromSurface( // Convert it to a texture
		renderer,
		textSurface
	);
	dwTextPos = SDL_Rect{
		WIN_PAD + 5,
		SCRN_H - MCARD_H*2 - WIN_PAD*3,
		textSurface->w, 
		textSurface->h
	}; // Text position
	
	SDL_FreeSurface(textSurface);
	
	TTF_SetFontStyle(gAssets->buttonFont, TTF_STYLE_STRIKETHROUGH);
	textColor = SDL_Color{0xFF, 0x00, 0x00, 0xFF}; // black text color
	textSurface = TTF_RenderText_Blended( // Create temp Surface for text
		gAssets->buttonFont,
		"knock", 
		textColor
	);
	knockTextureST = SDL_CreateTextureFromSurface( // Convert it to a texture
		renderer,
		textSurface
	);
	
	SDL_FreeSurface(textSurface); // free the memory
	
}


void Window::renderAll() {
	clear();
	renderBackground();
	
	gDeck->render();
	gDiscard->render();
	renderButtons();
	renderMeldsDeadwood();
	renderHelp();
	
	P1->render();
	P2->render();
	
	SDL_RenderPresent(renderer);
}


void Window::renderBackground() {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x99, 0x00, 0xFF); // http://www.colorhexa.com/009900
	SDL_Rect bg{0, 0, SCRN_W, SCRN_H};
	SDL_RenderFillRect(renderer, &bg);
}


void Window::clear() {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); // Black
	SDL_RenderClear(renderer);
}


void Window::renderButtons() {
	drawAButton(
		gAssets->uiSheets[UIC_BLUE], // sprite sheet
		gAssets->uiClippings[0], // clipping
		5, 7, // border
		knockButton // location
	);
	
	drawAButton(
		gAssets->uiSheets[UIC_BLUE],
		gAssets->uiClippings[0],
		5, 7, 
		sortButton
	);
	
	SDL_RenderCopy(gWindow->getRenderer(), knockTextureST, NULL, &knockPos);
	SDL_RenderCopy(gWindow->getRenderer(), sortTexture, NULL, &sortPos);
}


void Window::renderMeldsDeadwood() {
	drawAButton(
		gAssets->uiSheets[UIC_GREY],
		gAssets->uiClippings[1],
		8, 7,
		deadwoodPanel
	);

	drawAButton(
		gAssets->uiSheets[UIC_GREY],
		gAssets->uiClippings[1],
		8, 7,
		meldsPanel
	);
	
	SDL_RenderCopy(gWindow->getRenderer(), meldTextTexture, NULL, &meldTextPos);
	SDL_RenderCopy(gWindow->getRenderer(), dwTextTexture, NULL, &dwTextPos);
}


void Window::renderHelp() {
	drawAButton(
		gAssets->uiSheets[UIC_GREY],
		gAssets->uiClippings[1],
		8, 7,
		helpPanel
	);
}

void Window::drawAButton(SDL_Texture* tex, SDL_Rect src, int h_p, int w_p, SDL_Rect dest) {
	// Im way to lazy to comment this algorithm. I created it a long time ago,
	// and im just copying it from an older project
	int x_i, y_i, w, h, x_f, y_f;
	
	x_i = src.x;
	y_i = src.y;
	w = src.w;
	h = src.h;
	
	x_f = x_i + w;
	y_f = y_i + h;
	
	SDL_Rect clip_topleft     = SDL_Rect{x_i, y_i, w_p, h_p};
	SDL_Rect clip_topright    = SDL_Rect{x_f - w_p, y_i, w_p, h_p};
	SDL_Rect clip_bottomleft  = SDL_Rect{x_i, y_f - h_p, w_p, h_p};
	SDL_Rect clip_bottomright = SDL_Rect{x_f - w_p, y_f - h_p, w_p, h_p};
	
	SDL_Rect clip_top    = SDL_Rect{x_i + w_p, y_i, w - 2*w_p, h_p};
	SDL_Rect clip_left   = SDL_Rect{x_i, y_i + h_p, w_p, h - 2*h_p};
	SDL_Rect clip_right  = SDL_Rect{x_f - w_p, y_i + h_p, w_p, h - 2*h_p};
	SDL_Rect clip_bottom = SDL_Rect{x_i + w_p, y_f - h_p, w - 2*w_p, h_p};
	
	SDL_Rect clip_center = SDL_Rect{x_i + w_p, y_i + h_p, w - 2*w_p, h - 2*h_p};

	x_i = dest.x;
	y_i = dest.y;
	w = dest.w;
	h = dest.h;
	
	x_f = x_i + w;
	y_f = y_i + h;
	
	SDL_Rect pos_topleft     = SDL_Rect{x_i, y_i, w_p, h_p};
	SDL_Rect pos_topright    = SDL_Rect{x_f - w_p, y_i, w_p, h_p};
	SDL_Rect pos_bottomleft  = SDL_Rect{x_i, y_f - h_p, w_p, h_p};
	SDL_Rect pos_bottomright = SDL_Rect{x_f - w_p, y_f - h_p, w_p, h_p};
	
	SDL_Rect pos_top    = SDL_Rect{x_i + w_p, y_i, w - 2*w_p, h_p};
	SDL_Rect pos_left   = SDL_Rect{x_i, y_i + h_p, w_p, h - 2*h_p};
	SDL_Rect pos_right  = SDL_Rect{x_f - w_p, y_i + h_p, w_p, h - 2*h_p};
	SDL_Rect pos_bottom = SDL_Rect{x_i + w_p, y_f - h_p, w - 2*w_p, h_p};
	
	SDL_Rect pos_center = SDL_Rect{x_i + w_p, y_i + h_p, w - 2*w_p, h - 2*h_p};
	
	SDL_RenderCopy(renderer, tex, &clip_topleft, &pos_topleft);
	SDL_RenderCopy(renderer, tex, &clip_topright, &pos_topright);
	SDL_RenderCopy(renderer, tex, &clip_bottomleft, &pos_bottomleft);
	SDL_RenderCopy(renderer, tex, &clip_bottomright, &pos_bottomright);
	
	SDL_RenderCopy(renderer, tex, &clip_top, &pos_top);
	SDL_RenderCopy(renderer, tex, &clip_left, &pos_left);
	SDL_RenderCopy(renderer, tex, &clip_right, &pos_right);
	SDL_RenderCopy(renderer, tex, &clip_bottom, &pos_bottom);
	
	SDL_RenderCopy(renderer, tex, &clip_center, &pos_center);
}


bool Window::checkKnockClick(const int x, const int y) {
	if(    x > knockButton.x
		&& x < knockButton.x + knockButton.w
		&& y > knockButton.y
		&& y < knockButton.y + knockButton.h
	) return true;
	
	return false;
}


bool Window::checkSortClick(const int x, const int y) {
	if(    x > sortButton.x
		&& x < sortButton.x + sortButton.w
		&& y > sortButton.y
		&& y < sortButton.y + sortButton.h
	) return true;
	
	return false;
}