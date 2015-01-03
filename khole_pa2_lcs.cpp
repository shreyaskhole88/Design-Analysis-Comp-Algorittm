/********************************************************************
*  Author: Shreyas Khole.
*  Course: CS 575.
*  Date: 03/18/2014
*  Purpose: To implement the Longest Common Subsequence by 
			Dynamic Programming.
*  LCS Problem Statement: Given two sequences, find the length 
			of longest subsequence present in both of them. 
			A subsequence is a sequence that appears in the same 
			relative order, but not necessarily contiguous.
*
********************************************************************/

/* printf */
#include <stdio.h>
/* malloc*/
#include <stdlib.h>
/* strlen */
#include <string.h>

/* Representing Diagonal Arrow*/
#define DIAGONAL 'D'

/* Representing UP Arrow*/
#define UP 'U'

/* Representing Left Arrow*/
#define LEFT 'L'

/*
* Declaring 2D array/matrix of type int.
* This variable is used to store the
* length of subsequence.
*/
int **matrix;

/*
* Declaring 2D array/matrix of type int.
* This variable is used as a arrow direction
* table.
*/
int **table;

/************************************************************************
* Function: void print_matrix(int **, int, int)
* Input   : int **a : 2D array.
			int m: row of a matrix
			int n: col of matrix
* Output  : None
* Procedure: This function is used to print the 2D array.
*			 
************************************************************************/
void print_matrix(int **a, int m, int n){
	for(int i = 0; i <= m; i++){
		for(int j = 0; j <= n; j++){
			printf("%c\t", (char) a[i][j] );
		}
		printf("\n\n");
	}
}

/************************************************************************
* Function: void find_lcs(char[], char[], int, int)
* Input   : char x[]: First input string.
			char y[]: Second input string.
			int m: row of a matrix
			int n: col of matrix
* Output  : None
* Procedure: This function is used to find the longest common subsequence
			 between two strings by dynamic programming.
*			 
************************************************************************/
void find_lcs(char x[], char y[], int first_string_length, int second_string_length){
	for(int i = 0; i <= first_string_length; i++){
		matrix[i][0] = 0;										
	}
	for(int i = 0; i <= second_string_length; i++){
		matrix[0][i] = 0;
	}
	for(int i = 1; i <= first_string_length; i++){
		for(int j = 1; j <= second_string_length; j++){
			if(x[i - 1] == y[j - 1]){									// Match is found in two strings
				matrix[i][j] = matrix[i-1][j-1] + 1;					// Inserting diagonal element + 1.
				table[i][j] = DIAGONAL;									// Inserting Diagonal Arraow in table.
			} else if(matrix[i-1][j] >= matrix[i][j-1]){				
				matrix[i][j] = matrix[i-1][j];							// Inserting UP element.
				table[i][j] = UP;										// Inserting UP Arraow in table.
			}else{
				matrix[i][j] = matrix[i][j-1];							// Inserting LEFT element.
				table[i][j] = LEFT;										// Inserting LEFT Arraow in table.
			}
		}
	}
}

/************************************************************************
* Function: void print_lcs(char **, char *, char *, int, int)
* Input   : char **table : 2D array with arrow poiting.
			char *x : First input string
			char *y : second input string
			int x_length: length of first string
			int y_length: length of second string
* Output  : None
* Procedure: This function is used to print the longest common subsequence
			 between two strings by recusrsive calls.
*			 
************************************************************************/
void print_lcs(int **table, char *x, int x_length, int y_length){
	if(x_length == 0 || y_length == 0){
		return;
	}
	if(table[x_length][y_length] == DIAGONAL){
		print_lcs(table, x, x_length - 1,y_length - 1);					// If Diagonal arrow found, move diagonally in matrix.
		printf("%c\t", x[x_length - 1]);								// If Diagonal arrow is found, print an element.
	} else if(table[x_length][y_length] == UP){
		print_lcs(table, x, x_length - 1, y_length);					// If UP arrow found, move UP in matrix.
	}else{
		print_lcs(table, x, x_length, y_length - 1);					// If Left arrow found, move LEFT in matrix.
	}
}

/************************************************************************
* Function: void free_memory(int **, int, int)
* Input   : int **a : 2D array.
			int row : number of rows of matrix
			int col : number of columns of matrix
* Output  : None
* Procedure: This function is used to free a memory allocated to 
			 the matrix using free() function.
			 
************************************************************************/
void free_memory(int **a, int row, int col){
	for(int i = 0; i < row; i++){
		free(a[i]);														// Freeing up memory of row.
	}
	free(a);															// Freeing up memory of matrix.
}

/************************************************************************
* Function: int main(int, char* [])
* Input   : int argc - number of input parameters
			char *arg[] - First Input String and Second Input String.
* Procedure: Main function accepts the 2 parameters - First input string
			 and second input string.
			 1. Check if size of both string is less than 100.
			 2. Allocate memory to matrix and table 2D array.
			 3. Find LCS.
			 4. Print LCS
************************************************************************/
int main(int argc, char *arg[]){
	printf("\t------- Longest Common Subsequence ------- \n\n");
	if(argc != 3){
		fprintf(stderr, "Error while accepting arguments!!!");
	} else {
		char *first_string = arg[1];
		printf("First input string: %s\n\n", first_string);
		char *second_string = arg[2];
		printf("Second input string: %s\n\n", second_string);
		int first_string_len = strlen(first_string);
		int second_string_len = strlen(second_string);
		if(first_string_len > 100 || second_string_len > 100){
			fprintf(stderr, "Length of input string should be less than 100.\n\n");
			exit(1);
		}
		/* Allocating memory to matrix array */
		matrix = (int **)calloc(first_string_len + 1, sizeof(int*));
		for(int i = 0; i < first_string_len + 1; i++){
			matrix[i] = (int *) calloc(second_string_len + 1,sizeof(int));
		}
		/* Allocating memory to table array */
		table = (int **)calloc(first_string_len + 1, sizeof(int*));
		for(int i = 0; i < first_string_len + 1; i++){
			table[i] = (int *) calloc(second_string_len + 1, sizeof(int));
		}
		find_lcs(arg[1], arg[2], first_string_len, second_string_len);		// Function call to find a longest common subsequence.
		printf("------- Arrow Table ------- \n\n");
		print_matrix(table, first_string_len, second_string_len);
		printf("------- LONGEST COMMON SUBSEQUENCE -------- \n\n");
		print_lcs(table, first_string, first_string_len, second_string_len);// Printing Longest common subsequence.
		free_memory(matrix, first_string_len + 1, second_string_len + 1);
		free_memory(table, first_string_len + 1, second_string_len + 1);
	}
	return 0;
}
