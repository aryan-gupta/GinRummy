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
using std::cout;
using std::cin;
using std::endl;
#include <vector>
using std::vector;

#include ".\inc\main.h"
#include ".\inc\Player.h"
#include ".\inc\CardPile.h"

Player::Player(bool isUser) {
	this->isUser = isUser;
}

vector<Meld> Player::getMelds() {
	
}

void Player::takeCard(Card* card) {
	hand.push_back(card);
}

void Player::doTurn() {
	if(isUser) {
		cout << "I have this many cards: " << hand.size() << endl;
	} else {
		
	}
}