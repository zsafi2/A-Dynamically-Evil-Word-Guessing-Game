#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Pattern_struct {
    char* pat;  //string pattern - exs: "hello", "-ell-", "-----"
    int count;  //frequency of pattern in the current word list
    int changes;//number of occurences of new letter in this pattern
} Pattern;

// function to add words to the words array by allocating and reallocating the array of strings
void addWord(char*** words, int* numWords, int* maxWords, char* newWord)
{
    // Check if we need to reallocate the array
    if (*numWords >= *maxWords) {
        
        // Double the capacity
        *maxWords *= 2;
        
        // Allocate memory for the new array of pointers
        char** newWords = (char**)malloc(sizeof(char*) * (*maxWords));
        
        // Copy the old data to the new array
        for (int i = 0; i < *numWords; i++)
        {
            newWords[i] = (*words)[i];
        }
        
        // Free the old array of pointers
        free(*words);
        
        // Update the words pointer to point to the new array
        *words = newWords;
    }
    
    // Allocate memory for the new word and copy it
    char* wordCopy = (char*) malloc((strlen(newWord) + 1) * sizeof(char));
    
    strcpy(wordCopy, newWord);
    wordCopy[strlen(wordCopy)] = '\0';
    
    // Add the new word to the array
    (*words)[*numWords] = wordCopy;
    
    // Increment the number of words
    (*numWords)++;
}

 // function to return the number of difference between two strings
int strNumMods(char* str1, char* str2)
{
    int numMods = 0; // veriable to store the differences between two strings

    if (strlen(str1) <= strlen(str2) )
    {
        // iterate until the end of the str1
        while (*str1 != '\0')
        {
            if (*str1 != *str2)
            {
                numMods++; // if an element doesnt match increment numMods
            }

            str1++; // increment the pointer to point to the next element.
            str2++;
        }
        
        // iterate until the end of str2
        while (*str2 != '\0')
        {
            numMods++; // becuase str2 is bigger in length every extra element is a difference so increment numMods
            str2++;
        }
        
    }
    
    // do the same process if str1 is bigger then str 2
    else if(strlen(str1) > strlen(str2))
    {
        while (*str2 != '\0')
        {
            if (*str1 != *str2)
            {
                numMods++;
            }

            str1++;
            str2++;
        }
        while (*str1 != '\0')
        {
            numMods++;
            str1++;
        }
        
    }

    return numMods;
}

// function to return the index where the change happens when comapring two strings
int strDiffInd(char* str1, char* str2)
{
    int indDiff = 0; //index were the difference happens

    // if str1 is bigger or equal to str2
    if (strlen(str1) <= strlen(str2) )
    {
        // go through until the end of str1
        while (*str1 != '\0')
        {
            if (*str1 != *str2)
            {
                return indDiff; // if a character is different in the strings simply return the index
            }

            // otherwise increment increment str1 and str2 pointer and the index
            str1++;
            str2++;
            indDiff++;
        }

        return indDiff;
    }
    
    // if str 1 is bigger then str2 do the same thing
    else if(strlen(str1) > strlen(str2))
    {
        while (*str2 != '\0')
        {
            if (*str1 != *str2)
            {
                return indDiff;
            }

            str1++;
            str2++;
            indDiff++;
        }
        return indDiff;
    }

    return indDiff;
}

