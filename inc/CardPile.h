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

#ifndef CARDPILE_H_INC
#define CARDPILE_H_INC

#include <vector>

extern const int CARD_W;
extern const int CARD_H;
extern const int CARD_PAD;

/// @brief the Suits of a card
enum Suits {
	SUIT_CLUBS,
	SUIT_DIAMONDS,
	SUIT_HEARTS,
	SUIT_SPADES,
	
	SUIT_TOTAL
};

/// @brief The values of a card
enum Ranks {
	RANK_ACE,
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	RANK_9,
	RANK_10,
	RANK_JACK,
	RANK_QUEEN,
	RANK_KING,
	
	RANK_TOTAL
};

/// @brief A card
struct Card {
	Suits suit;
	Ranks rank;
};

/// @brief The card pile types
enum CardPileTypes {
	PILE_DECK,
	PILE_DISCARD,
	
	PILE_TOTAL
};

/// @brief A card pile
class CardPile {
public:
	CardPile(CardPileTypes type);
	~CardPile();
	
	size_t size();
	Card* peek(); 
	
	void shuffle(); ///< Suffle the deck
	void render();  ///< Render the deck
	
	/// @brief Pulls a card from the deck
	/// @warning The card gets removed from the deck
	/// @return Card* The Card pointer
	Card* getACard();
	
	/// @brief Puts a card on the top of the deck
	/// @warning Does not check if \p is nullptr or NULL
	/// @param [in] Card* The Card pointer
	void takeACard(Card* card);
	
	/// @brief checks of our click was on this deck
	/// @param [in] x `int` The x coordinate of the click 
	/// @param [in] y `int` The y cordinate of the click
	bool checkClick(const int x, const int y);
	
private:
	std::vector<Card*> pile; ///< The deck/pile of cards
	CardPileTypes type;      ///< Type of CardPile @todo Convert to bool
	
	SDL_Rect position; ///< Position of the deck on the screen
};

#endif