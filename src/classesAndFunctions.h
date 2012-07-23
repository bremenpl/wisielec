/*
 *  classesAndFunctions.h
 *  wisielec
 *
 *  Created by Lukasz Przenioslo on 12-07-03.
 *  Copyright 2012 http://www.blog.przenioslo.eu. All rights reserved.
 *
 */

/* includes, #typedefs and usings etc.*/
typedef unsigned char u8;
#include <iostream>
using namespace std;
const short FOREVER = 1;

// function declarations & classes definitions.
void Print_Corpse (int missedLetters); // prints current hangler state.
u8 Letter_Lowerer (u8 letter2BLowered); // lowers input letters.

class word {
	string letterGuessedWrong;
	string letterGuessedRight;
	bool letterAppeared;
	volatile int wordSize; 
	
public:
	u8 guessedLetter;
	string currentWord;
	string hiddenWord;
	volatile int hanglerState;
	
	void Word_2_Gues (void) ; // takes the word from user.
	u8 Typed_Letter (void) ; // checks is typed char is ok.
	void Word_Mash (void) ; // creates hidden string.
	void Trace (void) ; // spits out word status.
	void Word_After_Letter (void) ; // creates hidden string.
	void Final_Score (void) ; // spits if user won or lost.
}; // end of class def.
