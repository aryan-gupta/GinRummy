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

#ifndef MAIN_H_INC
#define MAIN_H_INC

class Card;

extern const int SHUFFLE_TIMES;
extern std::vector<Card*> gCards;


int main(int argc, char* argv[]);
void create52Cards();

#endif // MAIN_H_INCLUDED