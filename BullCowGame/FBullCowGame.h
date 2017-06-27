/* The game logic (no view code or direct user interaction)
The game is a simple guess word game based on Mastermind
*/

#pragma once
#include <string>

using FString = std::string;
using int32 = int;


struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus //strongly typed enum
{
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
};


class FBullCowGame {
public:
	FBullCowGame(); //constructor 

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool isGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;


	void Reset(FString); 
	
	// counts bulls and cows and increasing turn number assuming valid guess
	FBullCowCount SubmitValidGuess(FString);


private: 
	//see constructor for intiization 
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

};