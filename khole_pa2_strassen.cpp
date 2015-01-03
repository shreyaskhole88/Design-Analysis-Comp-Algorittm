/********************************************************************
*  Author: Shreyas Khole.
*  Course: CS 575.
*  Date: 03/18/2014
*  Purpose: To implement the Strassen's Matrix Multiplication by 
			Divide and Conquer.
*
********************************************************************/

/* printf */
#include <stdio.h>
/* malloc*/
#include <stdlib.h>
/* strlen */
#include <string.h>
/* rand(), srand()*/
#include <time.h>

/* Range for generating matrix values. */
#define RANGE 10

/*
* Declaring 2D array/matrix of type int.
* This variable is used as a first
* matrix.
*/
int **first_matrix;

/*
* Declaring 2D array/matrix of type int.
* This variable is used as a second
* matrix.
*/
int **second_matrix;

/*
* Declaring 2D array/matrix of type int.
* This variable is used as a resulting
* matrix to store the multiplication.
*/
int **result_matrix;

/************************************************************************
* Function: void print_matrix(int **, int, int)
* Input   : int **a : 2D array.
			int n: size of matrix
* Output  : None
* Procedure: This function is used to print the 2D array.
*			 
************************************************************************/
void print_matrix(int **a, int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%d\t", a[i][j]);
		}
		printf("\n\n");
	}
}

/************************************************************************
* Function: void divide(int **, int, int, int)
* Input   : int **a : 2D array.
			int start_row: starting row for divided matrix.
			int start_col: starting col for divided matrix.
			int dim: size of matrix
* Output  : int** temp: return divided matrix.
* Procedure: This function is used to divide the larger matrix intp
			 sub matrices.
*			 
************************************************************************/
int** divide(int **matrix, int start_row, int start_col, int dim){
	int **temp;
	/* Allocating memory to first matrix */
	temp = (int **)calloc(dim, sizeof(int*));
	for(int i = 0; i < dim; i++){
		temp[i] = (int *) calloc(dim, sizeof(int));
	}
	for(int i = start_row; i < start_row + dim; i++){
		for(int j = start_col; j < start_col + dim; j++){
			temp[i-start_row][j - start_col] = matrix[i][j];
		}
	}
	return temp;
}

/************************************************************************
* Function: void matrix_add(int **, int **, int)
* Input   : int **a : 2D array.
			int **b: 2D array.
			int dim: size of matrix
* Output  : int** temp: return addition of matrices.
* Procedure: This function is used to add matrices.
*			 
************************************************************************/
int** matrix_add(int **a, int **b, int dim){
	int **temp = (int **)calloc(dim, sizeof(int*));
	for(int i = 0; i < dim; i++){
		temp[i] = (int *) calloc(dim, sizeof(int));
	} 
	for(int i = 0; i < dim; i++){
		for(int j = 0; j < dim; j++){
			temp[i][j] = a[i][j] + b[i][j];
		}
	}
	return temp;
}

/************************************************************************
* Function: void matrix_sub(int **, int **, int)
* Input   : int **a : 2D array.
			int **b: 2D array.
			int dim: size of matrix
* Output  : int** temp: return addition of matrices.
* Procedure: This function is used to substract matrices.
*			 
************************************************************************/
int** matrix_sub(int **a, int **b, int dim){
	int **temp = (int **)calloc(dim, sizeof(int*));
	for(int i = 0; i < dim; i++){
		temp[i] = (int *) calloc(dim, sizeof(int));
	} 
	for(int i = 0; i < dim; i++){
		for(int j = 0; j < dim; j++){
			temp[i][j] = a[i][j] - b[i][j];
		}
	}
	return temp;
}

/************************************************************************
* Function: void compose(int **, int **, int **, int **, int)
* Input   : int **a : 2D array.
			int **b : 2D array.
			int **c : 2D array.
			int **d : 2D array.
			int dim: size of matrix
* Output  : int** temp: composed matrix.
* Procedure: This function is used to compose the larger matrix from
			 sub matrices.
*			 
************************************************************************/
int** compose(int **a, int **b, int **c, int **d, int dim){
	int **temp = (int **)calloc(dim, sizeof(int*));
	for(int i = 0; i < dim; i++){
		temp[i] = (int *) calloc(dim, sizeof(int));
	} 
	for(int i = 0; i < dim; i++){
		for(int j = 0; j < dim; j++){
			if(i < dim/2){
				if(j < dim/2){
					temp[i][j] = a[i][j];
				}else{
					temp[i][j] = b[i][j - dim/2];
				}
			}else{
				if(j < dim/2){
					temp[i][j] = c[i-dim/2][j];
				}else{
					temp[i][j] = d[i-dim/2][j - dim/2];
				}
			}
		}
	}
	return temp;
}

