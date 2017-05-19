/* CS261- Assignment 3 - linkedList.c */
/* Name: Stephen Townsend
* Date: 2/5/17
* Solution description: This program is used to create a linked list and add or remove links as needed
*/

#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	list->frontSentinel = malloc(sizeof(struct Link));
	list->backSentinel = malloc(sizeof(struct Link));

	list->size = 0;
	
	list->frontSentinel->next = list->backSentinel;			//set frontSentinel next to the backSentinel
	list->frontSentinel->prev = NULL;						//set frontSentinel prev to NULL

	list->backSentinel->prev = list->frontSentinel;			//set backSentinel prev to the frontSentinel
	list->backSentinel->next = NULL;						//set backSentinel next to NULL
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	assert(list != NULL);										//check that list is not NULL
	struct Link *addNewLink = malloc(sizeof(struct Link));		//allocate a new link
	addNewLink->value = value;									//set links value

	assert(addNewLink != NULL);									//check that new link was created correctly

	addNewLink->next = link;									//place new link in the list.  Set next to the passed in link
	addNewLink->prev = link->prev;								//set prev to [assed in liks prev

	link->prev->next = addNewLink;								//set passed in link to point to new link.
	link->prev = addNewLink;
	
	list->size++;												//add one to list size
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	link->prev->next = link->next;			//set the prev link to point one link forward
	link->next->prev = link->prev;			//set the next link to point to the prev link

	link->next = NULL;						//set links pointers to null
	link->prev = NULL;						//set links pointers to null
	link->value = 0;						//set links val to 0

	free(link);								//dealocate the link
		
	list->size--;							//reduce list size by one
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	assert(list != NULL);										//check that list is not NULL
	addLinkBefore(list, list->frontSentinel->next, value);		//call addLinkBefore function and passin the first link
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	assert(list != NULL);								//check that list is not NULL
	addLinkBefore(list, list->backSentinel, value);		//call addLinkBefore function and passin the last link
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	return (list->frontSentinel->next->value);		//return the first link value
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	return (list->backSentinel->prev->value);		//return the last link value
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	assert(list != NULL);							//check that list is not NULL
	assert(list->size > 0);							//check that list has links

	removeLink(list, list->frontSentinel->next);	//call removeLink function and pass in front link
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	assert(list != NULL);							//check that list is not NULL
	assert(list->size > 0);							//check that list has links

	removeLink(list, list->backSentinel->prev);		//call removeLink function and pass in front link
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	assert(list != NULL);			//check that list is not NULL
	
	if (list->size == 0)			//check if size is equal to 0
		return 1;					//return empty
	else 
		return 0;					//return has link
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	struct Link *transverse = NULL;				//create a transverse pointer

	transverse = list->frontSentinel->next;		//set to the first link in list
	
	while (transverse != list->backSentinel)	//while not at the back
	{
		printf("%d ", transverse->value);		//print the value it is pointing to
		transverse = transverse->next;			//advance transverse pointer
	}	
	printf("\n");								//print newline
	
	transverse = NULL;							//remove transverse by pointing to NULL
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	assert(list != NULL);				//check that list is not NULL
	
	linkedListAddFront(list, value);	//call add to front function
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	struct Link *transverse = NULL;				//create a transverse pointer

	transverse = list->frontSentinel->next;		//set to first link


	while (transverse != list->backSentinel)	//while not at the back
	{
		if (EQ(transverse->value, value))		//check that values equal each other
		{
			return 1;							//return true
		}
		else
			transverse = transverse->next;		//advance transverse pointer
	}

	transverse = NULL;							//remove transverse by pointing to NULL

	return 0;									//return false


}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	
	assert(list != NULL);						//check that list is not NULL
	assert(list->size > 0);						//check that list has links
	
	struct Link *transverse = NULL;				//create a transverse pointer

	transverse = list->frontSentinel->next;		//set to first link


	while (transverse != list->backSentinel)	//while not at the back
	{
		if (EQ(transverse->value, value))		//check that values equal each other
		{
			removeLink(list, transverse);		//call removeLink at current location
			transverse = list->backSentinel;	//set tranverse to back to exit loop without checking more
		}
		else
			transverse = transverse->next;		//advance transverse pointer
	}

	transverse = NULL;							//remove transverse by pointing to NULL
}
