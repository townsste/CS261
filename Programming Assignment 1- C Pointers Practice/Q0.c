/* CS261- Assignment 1 - Q.0 */
/* Name: Stephen Townsend
 * Date: 1/22/17
 * Solution description: This program is used to show the memory address of
 *							a pointer and how it relates to dereferencing.
 */
 
#include <stdio.h>
#include <stdlib.h>

 /*****************************************************************************************
 **						void fooA(int* iptr)
 **	Output vaious pointer references
 *****************************************************************************************/
void fooA(int* iptr){
	printf("The value pointed to by iptr\n");
	printf("%d\n\n", *iptr);	/*Print the value pointed to by iptr*/
    
	printf("The address pointed to by iptr\n");
	printf("%p\n\n", iptr);		/*Print the address pointed to by iptr*/
     
	printf("The address of iptr\n");
	printf("%p\n\n", &iptr);	/*Print the address of iptr itself*/
}

int main(){
    
	int x = 0;					/*declare an integer x*/
    
	printf("The address of x\n");
	printf("%p\n\n", &x);		/*print the address of x*/
    
	fooA(&x);					/*Call fooA() with the address of x*/
    
	printf("The value of x\n");
	printf("%d\n\n", x);		/*print the value of x*/
    
    return 0;
}
