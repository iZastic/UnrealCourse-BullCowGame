#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
{
	NewGame();
}


void FBullCowGame::NewGame()
{
	MyHiddenWord = "planet"; // Must be a first-order isogram
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


int32 FBullCowGame::GetMaxTries() const
{
	// Returns the number of guesses allowed for the length of the hidden word
	TMap<int32, int32> WordLengthToMaxTries = { { 3, 4 },{ 4, 7 },{ 5, 10 },{ 6, 13 },{ 7, 16 } };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}


int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}


int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}


bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString *Guess) const
{
	if ((*Guess).length() != GetHiddenWordLength()) {
		return EGuessStatus::WRONG_LENGTH;
	}
	else if (!IsIsogram(Guess)) {
		return EGuessStatus::NOT_ISOGRAM;
	}
	else if (!IsLowercase(Guess)) {
		return EGuessStatus::NOT_LOWERCASE;
	}
	else {
		return EGuessStatus::OK;
	}
}


// Receives valid guess, counts bulls and cows, increments try
FBullCowCount FBullCowGame::SumbitValidGuess(FString *Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // Assume guess is the same length

	// Loop through all letters in guess and hidden word
	for (int32 GChar = 0; GChar < WordLength; GChar++)
	{
		for (int32 HChar = 0; HChar < WordLength; HChar++)
		{
			// Compare letters against hidden word
			if ((*Guess)[GChar] == MyHiddenWord[HChar])
			{
				if (GChar == HChar) {
					// Increment bulls if letters are in the correct place
					BullCowCount.Bulls++;
				} else {
					// Increment cows if they exist but in the wrong place
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}

	return BullCowCount;
}


bool FBullCowGame::IsIsogram(FString *Word) const
{
	int32 WordLength = (*Word).length();
	if (WordLength <= 1) {
		return true;
	}

	TMap<char, bool> LetterSeen;
	for (auto Letter : (*Word))
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false; // NOT an isogram if letter already exists
		}
		else {
			LetterSeen[Letter] = true;
		}
	}

	return true;
}


bool FBullCowGame::IsLowercase(FString *Word) const
{
	for (auto Letter : *Word) {
		// Return false if the letter is not lowercase
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
