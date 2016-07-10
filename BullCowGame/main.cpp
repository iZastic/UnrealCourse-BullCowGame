/* 
This is the console executable that makes use of the BullCow class.
This acts as the view in the MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// To make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();

// Global game instance
FBullCowGame BCGame;

int main()
{
	bool bPlayAgain = false;

	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);

	return 0;
}


void PrintIntro()
{
	// Introduce the game
	std::cout << FText(100, '\n');
	std::cout << "Welcome to Bulls and Cows, a word guessing game." << std::endl;
	std::cout << "A 'Bull' is a correct letter in the correct place. A 'Cow' is a correct letter in the wrong place." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;

	return;
}


// Loop to complete a single game
void PlayGame()
{
	BCGame.NewGame();

	// Loop while game is NOT won and tries are remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FText Guess = GetValidGuess();

		// Submit valid guess and receive count
		FBullCowCount BullCowCount;
		BullCowCount = BCGame.SumbitValidGuess(&Guess);

		// Print number of bulls and cows
		std::cout << "Bull: " << BullCowCount.Bulls;
		std::cout << ", Cows: " << BullCowCount.Cows;
		std::cout << std::endl << std::endl;
	}

	PrintGameSummary();

	return;
}


FText GetValidGuess()
{
	// Loop until a valid guess is given
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::INVALID;
	do {
		// Get a guess from the player
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// Check guesses are valid
		Status = BCGame.CheckGuessValidity(&Guess);
		switch (Status) {
		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "ERROR: Your guess must be an isogram!";
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "ERROR: Your guess must be lowercase!";
			break;
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "ERROR: Your guess must be " << BCGame.GetHiddenWordLength() << " characters long!";
			break;
		default:
			return Guess;
		}
		std::cout << std::endl << std::endl;
	}
	while (Status != EGuessStatus::OK);

	return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "CONGRADULATIONS - YOU WIN!" << std::endl;
	}
	else
	{
		std::cout << "BETTER LUCK NEXT TIME!" << std::endl;
	}
}

bool AskToPlayAgain()
{
	// Ask the player if they want to play again
	FText Response = "";
	std::cout << "Would you like to play again with the same word? [yes/no]: ";
	std::getline(std::cin, Response);
	std::cout << std::endl;

	return (Response[0] == 'Y' || Response[0] == 'y');
}
