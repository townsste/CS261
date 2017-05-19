/* CS261- Assignment 1 - Q.5*/
/* Name: Stephen Townsend
 * Date: 1/22/17
 * Solution description: Convert a string of lowercase or uppercase into sticky caps
 */
 
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************************
**							char toUpperCase(char ch)
**	Converts ch to upper case, assuming it is in lower case currently
*****************************************************************************************/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*****************************************************************************************
**							char toLowerCase(char ch)
**	Converts ch to lower case, assuming it is in upper case currently
*****************************************************************************************/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

/*****************************************************************************************
**							void sticky(char* word)
**	Converts a word to sticky caps
*****************************************************************************************/
void sticky(char* word){

	int i = 0;
	int count = 0;
	
	while (word[i] != '\0') //count the string leters
	{
		count++;			//Increment count
		i++;				//Increment array position
	}

	i = 0;				//reset array position marker
	while (i < count)	//Loop entire array
	{
		
		if (word[i] >= 'a' && word[i] <= 'z' && i % 2 == 0)			//Check if even leters are lowercase
		{
			word[i] = toUpperCase(word[i]);							//Call toUpperCase
		}
		else if (word[i] >= 'A' && word[i] <= 'Z' && i % 2 == 1)	//Check if odd leters are uppercase
		{
			word[i] = toLowerCase(word[i]);							//Call toLowerCase
		}

		i++;	//Increment array position
	}
}

/*****************************************************************************************
**							int main()
**	Accept input and call sticky function
*****************************************************************************************/
int main(){
	char input[100];
    
	printf("Please enter a word in all caps or lowercase: ");

	scanf("%s", input);		/*Read word from the keyboard using scanf*/
	
	sticky(input);			/*Call sticky*/
    
	printf("%s\n", input);	/*Print the new word*/

    return 0;
}