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
	knockButton = SDL_Rect{
		SCRN_W - 120 - 30,
		SCRN_H - 45 - 15,
		120,
		45
	};
	
	sortButton = SDL_Rect{
		knockButton.x,
		knockButton.y + 30,
		knockButton.w,
		knockButton.h
	};
}


void Window::renderAll() {
	clear();
	renderBackground();
	
	P1->render();
	P2->render();
	gDeck->render();
	gDiscard->render();
	renderButtons();
	
	
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
	SDL_Color textColor{0x00, 0x00, 0x00, 0xFF};
	SDL_Surface* textSurface = TTF_RenderText_Blended( // Create temp Surface for text
		gAssets->briefFont,
		"Hello", 
		textColor
	);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface( // Convert it to a texture
		renderer,
		textSurface
	);
	SDL_Rect textPos = SDL_Rect{
		10,
		10,
		textSurface->w, 
		textSurface->h
	}; // Text position
	
	SDL_RenderCopy(gWindow->getRenderer(),textTexture , NULL, &textPos);
	
	drawAButton(
		gAssets->uiSheets[UIC_BLUE],
		gAssets->uiClippings[1],
		5, 7, 
		knockButton
	);
	
	drawAButton(
		gAssets->uiSheets[UIC_BLUE],
		gAssets->uiClippings[1],
		5, 7, 
		sortButton
	);
	
	
}


void Window::drawAButton(SDL_Texture* tex, SDL_Rect src, int h_p, int w_p, SDL_Rect dest) {
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