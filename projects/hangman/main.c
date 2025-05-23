#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_WORD_LENGTH 50
#define MAX_TRIES 6

struct WordWithHint {
	char word[MAX_WORD_LENGTH];
	char hint[MAX_WORD_LENGTH];
};

void displayWord(const char word[], const bool guessed[]);

void drawHangman(int tries);

int main()
{
	srand(time(NULL));

	struct WordWithHint wordList[] =
	{
		{"geeks", "computer coding"},
		{"elephant", "A large mammal with trunk"},
		{ "pizza", "A popular Italian dish"},
		{"beach", "Sandy shore by the sea"},
		{"guitar", "A stringed musical instrument"},
		{"hangman", "A word guessing game"},
		{"programming", "The process of writing code"},
		{"computer", "An electronic device for processing data"},
		{"keyboard", "An input device with keys"},
		{"internet", "A global network of computers"},
		{"software", "Programs and applications for computers"}
	};

	int wordIndex = rand() % 4;

	const char* secretWrod = wordList[wordIndex].word;
	const char* hint = wordList[wordIndex].hint;

	int wordLength = strlen(secretWrod);
	char guessedWord[MAX_WORD_LENGTH] = {0};
	bool guessedLetters[26] = {false};

	printf("Welcome to Hangman!\n");
	printf("Hint: %s\n", hint);


	int tries = 0;

	while (tries < MAX_TRIES)
	{
		printf("\n");
		displayWord(guessedWord, guessedLetters);
		drawHangman(tries);

		char guess;
		printf("Enter a letter: ");
		scanf(" %c", &guess);
		guess = tolower(guess);

		if (guessedLetters[guess - 'a'])
		{
			printf("You've already guessed that letter. " 
					"Try again.\n");
			continue;
		}

		guessedLetters[guess - 'a'] = true;

		bool found = false;
		for (int i = 0; i < wordLength; i++)
		{
			if (secretWrod[i] == guess){
				found = true;
				guessedWord[i] = guess;
			}
		}

		if (found)
		{
			printf("Good guess!\n");
		}
		else
		{
			printf("Sorry, the letter '%c' is not in the word. \n",
																guess);
		}

		if (strcmp(secretWrod, guessedWord) == 0)
		{
			printf("\nCongratulations! You've guessed the "
					"word: %s\n",
					secretWrod);
			break;
		}
	}

	if (tries == MAX_TRIES)
	{
		drawHangman(tries);
		printf("\nSorry, you've run out of tries. The word was: %s\n",
				secretWrod);
	}
	return 0;	

}

void displayWord(const char word[], const bool guessed[])
{
	printf("Word: ");
	for (int i = 0; word[i] != '\0'; i++)
	{
		if (guessed[word[i] - 'a'])
		{
			printf("%c ", word[i]);
		}
		else
		{
			printf("_ ");
		}
	}
	printf("\n");
}

void drawHangman(int tries)
{
	const char* hangmanParts[]
        = { "     _________",    "    |         |",
            "    |         O",   "    |        /|\\",
            "    |        / \\", "    |" };
	printf("\n");
	for (int i = 0; i <= tries; i++)
	{
		printf("%s\n", hangmanParts[i]);
	}
}