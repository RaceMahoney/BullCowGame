#pragma once

#include "FBullCowGame.h"
#include <map>

//to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

void FBullCowGame::Reset(FString difficulty) {

	if (difficulty == "easy") {
		const FString HIDDEN_WORD = "ant"; //MUST be an isogram
		MyHiddenWord = HIDDEN_WORD;
	}
	else if (difficulty == "med") {
		const FString HIDDEN_WORD = "race"; //MUST be an isogram
		MyHiddenWord = HIDDEN_WORD;
	}
	else if (difficulty == "hard") {
		const FString HIDDEN_WORD = "whisk"; //MUST be an isogram
		MyHiddenWord = HIDDEN_WORD;
	}
	
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

FBullCowGame::FBullCowGame() { //default construcotr 
	//Reset();
}

int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}
bool FBullCowGame::isGameWon() const {return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthMaxTries{ {3,4}, {4,7}, {5,10}, {6,16},{7,20} };
	return WordLengthMaxTries[MyHiddenWord.length()];

}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) //if the guess isnt an isogram, 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) //if the guess isnt lowercase, 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) //if the guess legnth is wrong, 
	{
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}

//recives a valid guess, increments turn, and returns count ^^
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming the same length as Guess

	//loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		//compare letters against the hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			//if they match 
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // incriment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	//treat 0 and 1 letter words as isograms 
	if (Word.length() <= 1) { return true; }

	//setup TMap
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)		//for all letters of the word
	{
		Letter = tolower(Letter);	//handle mixed case
		if (LetterSeen[Letter]) {
			return false;			//we DO NOT have an isogram
		}
		else {
			LetterSeen[Letter] = true;	//add letter to map
		}
	}
	return true; //for example in cases where /0 is entered 
}

bool FBullCowGame::IsLowercase(FString Word) const {
	for (auto Letter : Word) {
		//if not a lowercase letter
		if (!islower(Letter))
			return false;

	}
	return true;
}




