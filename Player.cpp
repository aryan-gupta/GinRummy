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
using std::cout;
using std::cin;
using std::endl;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;
#include <SDL2/SDL.h>
#include <string.h>
#include <functional>
#include <set>

#include "./inc/main.h"
#include "./inc/Player.h"
#include "./inc/CardPile.h"
#include "./inc/Window.h"
#include "./inc/Resources.h"

const int MCARD_W = 35 *5/8;
const int MCARD_H = 55 *5/8;

Player::~Player() {
	for(Card* tmpCard : hand)
		delete tmpCard; // Delete the cards in our hands
}


void Player::takeCard(Card* card) {
	hand.push_back(card);
}
//#define DEBUG_MELDS

#ifdef DEBUG_MELDS
static std::ostream& operator << (std::ostream& out, Card* card) {
	// this is just a temp function, itll probs be removed in the final version
	static const char* SL[] = {
		"C",
		"D",
		"H",
		"S"
	};
	static const char* RL[] = {
		"A",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"10",
		"J",
		"Q",
		"K",
	};
	out << SL[card->suit] << RL[card->rank];
	
	return out;
}
#endif


void Player::getMelds() {
	typedef std::vector<Meld*> MS; // Meld Stack
	typedef std::vector<MS> MM;    // Meld Matrix
	typedef std::vector<Card*> CS; // Card Stack
	
	for(Meld* m : melds) delete m;
	melds.clear();
	
	MS allMelds;
	CS tmpHand = hand;
	
	#ifdef DEBUG_MELDS
		CLEAR_TERMINAL

		LOGL("OUR HAND")
		for(Card* tmpCard : hand)
			LOG(tmpCard << " ")
		LOG(endl)
	#endif
	
	/// @todo make separate function for the 3 parts of this function
	
	std::sort( // sort the hand by suit then rank, makes it easier to find RUNS
		tmpHand.begin(), tmpHand.end(),
		[](Card* a, Card* b) {
			return (a->suit*RANK_TOTAL + a->rank) < (b->suit*RANK_TOTAL + b->rank);
		}
	);
	
	#ifdef DEBUG_MELDS
		LOGL(endl << "OUR HAND AFTER SORTING BY SUIT")
		for(Card* tmpCard : tmpHand)
			LOG(tmpCard << " ")
		LOG(endl)
	#endif
	
	/** Algorithm for Finding RUNS
		1. Pick first card (C1) in the hand
		2. Compare the next card (C2) with the first card
		3. If C2 is a different suit than C1 then we don't have a RUN
		4. If C2 is not the next rank compared to C1 then we don't have a RUN
		5. If the ranks are the same then go to the next card (C2 -> C3)
		6. Compare the distance between C2 and C1
		7. If it is greater than 2 (so 3 cards), Then we have a RUN
		8. Add it to the list
		9. Start checking again starting from C2 (or the next card not part of the RUN)
	**/
	for(size_t i = 0; i < tmpHand.size(); ++i) {                 // 1
		size_t j = i + 1;
		for(/*blank*/; j < tmpHand.size(); ++j) {                // 2
			if(tmpHand[i]->suit != tmpHand[j]->suit)             // 3
				break;
			
			if(tmpHand[i]->rank != (tmpHand[j]->rank - (j - i))) // 4
				break;
		}                                                        // 5
		
		if(j - i >= 3) {                                         // 6, 7
			allMelds.push_back( new Meld {                       // 8
				MELD_RUN,
				CS(tmpHand.begin() + i, tmpHand.begin() + j)
			});
			// j minus 1 because i is incremented after loop 
			// finishes so we want to compensate for that
			i = j - 1;                                           // 9
		}
	}
	
	std::sort( // Sort the cards by rank then by suit, makes it easier to find SETS
		tmpHand.begin(), tmpHand.end(),
		[](Card* a, Card* b) {
			return (a->rank*SUIT_TOTAL + a->suit) < (b->rank*SUIT_TOTAL + b->suit);
		}
	);
	
	#ifdef DEBUG_MELDS
		LOGL(endl << "OUR HAND AFTER SORTING BY RANK")
		for(Card* tmpCard : tmpHand)
			LOG(tmpCard << " ")
		LOG(endl)
	#endif
	
	/** Algorithm for Finding SETS
		1.  Start at the first card
		2.  Pick the next card
		3.  See if it can form a SETS
		4.  If it can go the next card
		5.  Continue until we cannot create a set
		6.  If we cannot create a SETS
		7.  Then compare the distance between the two cards
		8.  If its 3 or higher then we have a meld
		9.  Add it to the list
		10. Continue Checking
	**/
	for(size_t i = 0; i < tmpHand.size(); ++i) {                // 1
		size_t j = i + 1;                                       // 2
		for(/*blank*/; j < tmpHand.size(); ++j) {               // 4
			if(tmpHand[i]->rank != tmpHand[j]->rank)            // 3
				break;                                          // 6
		}                                                       // 5
		
		if(j - i >= 3) {                                        // 7, 8
			allMelds.push_back( new Meld {                      // 9
				MELD_SET,
				CS(tmpHand.begin() + i, tmpHand.begin() + j)
			});
			// j minus 1 because i is incremented after loop 
			// finishes so we want to compensate for that
			i = j - 1;                                           // 10
		}
	}
	
	// SEE ISSUE #3 ON GITHUB FOR MORE DETAILS
	
	std::stable_sort( // Sort by size of meld, idk why I did it, but i did
		allMelds.begin(), allMelds.end(),
		[](Meld* a, Meld* b) {
			return a->cards.size() > b->cards.size(); // greatest to least
		}
	);
	
	
	
	/** Finding All Combinations for Melds
		1. Add the current Meld (leaf)
		2. If we are at our `maxDepth`
			2a. Add accumulated leaves (or Meld) to the master list 
			2b. collapse our function stack
		3. If there are more leaves after us
		4. Spawn function for each leaf
			4a. The new function stack will start at the next Meld
			4b. At a depth of current depth + 1
			4c. and COPY the accumulated Melds
		5. If there are no more leaves, collapse our function stack
	**/
	/// @todo fix function name to something better
	std::function<void (size_t, int, const int&, MS, MM&)> findAllMeld = 
	[&](size_t start, int depth, const int& maxDepth, MS stack, MM& ps) {
		stack.push_back(allMelds[start]);                      // 1
		
		if(depth == maxDepth) {                                // 2
			ps.push_back(stack);                               // 2a
			return;                                            // 2b
		}
		
		for(size_t i = start + 1; i < allMelds.size(); ++i) {  // 3
			findAllMeld(i, depth + 1, maxDepth, stack, ps);    // 4, 4a, 4b, 4c
		}                                                      // 5
	};
	
	MM ps;    // Possible Melds
	MS stack; // Meld Stack
	for(unsigned maxDepth = 0; maxDepth < allMelds.size(); ++maxDepth) // go through all the depths
		for(size_t start = 0; start < allMelds.size(); ++start) // go through all the starting pos
			findAllMeld(start, 0, maxDepth, stack, ps);
	
	// Function calculates deadwood given a Meld Stack
	std::function<unsigned(MS&)> calcDW = [&](MS& a) {
		unsigned sum = 0; 
		
		for(Meld* m : a) {
			for(Card* c : m->cards) {  // go through all the cards in each meld
				if(c->rank > RANK_JACK) { sum += 10; } // add up its values
				else { sum += c->rank + 1; } // Because RANK_ACE internally 0 and not 1
			}
		}
		
		return sum;
	};
	
	#ifdef DEBUG_MELDS
		LOGL(endl << "BEFORE OPTIMIZING") 
		for(MS& i : ps) { 
			LOGL("A POSSIBLE MELD:" << calcDW(i)) 
			for(auto& j : i) { 
				for(auto k : j->cards) { 
					LOG(k << " "); 
				} 
				cout << endl; 
			} 
		} 
	#endif
	
	/** Removing Illegal Candidates
		1. Go through all the Meld candidates
		2. Stores all the cards in the Meld candidate in a vector
		3. AND a set. Because we are using a set, only one of each Card will be included
		4. If the set and vector's size are equal
		5. Then we are using unique Cards, possible candidate
		6. If not then the Meld candidate is illegal, signal to be removed
		7. Remove all the candidates that were illegal
	**/
	auto idx1 = remove_if(
		ps.begin(), ps.end(),
		[&](MS& curMelds) {                                     // 1
			CS ucVec;
			std::set<Card*> ucSet;
			
			for(Meld* m : curMelds) {
				ucVec.insert(                                   // 2
					ucVec.begin(),
					m->cards.begin(), m->cards.end() /// @todo use push_back for efficiency
				);
				ucSet.insert(m->cards.begin(), m->cards.end()); // 3
			}
			
			if(ucVec.size() == ucSet.size())                    // 4
				return false;                                   // 5
			
			return true;                                        // 6
		}
	);
	ps.erase(idx1, ps.end());                                   // 7
	
	std::sort( // sort remaining meld candidates by deadwood
		ps.begin(), ps.end(),
		[&](MS& a, MS& b) {
			return calcDW(a) > calcDW(b); // highest to lowest
		}
	);
	
	#ifdef DEBUG_MELDS
		LOGL(endl << endl << "AFTER OPTIMIZING") 
		for(MS& i : ps) { 
			LOGL("A POSSIBLE MELD:" << calcDW(i)) 
			for(auto j : i) { 
				for(auto k : j->cards) { 
					LOG(k << " "); 
				} 
				cout << endl; 
			} 
		} 
	#endif
	
	if(ps.size() != 0) {// if we even had any melds, the optimal Meld is the first one
		melds = ps[0]; /// @todo FIX ALL THESE DAMN MEMORY LEAKS
		
		std::for_each(
			allMelds.begin(), allMelds.end(),
			[&](Meld* a) {
				for(Meld* m : melds) {
					if(a == m)
						return;
				}
				delete a;
			}
		);
	}
}


