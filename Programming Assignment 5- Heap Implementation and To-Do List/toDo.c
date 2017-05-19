/*
 * CS 261 Assignment 5
 * Name: Stephen Townsend
 * Date: 3/5/17
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[256];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
     while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    // FIXME: Implement
	char file[256] = "";
	char description [256] = "";
	char *endChar;
	int priority;
	FILE *pFile;			//open File Pointer
	Task *task;				//task pointer

//COMMAND l and s
	if (command == 'l' || command == 's')
	{
		printf("Please enter the filename: ");
		if(fgets(file, sizeof(file), stdin) != NULL);	//get file name
		{
			endChar = strchr(file, '\n');		//find newline char
			if (endChar)
				*endChar = '\0';				//replace newline
		}

		//open and read file if 'l'
		if (command == 'l')						
		{
			pFile = fopen(file, "r");

			if (pFile != NULL)
			{
				listLoad(list, pFile);
				printf("The list has been loaded successfully from the file.\n\n");
				fclose(pFile);
			}
			else
				printf("Cannot open the file.\n");		//cannot open file
		}

		//open and write file if 's'
		else if (command == 's')
		{
			pFile = fopen(file, "w");

			if (pFile != NULL)
			{
				listSave(list, pFile);
				printf("The list has been saved into the file successfully.\n\n");
				fclose(pFile);
			}
			else
				printf("Cannot open the file.\n");		//cannot open file
		}
		
	}
//COMMAND a
	else if (command == 'a')
	{
		printf("Please enter the task description: ");
		//get description
		if (fgets(description, sizeof(description), stdin) != NULL);	
		{
			endChar = strchr(description, '\n');	//find newline char
			if (endChar)
				*endChar = '\0';					//replace newline
		}
		
		//Test that priority is between 0 and 999
		do	
		{
			printf("Please enter the task priority (0-999): ");
			scanf("%i", &priority);							//get priority
		} 
		while (!(priority >= 0 && priority <= 999));		//check input
		
		while (getchar() != '\n');							//clear the buffer

		task = taskNew(priority, description);				//make a new task
		dyHeapAdd(list, task, taskCompare);					//add to heap
		printf("The task '%s' has been added to the list.\n\n", description);
	
	}
//COMMAND g, r, & p
	else if (command == 'g' || command == 'r' || command == 'p')
	{
		//common output between  command g, r, & p
		if (dySize(list) == 0)							//check if there is a list
			printf("Your to-do list is empty!\n\n");	//no list found
		
		if (command == 'g')			//print first task at top of heap			
		{
			task = (Task*)dyHeapGetMin(list);
			printf("Your first task is: %s\n\n", task->name);
		}
		else if (command == 'r')	//remove first task at top of heap
		{
			task = (Task*)dyHeapGetMin(list);	//Task pointer to heap from list
			printf("Your first task %s has been removed from the list\n\n", task->name);
			dyHeapRemoveMin(list, taskCompare);	//call remove min
		}
		else if (command == 'p')	//Print the list		
		{
			listPrint(list);		
			printf("\n");
		}
	}
	else if (command == 'e')
	{
		printf("Exiting\n\n");
	}
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
 /* free dynamically allocated List pointers in array to avoid memory leaks */
	for (int i = 0; i < dySize(list); i++) 
	{
		Task *task = dyGet(list, i);
		taskDelete(task);
	}

    dyDelete(list);
    return 0;
}