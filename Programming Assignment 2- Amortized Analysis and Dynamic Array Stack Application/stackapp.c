/* CS261- Assignment 2 - stackapp.c */
/* Name: Stephen Townsend
* Date: 1/29/17
* Solution description: This program is used to check if a string has balanced 
*						parethesis, braces, and brackets (,{,[.
*/


/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	struct DynArr *balArray = newDynArr(sizeof(s));
	char c;

	while ((c = nextChar(s)) != '\0') 
	{
		
		if (c == '(' || c == '{' || c == '[')	//Check if cahr is (, {, or [
			pushDynArr(balArray, c);

		if (c == ')')							//Check if char is )
		{
			if (topDynArr(balArray) == '(')		//Check if there is a corresponding char
				popDynArr(balArray);			//Remove char from stack
		}

		if (c == '}')							//Check if char is }
		{
			if (topDynArr(balArray) == '{')		//Check if there is a corresponding char
				popDynArr(balArray);			//Remove char from stack
		}

		if (c == ']')							//Check if char is ]
		{
			if (topDynArr(balArray) == '[')		//Check if there is a corresponding char
				popDynArr(balArray);			//Remove char from stack
		}
	}
	
	if (isEmptyDynArr(balArray) == 0)			//Check if empty
	{
		deleteDynArr(balArray);					//Delete array
		return 0;								//False
	}
	else
	{
		deleteDynArr(balArray);					//Delete array
		return 1;								//true
	}
}

int main(int argc, char* argv[]){

	char* s = argv[1];
	int res;
	
	printf("Assignment 2\n");

	if (s == NULL)
	{
		printf("No string provided\n");
		return 0;
	}
	else
	{
		res = isBalanced(s);

		if (res)
			printf("The string %s is balanced\n", s);
		else
			printf("The string %s is not balanced\n", s);

		return 0;
	}
}