//function to build the pattern and choose the final pattern to present to the user and update the wordList array
void buildPattern(char*** wordList, Pattern* wordPatterns, char patternCpy[], char finalPattern[], int* numWords, int wordSize, int* PatternSize, char guess)
{
    bool patternExist = false;// veriable to test to check if a pattern already exist in the word patterns
    *PatternSize = 0;// veriable for the size of wordPatterns array of structs
    int patternChanges = 0;// veriable to change the veriable changes to zero
    int size = 0;// size of wordList 1
    
    // array to store the original finalpattern
    char SecondpatternCpy[wordSize + 1];
    strcpy(SecondpatternCpy, finalPattern);
    SecondpatternCpy[wordSize] = '\0';

    char** wordList1 = malloc((*numWords) * sizeof(char*));// string array to help reallocate wordList and remove the not required strings
    Pattern* wordPatterns1 = malloc((*numWords) * sizeof(Pattern)); // to store unique patterns

    for (int i = 0; i < *numWords; i++)
    {
        patternExist = false;
        patternChanges = 0;
        
        strcpy(finalPattern, SecondpatternCpy);
        finalPattern[wordSize] = '\0';

        // go through each element in worList and match with guess letter and then store in the final pattern
        for (int k = 0; k < wordSize; k++)
        {
            if((*wordList)[i][k] == guess)
            {
                finalPattern[k] = guess;
                patternChanges++;
            }
        }

        // store the final pattern in unique patterns array
        wordPatterns1[i].pat = malloc((wordSize + 1) * sizeof(char));
        strcpy(wordPatterns1[i].pat, finalPattern);
        wordPatterns1[i].pat[wordSize] = '\0';
        
        // go through the wordPatterns array if it is a copy pattern just increment the count of patterns
        for (int j = 0; j < *PatternSize; j++)
        {
            if (strcmp(finalPattern, wordPatterns[j].pat) == 0)
            {
                (wordPatterns[j].count) += 1;
                patternExist = true;
                break;
            }
        }

        // else allocate space for a new pattern string in struct and update the changes count and pattern
        if (patternExist == false)
        {
            wordPatterns[*PatternSize].pat = malloc((wordSize + 1) * sizeof(char));
            strcpy(wordPatterns[*PatternSize].pat, finalPattern);
            wordPatterns[*PatternSize].pat[wordSize] = '\0';
            wordPatterns[*PatternSize].count += 1;
            wordPatterns[*PatternSize].changes = patternChanges;
            (*PatternSize)++;
        }
    }

    // find the max count in the word Pattern array
    int maxCount = -1;
    for (int i = 0; i < *PatternSize; i++)
    {
        if (maxCount < wordPatterns[i].count)
        {
            maxCount = wordPatterns[i].count;
            strcpy(finalPattern, wordPatterns[i].pat);
        }
    }
   
    // find the one with minimum changes
    int minChanges = wordPatterns[0].changes;
    for (int i = 0; i < *PatternSize; i++)
    {
        if(wordPatterns[i].count == maxCount)
        {
            if (wordPatterns[i].changes < minChanges)
            {
                minChanges = wordPatterns[i].changes;
                strcpy(finalPattern, wordPatterns[i].pat);
            }

        }
    }
    
    // find the pattern with earliest apperance of the guess letter int the pattern
    int earliestInstance = -1;
    for (int i = 0; i < *PatternSize; i++)
    {
        if(wordPatterns[i].count == maxCount && wordPatterns[i].changes == minChanges)
        {
            for (int j = 0; j < wordSize; j++)
            {
                if (wordPatterns[i].pat[j] != '-' && (earliestInstance == -1 || j < earliestInstance))
                {
                    earliestInstance = j;
                    strcpy(finalPattern, wordPatterns[i].pat);
                }
            }
        }
    }
    finalPattern[wordSize] = '\0';
    
    
    // all the strings which have the final pattern store in in worList1
    for (int i = 0; i < *numWords; i++)
    {
        if(strcmp(wordPatterns1[i].pat, finalPattern) == 0)
        {
            wordList1[size] = malloc((wordSize + 1) * sizeof(char));
            strcpy(wordList1[size], (*wordList)[i]);
            wordList1[size][wordSize] = '\0';
            size++;
        }
    }

    // remove all the pattern from wordList original array and also wordPatterns1 array
    for (int i = 0; i < *numWords; i++)
    {
        free((*wordList)[i]);
    }
    free(*wordList);

    // remove all the pattern from wordPatterns1 original array and also wordPatterns1 array
    for(int i = 0; i < *numWords; i++)
    {
        free(wordPatterns1[i].pat);
    }
    free(wordPatterns1);
    
    // change the worlist size to the size of wordList1 and allocate new space in wordList
    *numWords = size;
    *wordList = malloc(*numWords * sizeof(char*));
    
    // copy all the elemets from word list1 to wordList
    for (int i = 0; i < *numWords; i++)
    {
        (*wordList)[i] = malloc((wordSize + 1) * sizeof(char));
        strcpy((*wordList)[i], wordList1[i]);
    }

    // free all the memeory for wordList1
    for(int i = 0; i < *numWords; i++)
    {
        free(wordList1[i]);
    }
    free(wordList1);
    
}