void Player::getDeadwood() {
	// FIND anycard in our hand that not part of meld 
	deadwood = hand; // first copy the hand into deadwood
	
	for(Meld* tmpMeld : melds) {
		for(Card* tmpCard : tmpMeld->cards) { // go through all the cards in the melds
			auto idx = std::remove(deadwood.begin(), deadwood.end(), tmpCard); // remove it from deadwood
			deadwood.erase(idx, deadwood.end());
		}
	}
}


unsigned Player::getNumDeadwood() {
	// FIND how many deadwood do we have in our hand  
	int sum = 0; 
	
	for(unsigned i = 0; i < deadwood.size(); i++) { 
		if(deadwood[i]->rank > RANK_JACK) { 
			sum = sum + 10;
		}	
		else { sum = sum + deadwood[i]->rank + 1; } 
	}
	return sum;
	
}


bool Player::canWeKnock() {
	return getNumDeadwood() < 10;
}


unsigned Player::getPoints() {
	unsigned sum = 0;
	
	/// @todo get Knock Points
	 
	sum += getGin();
	sum += getBigGin();
	
	return sum;
}


Card* Player::getCard(Card* card) { 
	for(unsigned i = 0; i < hand.size(); ++i) // find the card in our hand
		if(card == hand[i]) 
			hand.erase(hand.begin() + i);     // remove card from hand  
	return card; // return the card
}		


unsigned Player::getGin() {
	// when all 10 cards in our hand are parts of melds also have 1 card in deadwood 
	
	if(deadwood.size() == 1) 
		
		return 25;
		
	return 0; 
}


unsigned Player::getBigGin() {
	// When all 10 cards in our hand are parts of melds and the card we just drew are parts of melds - 11 cards total
	if(deadwood.size() == 0) 
	
		return 30;
		
	return 0; 
}