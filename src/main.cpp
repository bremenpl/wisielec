/*
 *  main.cpp
 *  wisielec
 *
 *  Created by Lukasz Przenioslo on 12-07-03.
 *  Copyright 2012 http://www.blog.przenioslo.eu. All rights reserved.
 *
 */

/* includes, #typedefs and usings */
#include "classesAndFunctions.h"

// main:
int main (void) {
	word word2gues ; // create example of word class.
	
	word2gues.Word_2_Gues() ;
	word2gues.Word_Mash() ;
	
	word2gues.Trace() ;
	Print_Corpse(word2gues.hanglerState); // shows current "hangler state".
	
	while (word2gues.hiddenWord != word2gues.currentWord) {
		if (word2gues.hanglerState == 11) break; // quits while loop.
		word2gues.guessedLetter = word2gues.Typed_Letter() ;
		word2gues.Word_After_Letter() ;
		Print_Corpse(word2gues.hanglerState);
		word2gues.Trace() ;
	}
	
	// final score print.
	word2gues.Final_Score() ;
		
	return 0;
}

