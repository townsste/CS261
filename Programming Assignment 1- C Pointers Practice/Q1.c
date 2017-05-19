/* CS261- Assignment 1 - Q.1 */
/* Name: Stephen Townsend
 * Date: 1/22/17
 * Solution description:  This program is designed to randomly generate a student IDs and scores.
 *							The program will then summerize the min, max, and average score.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct student{
	int id;
	int score;
};

/*****************************************************************************************
**							struct student* allocate()
**	Allocates memory for ten students.
*****************************************************************************************/
struct student* allocate() {
	struct student* pArray = malloc(sizeof(struct student)*10);		/*Allocate memory for ten students*/

	return pArray;	/*return the pointer*/
}

/*****************************************************************************************
**					void generate(struct student* students)
**	Generate random and unique ID and scores for ten students, ID being between 1 and 10, 
**	scores between 0 and 100
*****************************************************************************************/
void generate(struct student* students){
	int random = 0;
	int flag;

	for (int i = 0; i < 10; i++)
	{
		flag = 0;	//reset flag
		random = rand() % 10 + 1;					//Random ID generator

			for (int j = 0; j < i; j++) 
			{
				if (flag == 0)						//Trip flag if ID is unique
				{
					if (random == students[j].id)	//Check new ID with IDs in the array
					{
						i--;						//Go back one element due to duplicate ID
						flag = 1;					//Flag trigger for non unique
					}
				}
			}

		if (flag == 0) //ID is unique
		{
			students[i].id = random;							//Add ID to array
			students[i].score = (rand() % (100 - 0 + 1) + 0);	//Generate random score
		}
	}
}

/*****************************************************************************************
**					void output(struct student* students)
**	Output information about the ten students
*****************************************************************************************/
void output(struct student* students){

	for (int i = 0; i < 10; i++)
		printf("ID %d, Score %d\n", students[i].id, students[i].score); //Output
	
	printf("\n"); //Add newline for formating
}

/*****************************************************************************************
**					void summary(struct student* students)
**	Compute and print the minimum, maximum and average scores of the ten students
*****************************************************************************************/
void summary(struct student* students){

	int min = students[0].score;	//Set min to first element in array (Base case)
	int max = students[0].score;	//Set max to first element in array (Base case)
	double avg = 0;

	for (int i = 0; i < 10; i++)
	{
		if (min > students[i].score)	//Check for a new min by comparing next element
			min = students[i].score;	//New min found.  Set min to element

		if (max < students[i].score)	//Check for a new max by comparing next element
			max = students[i].score;	//New max found.  Set max to element

		avg += students[i].score;		//Add score to avg
	}

	avg /= 10;		//Calculate average

	printf("min: %d, max: %d, avg: %.1f\n", min, max, avg);		//Output summary
}

/*****************************************************************************************
**					void deallocate(struct student* stud)
**	Deallocate memory from stud
*****************************************************************************************/
void deallocate(struct student* stud){
	free(stud);		//Deallocate stud
	stud = NULL;	//Set pointer to null
}


int main(){
    struct student* stud = NULL;
    
	stud = allocate();	/*call allocate*/
    
	generate(stud);		/*call generate*/
    
	output(stud);		/*call output*/
    
	summary(stud);		/*call summary*/
    
	deallocate(stud);	/*call deallocate*/

    return 0;
}