/************************************************************************
* Function: void standard_matrix_multiplication(int **, int **, int)
* Input   : int **a : 2D array.
			int **b : 2D array.
			int dim: size of matrix
* Output  : int** temp: return matrix matrix.
* Procedure: This function is used to multiply matrices.
*			 
************************************************************************/
int** standard_matrix_multiplication(int ** a, int **b, int dim){
	int **temp = (int **)calloc(dim, sizeof(int*));
	for(int i = 0; i < dim; i++){
		temp[i] = (int *) calloc(dim, sizeof(int));
	}
	for(int i = 0; i < dim; i++){
		for(int j = 0; j < dim; j++){
			for(int k = 0; k < dim; k++)
			temp[i][j] = temp[i][j] + a[i][k] * b[k][j];
		}
	}
	return temp;
}

/************************************************************************
* Function: void strassen_multiplication(int **, int **, int)
* Input   : int **matrix1 : 2D array.
			int **matrix2 : 2D array.
			int dim: size of matrix
* Output  : int**: return strassen matrix multiplication.
* Procedure: This function is used to multiply matrices using strassen's
			 multiplication. This function uses divide and conquer approach
			 to calculate matrix multiplication.
*			 
************************************************************************/
int** strassen_multiplication(int **matrix1, int **matrix2, int n){
	if( n == 2){
		/* Base Conditon n = 2*/
		/* dividing matrix 1 into a11, a12, a21, a22. */
		int **a = divide(matrix1,(n-n),(n-n),n/2);
		int **b = divide(matrix1,(n-n),(n-n/2),n/2);
		int **c = divide(matrix1,(n-n/2),(n-n),n/2);
		int **d = divide(matrix1,(n-n/2),(n-n/2),n/2);
		/* dividing matrix 2 into b11, b12, b21, b22. */
		int **e = divide(matrix2,(n-n),(n-n),n/2);
		int **f = divide(matrix2,(n-n),(n-n/2),n/2);
		int **g = divide(matrix2,(n-n/2),(n-n),n/2);
		int **h = divide(matrix2,(n-n/2),(n-n/2),n/2);
		/* Calculating m1 to m7. */
		int m1 = (a[0][0] + d[0][0]) * (e[0][0] + h[0][0]);
		int m2 = (c[0][0] + d[0][0]) * e[0][0];
		int m3 = a[0][0] * (f[0][0] - h[0][0]);
		int m4 = d[0][0] * (g[0][0] - e[0][0]);
		int m5 = (a[0][0] + b[0][0]) * h[0][0];
		int m6 = (c[0][0] - a[0][0]) * (e[0][0] + f[0][0]);
		int m7 = (b[0][0] - d[0][0]) * (g[0][0] + h[0][0]);
		/* Calculating c1, c2, c3, c4. */
		int c1 = m1 + m4 + m7 - m5;
		int c2 = m3 + m5;
		int c3 = m2 + m4;
		int c4 = m1 + m3 + m6 - m2;
		
		int *temp1 = &c1;
		int *temp2 = &c2;
		int *temp3 = &c3;
		int *temp4 = &c4;
		return compose(&temp1,&temp2,&temp3,&temp4,n);
	}else{
		/* dividing matrix 1 into a11, a12, a21, a22. */
		int **a = divide(matrix1,(n-n),(n-n),n/2);
		int **b = divide(matrix1,(n-n),(n-n/2),n/2);
		int **c = divide(matrix1,(n-n/2),(n-n),n/2);
		int **d = divide(matrix1,(n-n/2),(n-n/2),n/2);
		/* dividing matrix 2 into b11, b12, b21, b22. */
		int **e = divide(matrix2,(n-n),(n-n),n/2);
		int **f = divide(matrix2,(n-n),(n-n/2),n/2);
		int **g = divide(matrix2,(n-n/2),(n-n),n/2);
		int **h = divide(matrix2,(n-n/2),(n-n/2),n/2);
		/* Calculating m1 to m7 using recursive calls. */		
		int **m1 = strassen_multiplication(matrix_add(a, d, n/2), matrix_add(e, h, n/2), n/2);
		int **m2 = strassen_multiplication(matrix_add(c, d, n/2), e, n/2);
		int **m3 = strassen_multiplication(a, matrix_sub(f, h, n/2), n/2);
		int **m4 = strassen_multiplication(d, matrix_sub(g, e, n/2), n/2);
		int **m5 = strassen_multiplication(matrix_add(a, b, n/2), h, n/2);
		int **m6 = strassen_multiplication(matrix_sub(c, a, n/2), matrix_add(e, f, n/2), n/2);
		int **m7 = strassen_multiplication(matrix_sub(b, d, n/2), matrix_add(g, h, n/2), n/2);
		/* Calculating c1, c2, c3, c4. */
		int **c1 = matrix_sub(matrix_add(matrix_add(m1, m4, n/2), m7, n/2), m5, n/2);
		int **c2 = matrix_add(m3, m5, n/2);
		int **c3 = matrix_add(m2, m4, n/2);
		int **c4 = matrix_sub(matrix_add(matrix_add(m1, m3, n/2), m6, n/2), m2, n/2);
		return compose(c1, c2, c3, c4, n);
	}
}

