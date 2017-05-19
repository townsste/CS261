/* CS261- Assignment 2 - dynamicArray.c */
/* Name: Stephen Townsend
* Date: 1/29/17
* Solution description: This program is used to update and check for elements 
*						in an array through a stack like structure
*/


/*	dynamicArray.c: Dynamic Array implementation. */
#include <assert.h>
#include <stdlib.h>
#include "dynArray.h"

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};


/* ************************************************************************
	Dynamic Array Functions
************************************************************************ */

/* Initialize (including allocation of data array) dynamic array.

	param: 	v		pointer to the dynamic array
	param:	cap 	capacity of the dynamic array
	pre:	v is not null
	post:	internal data array can hold cap elements
	post:	v->data is not null
*/
void initDynArr(DynArr *v, int capacity)
{
	assert(capacity > 0);
	assert(v!= 0);
	v->data = (TYPE *) malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	v->size = 0;
	v->capacity = capacity;	
}

/* Allocate and initialize dynamic array.

	param:	cap 	desired capacity for the dyn array
	pre:	none
	post:	none
	ret:	a non-null pointer to a dynArr of cap capacity
			and 0 elements in it.		
*/
DynArr* newDynArr(int cap)
{
	assert(cap > 0);
	DynArr *r = (DynArr *)malloc(sizeof( DynArr));
	assert(r != 0);
	initDynArr(r,cap);
	return r;
}

