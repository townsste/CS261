/* CS261- Assignment 1 - Q.4 */
/* Name: Stephen Townsend
 * Date: 1/22/17
 * Solution description:  This program is designed to randomly generate student IDs and scores.
							This goes a little further and sorts the scores in ascending order.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct student{
	int id;
	int score;
};

/*****************************************************************************************
**						void sort(struct student* students, int n)
**	Uses a bubble sort to sort an array.
*****************************************************************************************/
void sort(struct student* students, int n){
     /*Sort the n students based on their score*/   
	int temp = 0;
	int swap;

	//Bubble Sort
	do
	{
		swap = 0;	//Reset flag
		for (int i = 0; i < (n - 1); i++)
		{
			if (students[i].score > students[i + 1].score)		//Check if current number is greater then next
			{
				temp = students[i].score;						//Place current number in temp
				students[i].score = students[i + 1].score;		//Move the next number back one element
				students[i + 1].score = temp;					//Make first element to be the second element
				swap = 1;										//Flag swap occured
			}
		}
	} while (swap);		//Loop again if a swap occurred on this pass.
}

/*****************************************************************************************
**									int main()
**	Generate random and unique IDs and random scores for the n students
*****************************************************************************************/
int main(){
	int n = 15;		/*Declare an integer n and assign it a value.*/
    
	struct student* pStudents = malloc(sizeof(struct student)*n);	/*Allocate memory for n students using malloc.*/
    
	
	/*Generate random and unique IDs and random scores for the n students, using rand().*/
	int random = 0;
	int flag;

	for (int i = 0; i < n; i++)
	{
		flag = 0;	//reset flag
		random = rand() % n + 1;					//Random ID generator

		for (int j = 0; j < i; j++)				
		{
			if (flag == 0)							//Trip flag if ID is unique
			{
				if (random == pStudents[j].id)		//Check new ID with IDs in the array
				{
					i--;							//Go back one element due to duplicate ID
					flag = 1;						//Flag trigger for non unique
				}
			}
		}

		if (flag == 0)	//ID is unique
		{
			pStudents[i].id = random;								//Add ID to array
			pStudents[i].score = (rand() % (100 - 0 + 1) + 0);		//Generate random score
		}
	}

		/*Print the contents of the array of n students.*/
		printf("Students and their scores\n");
		for (int k = 0; k < n; k++)
			printf("ID %d, Score %d\n", pStudents[k].id, pStudents[k].score);
	
	sort(pStudents, n);		/*Pass this array along with n to the sort() function*/

	printf("\nStudents and their sorted scores\n");
	for (int m = 0; m < n; m++)		 /*Print the contents of the array of n students.*/
		printf("ID %d, Score %d\n", pStudents[m].id, pStudents[m].score);

	if (pStudents)
	{
		free(pStudents);	//Deallocate array
		pStudents = NULL;	//Set pointer to NULL
	}

    return 0;
}