/************************************************************************
* Function: void create_matrix(int **, int)
* Input   : int **a : 2D array.
			int size: size of matrix
* Output  : None.
* Procedure: This function is used to generate matrix element.
*			 
************************************************************************/
void create_matrix(int **matrix, int size){
	srand(time(NULL)); 
	for(int i = 0; i < size; i++){
		for(int j = 0; j< size; j++){
			matrix[i][j] = rand() % 10;
		}
	}
}

/************************************************************************
* Function: void is_poweer(int)
* Input   : int size: size of matrix
			
* Output  : bool.
* Procedure: This function is used to return true if n is of power of 2.
*			 
************************************************************************/
bool is_power(int n){
	while((n % 2) == 0 && n > 1){
		n = n /2;
	}
	return ( n == 1);
}


/************************************************************************
* Function: int main(int, char* [])
* Input   : int argc - number of input parameters
			char *arg[] - size.
* Procedure: Main function accepts the 1 parameter - size of matrix.
			 1. Check if size if it is power of 2 or not.
			 2. Allocate memory to matrices.
			 3. create matrix 1 and matrix 2.
			 4. Multiply using strassen's method.
			 5. Multiply using standard method.
************************************************************************/
int main(int argc, char *arg[]){
	if(argc != 2){
		fprintf(stderr, "Error while accepting arguments!!!");
	}else{
		int size = atoi(arg[1]);
		if(!is_power(size)){
			fprintf(stderr," Size is not a power of 2. \n");
			exit(0);
		}
		/* Allocating memory to first matrix */
		first_matrix = (int **)calloc(size, sizeof(int*));
		for(int i = 0; i < size; i++){
			first_matrix[i] = (int *) calloc(size, sizeof(int));
		}
		/* Allocating memory to second matrix */
		second_matrix = (int **)calloc(size, sizeof(int*));
		for(int i = 0; i < size; i++){
			second_matrix[i] = (int *) calloc(size,sizeof(int));
		}
		/* Allocating memory to resulting matrix */
		result_matrix = (int **)calloc(size, sizeof(int*));
		for(int i = 0; i < size; i++){
			result_matrix[i] = (int *) calloc(size,sizeof(int));
		}
		create_matrix(first_matrix,size);
		create_matrix(second_matrix,size);
		printf("------ Matrix A ------\n\n");
		print_matrix(first_matrix,size);
		printf("------ Matrix B ------\n\n");
		print_matrix(second_matrix,size);
		printf("------ Strassen's Matrix Multiplication ------ \n\n");
		result_matrix = strassen_multiplication(first_matrix, second_matrix, size);
		print_matrix(result_matrix, size);
		printf("------ Standard Matrix Multiplication ------ \n\n");
		int ** standard_matrix = standard_matrix_multiplication(first_matrix, second_matrix, size);
		print_matrix(standard_matrix, size);
	}
	return 1;
}
