/* CS261- Assignment 3 circularList.c */
/* Name: Stephen Townsend
* Date: 2/5/17
* Solution description: This program is used to create a circular linked list and add or remove links as needed
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	list->sentinel = malloc(sizeof(struct Link));		//create a sentinel
	list->size = 0;										//set size to 0

	list->sentinel->next = list->sentinel;				//set sentinel next to itself
	list->sentinel->prev = list->sentinel;				//set sentinel next to itself
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link *newLink = malloc(sizeof(struct Link));		//create a new link

	newLink->value = value;									//set new links value

	assert(newLink != NULL);								//check that new link was made correctly
	
	return newLink;											//return created link
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	assert(list != NULL);							//check that list is not NULL

	struct Link *addNewLink = createLink(value);	//create a new link to add

	addNewLink->next = link;						//set newLink next to current link
	addNewLink->prev = link->prev;					//set newLink prev to the current link prev

	link->prev->next = addNewLink;					//set the prev to newLink
	link->prev = addNewLink;						//set currentLink to new link

	list->size++;									//increase list size by one
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	link->prev->next = link->next;			//set the prev link to point to next link
	link->next->prev = link->prev;			//set next link to point to last link

	link->next = NULL;						//set current link to NULL
	link->prev = NULL;						//set current link to NULL
	link->value = 0;						//set current link value to 0

	free(link);								//remove current link

	list->size--;							//decrease list size by one
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	while (!circularListIsEmpty(list))		//while list is not empty
	{
		circularListRemoveFront(list);		//remove the first link in list
	}
	free(list->sentinel);					//remove the sentinel
	free(list);								//remove the list
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	addLinkAfter(list, list->sentinel->next, value);		//call addLinkAfter function
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	addLinkAfter(list, list->sentinel, value);			//call addLinkAfter function
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	return list->sentinel->next->value;			//return front lnk value
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	return (list->sentinel->prev->value);		//return last link value
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	assert(list != NULL);						//check that list is not NULL
	assert(list->size > 0);						//check that there is a link

	removeLink(list, list->sentinel->next);		//remove the front link by calling removeLink function
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	assert(list != NULL);						//check that list is not NULL
	assert(list->size > 0);						//check that there is a link

	removeLink(list, list->sentinel->prev);		//remove the back link by calling removeLink function
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	if (list->size == 0)		//check if list size is equal to 0
		return 1;				//return empty
	else
		return 0;				//return has link
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	struct Link *transverse = NULL;				//create a transverse pointer

	transverse = list->sentinel->next;			//set to the first link in list


		while (transverse != list->sentinel)	//while not at the back
		{
			printf("%g ", transverse->value);	//print the value it is pointing to
			transverse = transverse->next;		//advance transverse pointer
		}
		printf("\n");							//print newline

		transverse = NULL;						//remove transverse by pointing to NULL
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	struct Link *temp = NULL;				//create temp pointer
	struct Link *transverse = NULL;			//create transverse pointer

	temp = list->sentinel;					//set temp to sentinel
	transverse = list->sentinel->next;		//tranverse to first link

	for (int i = 0; i <= list->size; i++)
	{
		temp->next = temp->prev;			//set next to prev
		temp->prev = transverse;			//set temp prev to surrent transverse point

		temp = transverse;					//set temp to current link
		transverse = transverse->next;		//Advance to next link
	}
	
	temp = NULL:							//remove temp by pointing to NULL
	transverse = NULL;						//remove transverse by pointing to NULL
}
