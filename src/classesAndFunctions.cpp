/*
 *  classesAndFunctions.cpp
 *  wisielec
 *
 *  Created by Lukasz Przenioslo on 12-07-03.
 *  Copyright 2012 http://www.blog.przenioslo.eu. All rights reserved.
 *
 */

/* includes, #typedefs and usings etc.*/
#include "classesAndFunctions.h"

// function definitions:
void Print_Corpse (int missedLetters) {	
	// hangler creation definition, depending of numbers or wrong guest letters:
	string loss[12] = {
		/*  0 */		"\n \n\n\n\n\n\n",
		/*  1 */		"\n \n\n\n\n\n\n \\ ",
		/*  2 */		"\n|\n|\n|\n|\n|\n|\n|\\",
		/*  3 */		"\n|\n|/\n|\n|\n|\n|\n|\\",
		/*  4 */		"\n|--------\n|/\n|\n|\n|\n|\n|\\",
		/*  5 */		"\n|--------\n|/     |\n|\n|\n|\n|\n|\\",
		/*  6 */		"\n|--------\n|/     |\n|      O\n|\n|\n|\n|\\",
		/*  7 */		"\n|--------\n|/     |\n|      O\n|      |\n|      |\n|\n|\\",
		/*  8 */		"\n|--------\n|/     |\n|      O\n|     /|\n|      |\n|\n|\\",
		/*  9 */		"\n|--------\n|/     |\n|      O\n|     /|\\\n|      |\n|\n|\\",
		/* 10 */		"\n|--------\n|/     |\n|      O\n|     /|\\\n|      |\n|     /\n|\\",
		/* 11 */		"\n|--------\n|/     |\n|      O\n|     /|\\\n|      |\n|     / \\\n|\\"
	};
	
	// hangler print:
	cout << loss[missedLetters] << endl;
}

u8 Letter_Lowerer (u8 letter2BLowered) {
	// usage of Letter_Lowerer to lower letters.
	if ((letter2BLowered >= 'A') && (letter2BLowered <= 'Z'))
		letter2BLowered += 32;
	return letter2BLowered;
}

// word class function declarations:
void word::Word_Mash () {	
	for (int i = 0; i < wordSize; i++) {
		if ((currentWord[i] == ' ') || (currentWord[i] == '-')) // show spaces in hidden word.
			hiddenWord += '-';
		else hiddenWord += '_'; // if no spaces add lower case line.
	}
	
	hanglerState = 0; // starts hangler.
}

void word::Trace () {
	//  letter count starts here.
	int lettersLeft = 0;
	for (int i = 0; i < wordSize ; i++)
		if (hiddenWord[i] == '_') lettersLeft++;
	
	//  word count starts here.
	int numberOfWords = 0;
	if (lettersLeft == 0) numberOfWords = 0;
	
	bool spaceFound = false;
	bool   gapFound = false;
	for (volatile int i = 0; i < wordSize ; i++) {
		if (hiddenWord[i] == '_') gapFound = true;
		if ((hiddenWord[i] == '-' || hiddenWord[i+1] == '\0') && gapFound == true) spaceFound = true;
		if (spaceFound == true) {
			numberOfWords++;
			gapFound = false;
			spaceFound = false;
		}
	}
	
	// trace of current word status.
	cout << hiddenWord << "\tDo odgadniecia zostalo liter: " << lettersLeft
	<< "\twyrazow: " << numberOfWords << endl;
	if (letterAppeared == true) // doesnt work for 100%, cba fixin.
		cout << "ta litera juz byla" << endl;
	cout << "zlych strzalow: " << hanglerState << endl;
}

void word::Word_2_Gues () {
	while (FOREVER) {
		cout << "Podaj fraze do odgadniecia\t" ;
		cin  >> currentWord ; // word which has 2 b guessed is stored in currentWord string.
		
		// word lenght stored in wordSize.
		for (wordSize = 0; ; wordSize++) {
			if (currentWord[wordSize] == '\0') break; // break for loop when end of sign symbol found.
		}
		
		// usage of Letter_Lowerer to lower letters.  
		for (int i = 0; i < wordSize; i++)
			currentWord[i] = Letter_Lowerer(currentWord[i]);
		
		// If user types wrong character - loop.
		bool phaseAllRight = true;
		for (int i = 0; i < wordSize; i++) {
			if (((currentWord[i] < 'a') || (currentWord[i] > 'z')) && currentWord[i] != '-')
				phaseAllRight = false;
			if (currentWord[i] == '-' && (i == (wordSize-1) || i == 0))
				phaseAllRight = false;
		}
		
		if (phaseAllRight == false) 
			cout << "Podana fraza zawiera zakazane znaki, " 
			<< "lub odstep na poczatku/ koncu" << endl << "Jeszcze raz ";
		else break; // If all chars r ok - break while loop.
	}
}

u8 word::Typed_Letter () {
	u8 tempLetter;
	while (FOREVER) {
		cout << "Zgadnij litere:\t" ;
		cin >> tempLetter;
		
		// usage of Letter_Lowerer to lower letters.
		tempLetter = Letter_Lowerer(tempLetter);
		
		// If user types wrong character - loop.
		bool phaseAllRight = true;
		if (tempLetter < 'a' || tempLetter > 'z')
			phaseAllRight = false;
		if (phaseAllRight == false) 
			cout << "Podana fraza zawiera zakazane znaki" << endl << "Jeszcze raz ";
		else break; // If all chars r ok - break while loop.
	}
	return tempLetter;
}

void word::Word_After_Letter () {
	// replacement the lowercased-lines with current guessed letters.
	letterAppeared = false;
	for (int i = 0; ; i++)
		if (guessedLetter == letterGuessedWrong[i] || guessedLetter == letterGuessedRight[i])
			letterAppeared = true;
		else if (letterGuessedWrong[i] == '\0')
			break;
	if (letterAppeared == false) {
		bool letterFound = false;
		for (int i = 0; i < wordSize; i++) {
			if (guessedLetter == currentWord[i]) {
				hiddenWord[i] = currentWord[i];
				letterGuessedRight += hiddenWord[i];
				letterFound = true;
			}
		}
		// when letterAppeared == false new letter is added to letterGuessedWrong string.
		if (letterFound == false && letterAppeared == false) {
			hanglerState++;
			letterGuessedWrong += guessedLetter;
		}
	}
}

void word::Final_Score () {
	if (hanglerState == 11)
		cout << "\nDefeat" << endl << "Poprawna odpowiedz: " << currentWord << endl;
	else if ((hanglerState == 0) && (hiddenWord == currentWord))
		cout << "\nFlawless Victory" << endl;
	else if ((hanglerState != 0) && (hiddenWord == currentWord))
		cout << "\nVictory" << endl;
}
