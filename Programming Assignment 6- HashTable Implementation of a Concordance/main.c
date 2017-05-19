/*
* CS 261 Data Structures
* Assignment 6
* Name: Stephen Townsend
* Date: 3/12/17
*/

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
	// FIXME: implement
	const char* fileName = "input1.txt";
	if (argc > 1)
	{
		fileName = argv[1];
	}
	printf("Opening file: %s\n", fileName);

	clock_t timer = clock();

	HashMap* map = hashMapNew(10);

	// --- Concordance code begins here ---
	// Be sure to free the word after you are done with it here.
	// --- Concordance code ends here ---

	FILE *file = fopen(fileName, "r");
	int *value;

		char* word = nextWord(file);			//Hold word from file

		while (word != NULL)
		{
			if (hashMapContainsKey(map, word) == 0)		//check if table contains word
				hashMapPut(map, word, 1);				//put word in table
			else
			{
				value = hashMapGet(map, word);			//get value
				*value += 1;							//add one to value
				hashMapPut(map, word, *value);			//put new value in table
			}
			free(word);									//free word
			word = nextWord(file);						//set word to next word
		}

		fclose(file);

		for (int i = 0; i < map->capacity; i++)		 //print word and the amount of times it appears
		{
			HashLink* current = map->table[i];
			if (current != NULL)
			{
				while (current)
				{
					printf("%s: %d\n", current->key, current->value);
					current = current->next;
				}
			}
		}
    
    hashMapPrint(map);

    timer = clock() - timer;
    printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
    printf("Number of links: %d\n", hashMapSize(map));
    printf("Number of buckets: %d\n", hashMapCapacity(map));
    printf("Table load: %f\n", hashMapTableLoad(map));
    
    hashMapDelete(map);
    return 0;
}