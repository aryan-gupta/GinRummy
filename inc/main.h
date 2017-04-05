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
// Forward Declarations
class CardPile;
class Player;
struct Meld;

extern const int NUM_PLAYERS;   ///< Number of players (keep it at 4 please)
extern const int NUM_CARDS_PER; ///< Number of cards per player (default 7)

extern CardPile* gDeck;    ///< The CardPile for the main deck
extern CardPile* gDiscard; ///< The discard pile

extern std::vector<Meld*> melds;      ///< The melds on the board
extern std::vector<Player*> gPlayers; ///< The players

// =========================

int main(int argc, char* argv[]); ///< Program Entry (if anyone wants to elaborate, feel free to)

void initSDL();       ///< Inits the graphics
void createPlayers(); ///< creates the players
void dealCards();     ///< Deals the cards

#endif // MAIN_H_INCLUDED