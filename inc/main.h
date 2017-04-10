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

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <vector>

// Forward Declarations
class CardPile;
class Player;
class Window;
struct Resources;
struct Card;

extern const int NUM_CARDS_PER; ///< Number of cards per player (default 10)

extern CardPile* gDeck;    ///< The CardPile for the main deck
extern CardPile* gDiscard; ///< The discard pile

extern Player* P1;
extern Player* P2;

extern Window* gWindow;
extern Resources* gAssets;


// =========================
/// @retval -0x101 initSDL();
/// @retval -0x102 Window::Window();
int main(int argc, char* argv[]); ///< Program Entry (if anyone wants to elaborate, feel free to)

void initSDL();       ///< Inits the graphics
void createPlayers(); ///< creates the players
void dealCards();     ///< Deals the cards
void quit(int code);  ///< Deletes variables and exits

unsigned getDeadwood(const std::vector<Card*> &cards);

#endif // MAIN_H_INCLUDED