/* CS261- Assignment 4 - compare.c */
/* Name: Stephen Townsend
* Date: 2/21/17
* Solution description: This program is used compare the left and right children in a 
*		binary tree
*/


#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"

/*----------------------------------------------------------------------------
 very similar to the compareTo method in java or the strcmp function in c. it
 returns an integer to tell you if the left value is greater then, less then, or
 equal to the right value. you are comparing the number variable, letter is not
 used in the comparison.

 if left < right return -1
 if left > right return 1
 if left = right return 0
 */

 /*Define this function, type casting the value of void * to the desired type.
  The current definition of TYPE in bst.h is void*, which means that left and
  right are void pointers. To compare left and right, you should first cast
  left and right to the corresponding pointer type (struct data *), and then
  compare the values pointed by the casted pointers.

  DO NOT compare the addresses pointed by left and right, i.e. "if (left < right)",
  which is really wrong.
 */
int compare(TYPE left, TYPE right)
{
	struct data* data1;
	struct data* data2;

	data1 = (struct data*)left;						//retype void pointer to a data struct type for left
	data2 = (struct data*)right;					//retype void pointer to a data struct type for right

	if (data1->number > data2->number)				//check if right is less then left
		return 1;
	else if (data1->number < data2->number)			//check if less is less then right
		return -1;
	else
		return 0;									//return the same
}

/*Define this function, type casting the value of void * to the desired type*/
void print_type(TYPE curval)
{
	assert(curval != NULL);
	
	struct data *cur;					//retype void pointer to a data struct type for cur
	cur = (struct data *) curval;		//set cur to curval

	printf("%d", cur->number);			//print number			
}


