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

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include <string>
#include <cmath>

#include "./inc/main.h"
#include "./inc/Window.h"
#include "./inc/Player.h"
#include "./inc/Human.h"
#include "./inc/Opponent.h"
#include "./inc/CardPile.h"
#include "./inc/Resources.h"

const int SCRN_W = 680; /// @todo Make sure that this is a good ratio
const int SCRN_H = 510;

const int WIN_PAD = 15;

const char* HELP_TEXT[] = {
	"Its your turn. Pick a deck to pick from. You can either click on the stock deck or the discard deck.",
	"You MUST draw from either card pile. Please click on either the stock deck or the discard deck.",
	"Now you must discard a card, or knock if you can",
	"You MUST click on a card, or knock if you can. You can knock ONLY if you have less than 10 deadwood.",
	"Its your Opponent's turn.", 
	"You cannot knock right now, You need less than 10 deadwoods to knock",
	"You cannot knock right now, You need to draw card from a deck", 
	"These are the melds, click continue to see points" 
};

Window::Window() {
	if( NULL ==
		(window = SDL_CreateWindow(  // Create our Window
			R_DESCRIPTION,  // Window name
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
	
	for(unsigned* u : roundPoints)
		delete[] u;
}


void Window::knock(int player) { 
	unsigned* pnt;
	
	if(player == PLAYER_1) { // player1 
		pnt = new unsigned[2]{P1->getPoints(), 0};
		 
		int totalDeadwood = abs((int)P1->getNumDeadwood() - (int)P2->getNumDeadwood()); 
		pnt[0] = pnt[0] + totalDeadwood; 
		
	} else { // player2 
		pnt = new unsigned[2]{0, P2->getPoints()};
		
		int totalDeadwood = abs((int)P2->getNumDeadwood() - (int)P1->getNumDeadwood()); 
		pnt[1] = pnt[1] + totalDeadwood; 
	
	}		
	
	roundPoints.push_back(pnt);
	
	soKnocked = true; 
} 


void Window::initWindow() {
	/// @todo remove this later on
}


void Window::renderAll() {
	// does what you think it does
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
	SDL_Rect bg{0, 0, SCRN_W, SCRN_H}; // renders a solid green background
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
		gAssets->knockButton // location
	);
	
	drawAButton(
		gAssets->uiSheets[UIC_BLUE],
		gAssets->uiClippings[0],
		5, 7, 
		gAssets->sortButton
	);
	
	if(P1->canWeKnock()) // if we can knock then render the normal texture
		SDL_RenderCopy(gWindow->getRenderer(), gAssets->knockTexture, NULL, &gAssets->knockPos);
	else // else render the crossed out texture
		SDL_RenderCopy(gWindow->getRenderer(), gAssets->knockTextureST, NULL, &gAssets->knockPos);
	
	SDL_RenderCopy(gWindow->getRenderer(), gAssets->sortTexture, NULL, &gAssets->sortPos);
}


void Window::renderMeldsDeadwood() {
	drawAButton( // draw the panels
		gAssets->uiSheets[UIC_GREY],
		gAssets->uiClippings[1],
		8, 7,
		gAssets->deadwoodPanel
	);

	drawAButton(
		gAssets->uiSheets[UIC_GREY],
		gAssets->uiClippings[1],
		8, 7,
		gAssets->meldsPanel
	);
	
	SDL_RenderCopy(gWindow->getRenderer(), gAssets->meldTextTexture, NULL, &gAssets->meldTextPos); // draw the texts
	SDL_RenderCopy(gWindow->getRenderer(), gAssets->dwTextTexture, NULL, &gAssets->dwTextPos);
}


void Window::renderHelp() {
	drawAButton(
		gAssets->uiSheets[UIC_GREY],
		gAssets->uiClippings[1],
		8, 7,
		gAssets->helpPanel
	);
	
	int cursorx = gAssets->helpPanel.x + 10;
	int cursory = gAssets->helpPanel.y + 10;
	for(int i = 0; HELP_TEXT[helpToRender][i] != '\0'; ++i) { // go through all the letters
		SDL_Surface* tmpS = TTF_RenderGlyph_Blended(gAssets->nFont, HELP_TEXT[helpToRender][i], gAssets->textColor); // create the surface for the character
		SDL_Texture* tmpT = SDL_CreateTextureFromSurface(renderer, tmpS); // convert it to a texture
		SDL_Rect tmpR = {cursorx, cursory, tmpS->w, tmpS->h};// get the position of the character
		SDL_RenderCopy(renderer, tmpT, NULL, &tmpR); // render it
		
		cursorx += tmpS->w + 1; // move the position forward
		
		if(HELP_TEXT[helpToRender][i] == ' ') { // if we just rendered a space
			int j;
			for(j = i + 1; HELP_TEXT[helpToRender][j] != '\0'; ++j) { // find the next space
				if(HELP_TEXT[helpToRender][j] == ' ')
					break;			
			}
			
			std::string s2(HELP_TEXT[helpToRender], i, j - i); // get the next word (space to next space)
			int w, h;
			TTF_SizeText(gAssets->nFont, s2.c_str(), &w, &h); // get how big it will be
			if(cursorx + w > gAssets->helpPanel.x + gAssets->helpPanel.w - 5) { // if it wont fit on the button
				cursorx = gAssets->helpPanel.x + 10; // reset the cursor to the next line
				cursory = cursory + tmpS->h + 3;
			}
		}
		
		SDL_FreeSurface(tmpS); // Free the memory
		SDL_DestroyTexture(tmpT);
	}
}


void Window::changeHelp(HelpTextItems helpToRender) {
	this->helpToRender = helpToRender;
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
	const SDL_Rect &knockButton = gAssets->knockButton;
	// check if the x and y was within the button
	if(    x > knockButton.x
		&& x < knockButton.x + knockButton.w
		&& y > knockButton.y
		&& y < knockButton.y + knockButton.h
	) return true;
	
	return false;
}


bool Window::checkSortClick(const int x, const int y) {
	const SDL_Rect &sortButton = gAssets->sortButton;
	// check if the x and y was within the button
	if(    x > sortButton.x
		&& x < sortButton.x + sortButton.w
		&& y > sortButton.y
		&& y < sortButton.y + sortButton.h
	) return true;
	
	return false;
}


bool Window::checkContinueClick(const int x, const int y) {
	const SDL_Rect &continueButton = gAssets->continueButton;
	// check if the x and y was within the button
	if(    x > continueButton.x
		&& x < continueButton.x + continueButton.w
		&& y > continueButton.y
		&& y < continueButton.y + continueButton.h
	) return true;
	
	return false;
}


void Window::renderFinal(bool displayPoints) {
	// does what you think it does
	clear();
	renderBackground();

	renderHelp();
	
	P1->renderLayoff();
	P2->renderLayoff();
	
	if(displayPoints) {
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xD0);
		SDL_RenderFillRect(renderer, NULL);
		drawAButton(
			gAssets->uiSheets[UIC_BLUE], // sprite sheet
			gAssets->uiClippings[0], // clipping
			5, 7, // border
			gAssets->continueButton // location
		);
		SDL_RenderCopy(gWindow->getRenderer(), gAssets->continueTexture, NULL, &gAssets->continuePos);
		
		SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
		
		// First render the number of deadwood
		SDL_Surface* textSurface = TTF_RenderText_Blended( // Create temp Surface for text
			gAssets->buttonFont,
			("P1 Points: " + std::to_string(roundPoints[roundPoints.size() - 1][0]) + "    P2 Points: " + std::to_string(roundPoints[roundPoints.size() - 1][1])).c_str(), // convert num of deadwood into a string
			textColor
		);
		SDL_Texture* pointsTex = SDL_CreateTextureFromSurface( // Convert it to a texture
			gWindow->getRenderer(),
			textSurface
		);
		SDL_Rect pointsPos = SDL_Rect{ // get the position
			SCRN_W/2 - textSurface->w/2,
			gAssets->continueButton.y + gAssets->continueButton.h + WIN_PAD, // 2 lines of cards plus 3 paddings from the bottom
			textSurface->w, 
			textSurface->h
		};
		
		SDL_FreeSurface(textSurface); // render and free memory
		SDL_RenderCopy(gWindow->getRenderer(), pointsTex, NULL, &pointsPos);
		SDL_DestroyTexture(pointsTex);
	} else {
		drawAButton(
			gAssets->uiSheets[UIC_BLUE], // sprite sheet
			gAssets->uiClippings[0], // clipping
			5, 7, // border
			gAssets->continueButton // location
		);
		SDL_RenderCopy(gWindow->getRenderer(), gAssets->continueTexture, NULL, &gAssets->continuePos);
	}
	
	SDL_RenderPresent(renderer);
}


void Window::finalizeRound() {
	// calculate pre layoff points
	// get melds and deadwood of each player
	// layoff cards
	// calculate final points
	// wait until we quit or restart the game
	layoffCards();
	showPoints();
}


void Window::layoffCards() {
	
    gWindow->changeHelp(HTI_SHOWMELD); // Change help text	
	bool finished = false;
	SDL_Event event;

	while(!finished) {
		
		renderFinal(false);
		
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					quit(0x03);
				break;
				
				case SDL_MOUSEBUTTONUP: {
					int x, y;
					SDL_GetMouseState(&x, &y);
					
					if(checkContinueClick(x, y)) {
						finished = true;
					}
				} break;
			}
		}
	}
}


void Window::showPoints() {
	bool finished = false;
	SDL_Event event;
	LOGL("POINTS: " << roundPoints[roundPoints.size() - 1][0] << " \t " << roundPoints[roundPoints.size() - 1][1]);
	
	while(!finished) {
		
		renderFinal(true);
		
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					quit(0x04);
				break;
				
				case SDL_MOUSEBUTTONUP: {
					int x, y;
					SDL_GetMouseState(&x, &y);
					
					if(checkContinueClick(x, y)) {
						finished = true;
					}
				} break;
			}
		}
	}
}