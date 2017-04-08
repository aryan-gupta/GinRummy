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

#include ".\inc\main.h"
#include ".\inc\Window.h"
#include ".\inc\Player.h"
#include ".\inc\CardPile.h"

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


Window::~Window() {}


void Window::initWindow() {}


void Window::renderAll() {
	clear();
	renderBackground();
	
	P1->render();
	P2->render();
	gDeck->render();
	gDiscard->render();
	
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