/* CS261- Assignment 1 - Q.3 */
/* Name: Stephen Townsend
 * Date: 1/22/17
 * Solution description:  This program is used to dynamically allocate an array and fill that
							array with random numbers that will be sorted.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

 /*****************************************************************************************
 **							void sort(int* number, int n)
 **	Uses a bubble sort to sort an array.
 *****************************************************************************************/
void sort(int* number, int n){
     /*Sort the given array number , of length n*/ 
	int temp = 0;
	int swap;

	//Bubble Sort
	do
	{
		swap = 0;	//Reset flag
		for (int i = 0; i < (n - 1); i++)
		{
			if (number[i] > number[i + 1])		//Check if current number is greater then next
			{
				temp = number[i];				//Place current number in temp
				number[i] = number[i + 1];		//Move the next number back one element
				number[i + 1] = temp;			//Make first element to be the second element
				swap = 1;						//Flag swap occured
			}
		}
	} while (swap);		//Loop again if a swap occurred on this pass.
}

/*****************************************************************************************
**									int main()
**	Fill the dynamic array with random numbers
*****************************************************************************************/
int main(){
	int n = 20;	/*Declare an integer n and assign it a value of 20.*/
    
	int* pArray = (int*)malloc(sizeof(int)*n);	/*Allocate memory for an array of n integers using malloc.*/
    
	printf("Random Numbers\n");

	for (int i = 0; i < n; i++)	/*Fill this array with random numbers, using rand().*/
	{
		pArray[i] = rand();
		printf("%d\n", pArray[i]);	/*Print the contents of the array.*/
	}

	sort(pArray, n);	/*Pass this array along with n to the sort() function of part a.*/
    
	printf("\n\nRandom Numbers Sorted\n");

	for (int j = 0; j < n; j++)
		printf("%d\n", pArray[j]);	/*Print the contents of the array.*/

	free(pArray);		//Deallocate array
	pArray = NULL;		//Set pointer to NULL
    
    return 0;
}
