/*
This is the console excultable that makes use of the bull cow class
This acts as the view in a MVC pattern and is responsible for all user
interation. For Game logic, see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax unreal friendly
using FText = std::string;
using int32 = int;

//function prototypes as outside a class
FString PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instansiate a new game which we re-use across plays

int main() {
	bool bPlayAgain = false;
	do {
		//introduce game
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0; //exit game
}

FString PrintIntro() {

	std::cout << "\nWelcome to Bulls and Cows, a fun word game!\n\n";
	
	std::cout << " ******   **     ** **       **        ********           **     ****     ** *******           ******    *******   **       **  ********" << std::endl;
	std::cout << "/*////** /**    /**/**      /**       **//////           ****   /**/**   /**/**////**         **////**  **/////** /**      /** **//////" << std::endl;
	std::cout << "/*   /** /**    /**/**      /**      /**                **//**  /**//**  /**/**    /**       **    //  **     //**/**   *  /**/**" << std::endl;
	std::cout << "/******  /**    /**/**      /**      /*********        **  //** /** //** /**/**    /**      /**       /**      /**/**  *** /**/*********" << std::endl;
	std::cout << "/*//// **/**    /**/**      /**      ////////**       **********/**  //**/**/**    /**      /**       /**      /**/** **/**/**////////**" << std::endl;
	std::cout << "/*    /**/**    /**/**      /**             /**      /**//////**/**   //****/**    **       //**    **//**     ** /**** //****       /**" << std::endl;
	std::cout << "/******* //******* /********/******** ********       /**     /**/**    //***/*******         //******  //*******  /**/   ///** ********" << std::endl;
	std::cout << "///////   ///////  //////// //////// ////////        //      // //      /// ///////            //////    ///////   //       // ////////\n" << std::endl;

	std::cout << "Tip 1: \tAn isogram (also known as a 'nonpattern word') is a word with no repeating letters.\n";
	std::cout << "Tip 2: \tBULLS = correct letters in the correct places. \n\tCOWS = correct letters in incorrect places.\n";

	std::cout << "\nChoose your level of difficulty (easy, med, hard)\n";
	FString difficulty = "";
	std::getline(std::cin, difficulty);
	std::cout << std::endl;
	BCGame.Reset(difficulty);

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n" << std::endl;;
	
	
	return difficulty;
}

//making a change
//plays a single game to completion
void PlayGame()
{	
	
	int32 MaxTries = BCGame.GetMaxTries();

	//while the game is NOT won and there are still tries remaining
	while(!BCGame.isGameWon() &&  BCGame.GetCurrentTry() <= MaxTries){ 
		FText Guess = GetValidGuess(); 

		//submit valid guess to game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";

	}
	PrintGameSummary();
}

FText GetValidGuess() { //loop until user gives a valid guess

	EGuessStatus Status = EGuessStatus::Invalid;
	FText Guess = "";
	do {
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
	
		//display remaing tries
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) //check for entry errors
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please type in ALL lowercase \n\n";
			break;
		default:
			//assuming that guess us valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until no errors
	return Guess;
}

void PrintGameSummary() {
	if (BCGame.isGameWon()) {
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else {
		std::cout << "Better luck next time!\n";
	}
}
	
bool AskToPlayAgain() {
	std::cout << "Do you want to play again? (y/n) ";
	FText response = "";
	std::getline(std::cin, response);
	return (response[0] == 'y') || (response[0] == 'Y');

}