/* Deallocate data array in dynamic array. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	d.data points to null
	post:	size and capacity are 0
	post:	the memory used by v->data is freed
*/
void freeDynArr(DynArr *v)
{
	if(v->data != 0)
	{
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}

/* Deallocate data array and the dynamic array ure. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	the memory used by v->data is freed
	post:	the memory used by d is freed
*/
void deleteDynArr(DynArr *v)
{
	freeDynArr(v);
	free(v);
}

/* Resizes the underlying array to be the size cap 

	param: 	v		pointer to the dynamic array
	param:	cap		the new desired capacity
	pre:	v is not null
	post:	v has capacity newCap
*/
void _dynArrSetCapacity(DynArr *v, int newCap)
{	
	
	TYPE *  prevArrayData;			//pointer to old array location
	prevArrayData = v->data;		//set to point to old array
	int prevArraySize = v->size;	//hold array size to put back old data

	initDynArr(v, newCap);  //Call to make new array with higher capacity

	v->size = prevArraySize;

		//Put data from prev array into new array
	for (int i = 0; i < prevArraySize; i++)
	{
		//printf("%d\n", prevArrayData[i]);
		v->data[i] = prevArrayData[i];
	}

}

/* Get the size of the dynamic array

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	none
	ret:	the size of the dynamic array
*/
int sizeDynArr(DynArr *v)
{
	return v->size;
}

/* 	Adds an element to the end of the dynamic array

	param: 	v		pointer to the dynamic array
	param:	val		the value to add to the end of the dynamic array
	pre:	the dynArry is not null
	post:	size increases by 1
	post:	if reached capacity, capacity is doubled
	post:	val is in the last utilized position in the array
*/
void addDynArr(DynArr *v, TYPE val)
{
	assert(v != 0);									//v is not null

	if (v->size == v->capacity)						//check if size == capacity
		_dynArrSetCapacity(v, 2 * v->capacity);		//if ture then double capacity

	v->data[v->size] = val;							//set val to the last position
	v->size++;										//increase size by 1
}

/*	Get an element from the dynamic array from a specified position
	
	param: 	v		pointer to the dynamic array
	param:	pos		integer index to get the element from
	pre:	v is not null
	pre:	v is not empty
	pre:	pos < size of the dyn array and >= 0
	post:	no changes to the dyn Array
	ret:	value stored at index pos
*/

TYPE getDynArr(DynArr *v, int pos)
{
	assert(v != 0);							//v is not null
	assert(v->size > 0);					//v is not empty
	assert(pos < v->size && pos >= 0);		//pos < size and pos >= 0

	return v->data[pos];					//return the data at given position
}

/*	Put an item into the dynamic array at the specified location,
	overwriting the element that was there

	param: 	v		pointer to the dynamic array
	param:	pos		the index to put the value into
	param:	val		the value to insert 
	pre:	v is not null
	pre:	v is not empty
	pre:	pos >= 0 and pos < size of the array
	post:	index pos contains new value, val
*/
void putDynArr(DynArr *v, int pos, TYPE val)
{
	assert(v != 0);							//v is not null
	assert(v->size > 0);					//v is not empty
	assert(pos >= 0 && pos < v->size);		//pos >= 0 and pos < size
		
	v->data[pos] = val;						//set a given positions data
}

/*	Swap two specified elements in the dynamic array

	param: 	v		pointer to the dynamic array
	param:	i,j		the elements to be swapped
	pre:	v is not null
	pre:	v is not empty
	pre:	i, j >= 0 and i,j < size of the dynamic array
	post:	index i now holds the value at j and index j now holds the value at i
*/
void swapDynArr(DynArr *v, int i, int  j)
{
	assert(v != 0);						//v is not null
	assert(v->size > 0);				//v is not empty
	assert(i >= 0 && i < v->size);		//j >= 0 and j < size
	assert(j >= 0 && j < v->size);		//i >= 0 and i < size

	int temp = 0;						//swap temp holder
	
	temp = v->data[i];					//temp is equal to pos i
	v->data[i] = v->data[j];			//set pos i to pos j
	v->data[j] = temp;					//set pos j to temp from pos i
}

/*	Remove the element at the specified location from the array,
	shifts other elements back one to fill the gap

	param: 	v		pointer to the dynamic array
	param:	idx		location of element to remove
	pre:	v is not null
	pre:	v is not empty
	pre:	idx < size and idx >= 0
	post:	the element at idx is removed
	post:	the elements past idx are moved back one
*/
void removeAtDynArr(DynArr *v, int idx)
{
	assert(v != 0);							//v is not null
	assert(v->size > 0);					//v is not empty
	assert(idx < v->size && idx >= 0);		//idx < size and idx >= 0
	
	for (int i = idx; i < v->size - 1; i++)
		v->data[i] = v->data[i + 1];		//shift val at pos i + 1 to pos i

	v->size--;								//decrease array size
}



/* ************************************************************************
	Stack Interface Functions
************************************************************************ */

/*	Returns boolean (encoded in an int) demonstrating whether or not the 
	dynamic array stack has an item on it.

	param:	v		pointer to the dynamic array
	pre:	the dynArr is not null
	post:	none
	ret:	1 if empty, otherwise 0
*/
int isEmptyDynArr(DynArr *v)
{
	assert(v != 0);		//v is not null

	if (v->size == 0)	// check if array has a size
		return 1;		//return empty
	else
		return 0;		//return has elements
}

/* 	Push an element onto the top of the stack

	param:	v		pointer to the dynamic array
	param:	val		the value to push onto the stack
	pre:	v is not null
	post:	size increases by 1
			if reached capacity, capacity is doubled
			val is on the top of the stack
*/
void pushDynArr(DynArr *v, TYPE val)
{
	assert(v != 0);			//v is not null

	addDynArr(v, val);		//call addDynArr function to add elements
}

/*	Returns the element at the top of the stack 

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the stack
*/
TYPE topDynArr(DynArr *v)
{
	assert(v != 0);								//v is not null
	assert(v->size > 0);						//v is not empty
	
	return getDynArr(v, sizeDynArr(v) - 1);		//return the data at the top of the array
}

/* Removes the element on top of the stack 

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	size is decremented by 1
			the top has been removed
*/
void popDynArr(DynArr *v)
{
	assert(v != 0);							//v is not null
	assert(v->size > 0);					//v is not empty

	removeAtDynArr(v, sizeDynArr(v) - 1);	//call removeAtDynArr function to remove element
}

/* ************************************************************************
	Bag Interface Functions
************************************************************************ */

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	v		pointer to the dynamic array
	param:	val		the value to look for in the bag
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the bag
*/
int containsDynArr(DynArr *v, TYPE val)
{
	assert(v != 0);						//v is not null
	assert(v->size > 0);				//v is not empty
	
	for (int i = 0; i < v->size; i++)	
	{
		if (getDynArr(v, i) == val)		//check for element in array
			return 1;					//found element
	}
	
	return 0;							//found nothing
}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	v		pointer to the dynamic array
	param:	val		the value to remove from the array
	pre:	v is not null
	pre:	v is not empty
	post:	val has been removed
	post:	size of the bag is reduced by 1
*/
void removeDynArr(DynArr *v, TYPE val)
{
	assert(v != 0);						//v is not null
	assert(v->size > 0);				//v is not empty

	for (int i = 0; i < v->size; i++)
		if (v->data[i] == val)			//check for element in array
			removeAtDynArr(v, i);		//call removeAtDynArr to remove element
}
