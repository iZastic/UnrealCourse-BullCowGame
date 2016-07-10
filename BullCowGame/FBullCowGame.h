/*
	This class contains the game logic for Bulls and Cows.
	Bulls and Cows is based on the game Mastermind.
*/

#pragma once
#include <string>
#include <map>

#define TMap std::map

using FString = std::string;
using int32 = int;

// All values initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	INVALID,
	OK,
	NOT_ISOGRAM,
	WRONG_LENGTH,
	NOT_LOWERCASE
};

class FBullCowGame
{
public:
	FBullCowGame();

	void NewGame();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString*) const;
	FBullCowCount SumbitValidGuess(FString*);

private:
	FString MyHiddenWord;
	int32 MyCurrentTry;
	bool bGameIsWon;

	bool IsIsogram(FString*) const;
	bool IsLowercase(FString*) const;
};