//function to print the guessed letter array in ascending to descending order.
int compare(const void *a, const void *b)
{
    return (*(char *)a - *(char *)b);
}


int main(int argc, char* argv[])
{

    printf("Welcome to the (Evil) Word Guessing Game!\n\n");
    
    bool solved = false;
    
    // intialize every command to default values as described the instructions
    int wordSize = 5;
    int numGuesses = 26;
    char statsMode[4] = "OFF";
    char wordListMode[4] = "OFF";
    char letterListMode[4] = "OFF";
    char patternListMode[4] = "OFF";
    char verboseMode[4] = "OFF";
    char extensionMode[4] = "OFF";
    bool invalidCommand = false;
    
    
    // go through the command line arguments
    for (int i = 1; i < argc; i++)
    {
        // read the command if it is "-n" it indicates the size of word now change the value of wordSize
        if (strcmp(argv[i], "-n") == 0)
        {
            wordSize = atoi(argv[i+1]);
        }

        // dont consider the number go forward
        else if(wordSize == atoi(argv[i]))
        {
            invalidCommand = false;
        }

        // do the same thing identify if it is the right letter and changes the values for number of guesses
        else if(strcmp(argv[i], "-g") == 0)
        {
            numGuesses = atoi(argv[i+1]);
        }

        else if(numGuesses == atoi(argv[i]))
        {
            invalidCommand = false;
        }

        // continue to cover all the cases
        else if(strcmp(argv[i], "-s") == 0)
        {
            strcpy(statsMode, "ON");
        }

        else if(strcmp(argv[i], "-w") == 0)
        {
            strcpy(wordListMode, "ON");
        }
        
        else if(strcmp(argv[i], "-l") == 0)
        {
            strcpy(letterListMode, "ON");
        }

        else if(strcmp(argv[i], "-p") == 0)
        {
            strcpy(patternListMode, "ON");
        }

        // if -v is identified the changes all the modes to on
        else if(strcmp(argv[i], "-v") == 0)
        {
            strcpy(letterListMode, "ON");
            strcpy(statsMode, "ON");
            strcpy(wordListMode, "ON");
            strcpy(patternListMode, "ON");
        }

        // if none of these letters are entered changes the invalid command to true
        else
        {
            invalidCommand = true;
        }
        
    }

    // if invalid command has been entered end the game and show the message
    if (invalidCommand == true)
    {
        printf("Invalid command-line argument.\n");
        printf("Terminating program...\n");
        return -1;
    }

    // take care of incorrect size of wordSize and num of guesses
    else if(wordSize < 2 || wordSize > 29)
    {
        printf("Invalid word size.\n");
        printf("Terminating program...\n");
        return -1;
    }

    else if(numGuesses <= 0)
    {
        printf("Invalid number of guesses.\n");
        printf("Terminating program...\n");
        return -1;
    }
    
    // otherwise print the setting to the user
    else
    {
        printf("Game Settings:\n");
        printf("  Word Size = %d\n", wordSize);
        printf("  Number of Guesses = %d\n", numGuesses);
        printf("  View Stats Mode = %s\n", statsMode);
        printf("  View Word List Mode = %s\n", wordListMode);
        printf("  View Letter List Mode = %s\n", letterListMode);
        printf("  View Pattern List Mode = %s\n", patternListMode);
    }
    
    // allocate space of 4 strings in the wordList array
    int capacity = 4;
    char** wordList = (char**) malloc(capacity*sizeof(char*));
    
    // open the dictionary file
    FILE* infile = NULL;
    infile = fopen("dictionary.txt", "r");
    
    // veriables to store the word, find the total words maximum owrd and maximum word size
    char word[100];
    int numWords = 0;
    int totalWords = 0;
    int maxSizeWord = 0;
    char maxWord[50];

    // go through each line of the dictionary file
    while (fscanf(infile, "%s ", word) == 1)
    {
        // if it is equal to the required size add it to the array
        if (strlen(word) == wordSize)
        {
            addWord(&wordList, &numWords, &capacity, word);
        }

        // find the maximum word
        if (strlen(word) > maxSizeWord)
        {
            maxSizeWord = strlen(word);
            strcpy(maxWord, word);
        }

        // account for total words
        totalWords++;
    }

    fclose(infile);

    // if no words of the size were found
    if (numWords == 0)
    {
        printf("The dictionary contains %d words total.\n", totalWords);
        printf("The longest word %s has 29 chars.\n", maxWord);
        printf("The dictionary contains %d words of length %d.\n", numWords, wordSize);
        printf("Max size of the dynamic words array is %d.\n", capacity);
        printf("Words of length %d:\n", wordSize);
        printf("Dictionary has no words of length %d.\n", wordSize);
        printf("Terminating program...\n");
        return -1;
    }

    // if stats mode or verbrose mode is on show the specifications
    if (strcmp(statsMode, "ON") == 0 || strcmp(verboseMode, "ON") == 0)
    {
        printf("The dictionary contains %d words total.\n", totalWords);
        printf("The longest word %s has 29 chars.\n", maxWord);
        printf("The dictionary contains %d words of length %d.\n", numWords, wordSize);
        printf("Max size of the dynamic words array is %d.\n", capacity);
    }

    // show all the words on specific length
    if (strcmp(wordListMode, "ON") == 0 || strcmp(verboseMode, "ON") == 0)
    {
        printf("Words of length %d:\n", wordSize);
        for (int i = 0; i < numWords; i++)
        {
            printf("  %s\n", wordList[i]);
        }
    }
    
    // show the intial empty pattern  with dashes
    printf("The word pattern is: ");
    char patternCpy[wordSize + 1]; // +1 for the null-terminator

    memset(patternCpy, '-', wordSize);
    patternCpy[wordSize] = '\0'; // Null-terminate the string
    printf("%s", patternCpy);
    printf("\n\n");
    
    // declare veriables
    char guess;
    bool repeatedGuess = false;
    int guessIndex = 0;
    int PatternSize = 0;
    char guessExausted[wordSize + 1];
    bool invalidLetter = false;
   
    // intiazlie final pattern with dashes
    char finalPattern[wordSize + 1];
    memset(finalPattern, '-', wordSize);
    finalPattern[wordSize] = '\0';
    
    char finalPattern1[wordSize + 1];
    memset(finalPattern1, '-', wordSize);
    finalPattern1[wordSize] = '\0';
    
    // array to account for all previous guesses
    char * guessArr;
    guessArr = malloc(numGuesses * sizeof(char));

    // wordPattern array that stores the patters of unique patterns for the user
    Pattern* wordPattern = malloc(numWords * sizeof(Pattern));
    for (int i = 0; i< numWords; i++)
    {
        wordPattern[i].count = 0;
    }
    
    // main do while loop of the game loop runs until all the guesses are exausted
    do
    {
        
        solved = true;

        if (!invalidLetter && !repeatedGuess)
        {
            printf("Number of guesses remaining: %d\n", numGuesses);
        }
        
        invalidLetter = false;
        repeatedGuess = false;

        // display the game accordingly
        if(strcmp(letterListMode, "ON") == 0 || strcmp(verboseMode, "ON") == 0)
        {
            printf("Previously guessed letters: ");
            qsort(guessArr, guessIndex, sizeof(char), compare);
            for (int i = 0; i < guessIndex; i++)
            {
                printf("%c ", guessArr[i]);
            }
            printf("\n");
        }
        
        printf("Guess a letter (# to end game): ");
        scanf(" %c", &guess);
        
        for (int i = 0; i < guessIndex; i++)
        {
            if (guessArr[i] == guess)
            {
                repeatedGuess = true;
                break;
            }
        }

        if(repeatedGuess)
        {
            printf("\nLetter previously guessed...\n");
            repeatedGuess = true;
        }

        // check if the guess in between a and z small letter and it is not a repeated guess
        if ((guess >= 'a' && guess <= 'z') && !repeatedGuess)
        {
            // build all the patterns and update the wordList array
            buildPattern(&wordList, wordPattern, patternCpy, finalPattern, &numWords, wordSize, &PatternSize, guess);
            
            // check the mode and show the data as required
            if (strcmp(patternListMode, "ON") == 0 || strcmp(verboseMode, "ON") == 0)
            {
                printf("\nAll patterns for letter %c:\n", guess);
                for(int i = 0; i < PatternSize; i++)
                {
                    printf("  %-10s      count = %-6d    changes = %-2d\n", wordPattern[i].pat, wordPattern[i].count, wordPattern[i].changes);
                }
            }

            // change all the counts to zero
            for(int i = 0; i < numWords; i++)
            {
                wordPattern[i].count = 0;
            }
            
            // free all the patterns
            for (int i = 0; i < PatternSize; i++)
            {
                free(wordPattern[i].pat);
            }
           
            // see if any changes happend to final Pattern if no changes happend decrement the num of guesses
            if (strcmp(finalPattern1, finalPattern) == 0)
            {
                printf("\nOops, there are no %c's. You used a guess.\n", guess);
                numGuesses--;
            }

            // if changes happened show the message
            else
            {
                printf("\nGood guess! The word has at least one %c.\n", guess);
            }
            
            // store the previous final pattern
            strcpy(finalPattern1, finalPattern);
            finalPattern1[wordSize] = '\0';
            
            // store the first element of wordList incase if all the guesses are exauseted
            if (wordList != NULL)
            {
                strcpy(guessExausted, wordList[0]);
                guessExausted[wordSize] = '\0';
            }

            // if there are no dashes left int the final pattern the game is solved break
            for (int i = 0; i < wordSize; i++)
            {
                if (!isalpha(finalPattern[i]))
                {
                    solved = false;
                    break;
                }
            }

            guessArr[guessIndex] = guess;// add the guess to the guess arr
            guessIndex++;

            // show the data according to the modes
            if (strcmp(statsMode, "ON") == 0 || strcmp(verboseMode, "ON") == 0)
            {
                printf("Number of possible words remaining: %d\n", numWords);
            }

            if (strcmp(wordListMode, "ON") == 0 || strcmp(verboseMode, "ON") == 0)
            {
                printf("Possible words are now:\n");
                for (int i = 0; i < numWords; i++)
                {
                    printf("  %s\n", wordList[i]);
                }
            }

            printf("The word pattern is: %s\n\n", finalPattern);
            
            if(solved)
            {
                printf("You solved the word!\n");
                printf("The word is: %s\n", finalPattern);
                printf("Game over.\n");
                break;
            }
        }

        // if hashes are entered end the game
        else if(guess == '#')
        {
            printf("\nTerminating game...\n");
            break;
        }
        
        else
        {
            if (!repeatedGuess)
            {
                printf("\nInvalid letter...\n");
                invalidLetter = true;
            }
        }
        
    } while (numGuesses != 0);

    // if all the guesses are exaused just show a word from the remainign wordList array
    if(numGuesses == 0)
    {
        printf("You ran out of guesses and did not solve the word.\n");
        printf("The word is: %s\n", guessExausted);
        printf("Game over.\n\n");
    }

    // free all the allocated memeory
    for (int i = 0; i < numWords; i++)
    {
        free(wordList[i]);
    }
    
    free(wordList);
    free(wordPattern);
    free(guessArr);
    
    return 0;
}






