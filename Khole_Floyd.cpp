/********************************************************************
*  Author: Shreyas Khole.
*  Course: CS 575.
*  Date: 04/8/2014
*  Purpose: To implement the FLOYD's ALGORITHM using dynamic programming.
*  Floyd's Algorithm: Find the all pair shortest path a given graph.
*
********************************************************************/

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Minimum number of vertices */
#define MIN_VERTICES 5

#define PRINT 100

/************************************************************************
* Function: void print_matrix(int**, int)
* Input   : int **matrix : Input Matrix
			int row : Number of rows in matrix
			int column : Number of columns in matrix
* Output  : None
* Procedure: This function is used to print the elements of a matrix. 
************************************************************************/
void print_matrix(int **graph, int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%d\t", graph[i][j]);
		}
		printf("\n\n");
	}
}

/************************************************************************
* Function: void allocate_memory(int **, int, int)
* Input   : char **matrix : matrix.
			int row : number of rows of matrix
			int col : number of columns of matrix
* Output  : None
* Procedure: This function is used to allocate a memory to the matrix 
			 dynamically using calloc() function.
			 
************************************************************************/
int** allocate_memory(int vertices){
	int **matrix;
	matrix = (int **)calloc(vertices, sizeof(int *));
	if(matrix == NULL){
		fprintf(stderr,"Error while allocating memory to matrix !!!");
		exit(0);
	}
	for(int i = 0; i < vertices; i++){
		matrix[i] = (int *)calloc(vertices, sizeof(int));
		if(matrix[i] == NULL){
			fprintf(stderr,"Error while allocating memory to row of a matrix!!!");
			exit(0);
		}
	}
	return matrix;
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
void free_memory(int **a, int size){
	for(int i = 0; i < size; i++){
		free(a[i]);													
	}
	free(a);														
}

/************************************************************************
* Function: void init_adjacency_matrix(int **, int vertices)
* Input   : int **graph : adjacency matrix
			int vertices : number of vertices
* Output  : None
* Procedure: This function is used to initialize the adjacency weight 
			 matrix. The function will create undirected complete graph
			 as per requirements.
************************************************************************/
void init_adjacency_matrix(int **matrix, int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			int number = 1 + rand() % 10;
			if(i == j){
				matrix[i][j] = 0;
			}else if(i < j){
				matrix[i][j] = number;
			}else{
				matrix[i][j] = matrix[j][i];
			}
		}
	}
}

/************************************************************************
* Function: void print_floyd_short_path(int **, int start_node, int end_node)
* Input   : int **matrix : print_array
			int start_node : start node
			int end_node: end node
* Output  : None
* Procedure: This function prints the shortest path from the 
			 source to dest using print_matrix.
************************************************************************/
void print_floyd_short_path(int **print_matrix, int start_node, int end_node){
	if(print_matrix[start_node][end_node] != PRINT){
		print_floyd_short_path(print_matrix, start_node, print_matrix[start_node][end_node]);
		printf("  Node %d--->\t ", print_matrix[start_node][end_node]);
		print_floyd_short_path(print_matrix, print_matrix[start_node][end_node], end_node);
	}
}

/************************************************************************
* Function: void dijkstra_algorithm(int **, int vertices)
* Input   : int **graph : adjacency matrix
			int vertices : number of vertices
* Output  : None
* Procedure: This function is used to calculate all pairs shortest 
			 distance using FLOYD'S ALGORITHM.
************************************************************************/
void floyd_algorithm(int **graph, int vertices){
	/* Allocating memory to distance matrix */
	int **distance_matrix = allocate_memory(vertices);
	/* Allocating memory to print matrix */
	int **print_distance = allocate_memory(vertices + 1);
	/* intializing distance matrix with graph */
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			distance_matrix[i][j] = graph[i][j];
			print_distance[i][j] = PRINT;
		}
	}
	for(int k = 0; k < vertices; k++){
		for(int i = 0; i < vertices; i++){
			for(int j = 0; j < vertices; j++){
				if(distance_matrix[i][j] > distance_matrix[i][k] + distance_matrix[k][j]){
					distance_matrix[i][j] = distance_matrix[i][k] + distance_matrix[k][j];
					print_distance[i][j] = k;
				}
			}
		}	
	}
	/* Printing Distance Matrix */
	printf("----- DISTANCE MATRIX ----- \n");
	print_matrix(distance_matrix, vertices);
	/* Printing pring matrix */
	printf("----- PRINT MATRIX ----- \n");
	print_matrix(print_distance, vertices);
	/* Printing all pairs shortest path and their distance*/
	printf("-----------------------------------------\n\n");
	printf("Start \t End \t Distance \t Path \n");
	printf("-----------------------------------------\n\n");
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			int start_node = i;
			int end_node = j;
			printf("%d \t %d\t %d \t\t", start_node, end_node, distance_matrix[i][j]);
			printf("Node %d---> ", start_node);
			print_floyd_short_path(print_distance, start_node, end_node);
			printf("Node %d \n", end_node);
			printf("\n");
		}
	}
	/* Freeing memory of distance matrix */
	free_memory(distance_matrix, vertices);
	/* Freeing memory of print matrix */
	free_memory(print_distance, vertices);
}

/************************************************************************
* Function: int main()
* Input   : None
* Procedure: 1. Calculate number of vertices randomly.
			 2. Allocate memory to adjacency matrix.
			 3. intialize with randomly generated values.
			 4. Print Adjacency matrix.
			 5. Calculate all pairs shortest path using floyd's algo,
			 6. Free memory.
************************************************************************/
int main(){
	srand(time(NULL));
	printf("---------- FLOYD'S ALGORITHM -----------\n");
	printf("\n");
	/* Calculating number of vertices .*/
	int vertices = MIN_VERTICES + rand() % 6;
	printf("NUMBER OF VERTICES IN UNDIRECTED COMPLETE GRAPH ARE %d\n", vertices);
	/* Allocating memory to adjacency matrix */
	int **adjacency_matrix = allocate_memory(vertices + 1);
	/* Initializing adjacency matrix */
	init_adjacency_matrix(adjacency_matrix, vertices);
	/* Printing adjacency matrix */
	printf("\n------ ADJACENCY MATRIX ------\n\n");
	print_matrix(adjacency_matrix, vertices);
	/* Finding all pairs shortest path */
	floyd_algorithm(adjacency_matrix, vertices);
	/* Freeing memory of adjacency matrix */
	free_memory(adjacency_matrix, vertices);
	return 0;
}
