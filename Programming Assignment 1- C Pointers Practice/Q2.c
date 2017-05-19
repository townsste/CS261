/* CS261- Assignment 1 - Q.2 */
/* Name: Stephen Townsend
 * Date: 01/22/17
 * Solution description:  This program is used to modify three variables and show the
							correlation of pointers and pass by copy.
 */
 
#include <stdio.h>
#include <stdlib.h>

 /*****************************************************************************************
 **							int foo(int* a, int* b, int c)
 **	Modifies variables.
 *****************************************************************************************/
int foo(int* a, int* b, int c){
	*a *= 2;	/*Set a to double its original value*/
    
	*b /= 2;	/*Set b to half its original value*/
    
	c = *a + *b;	/*Assign a+b to c*/
    
	return c;	/*Return c*/
}

/*****************************************************************************************
**									int main()
**	Declare variables and output results.
*****************************************************************************************/
int main(){
	int x = 5;
	int y = 6;
	int z = 7;	/*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    
	printf("x:%i  y:%i  z:%i\n\n", x, y, z);	/*Print the values of x, y and z*/
    
	printf("Returned by foo: %d\n\n", foo(&x, &y, z));	/*Call foo() appropriately, passing x,y,z as parameters*/
    
									/*Print the value returned by foo*/
    
	printf("x:%i  y:%i  z:%i\n\n", x, y, z);	/*Print the values of x, y and z again*/

    return 0;
}
    
    
/*
Is the return value different than the value of z?  Why?

Yes, the reason being is that z is not a pointer in the foo function.  
As a result, its address is not being passed like x and y.  
Thus, only a copy of z is being passed and this in-turn will not modify
the original value stored in z.
*/