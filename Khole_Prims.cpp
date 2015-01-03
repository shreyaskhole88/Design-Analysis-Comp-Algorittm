/********************************************************************
*  Author: Shreyas Khole.
*  Course: CS 575.
*  Date: 04/8/2014
*  Purpose: To implement the PRIM's ALGORITHM using greedy method.
*  PRIM's Algorithm: Find the Minimum Spanning Tree a given graph.
*
********************************************************************/

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Minimum number of vertices */
#define MIN_VERTICES 5
/* Infinite distance as max distance between nodes is 10 */
#define INFINITY 1000
/* Initial parent value of each node*/
#define PARENT -1
/* Source node for finding path. */
#define START_NODE 0

/************************************************************************
* Function: void print_matrix(int**, int)
* Input   : int **matrix : Input Matrix
			int row : Number of rows in matrix
			int column : Number of columns in matrix
* Output  : None
* Procedure: This function is used to print the elements of a matrix. 
************************************************************************/
void print_matrix(int **matrix, int n){
	for(int i =0; i < n; i++){
		for(int j =0; j < n; j++){
			printf("%d\t", matrix[i][j]);
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
* Function: void get_minimum_weight_node(int *, bool *, int n)
* Input   : int *cost : cost/distance array
			int *node_in_mst : list of visited nodes
			int n : number of vertices
* Output  : None
* Procedure: This function is used to get minimum distance/cost node
			 which is adjacent to selected node.
************************************************************************/
int get_minimum_weight_node(int *cost, bool *node_in_mst, int n){
	int minimum_weight = INFINITY;
	int minimum_weight_node;
	for(int i = 0; i < n; i++){
		/* Checking for minimum distance/code node and node is not visited previously. */
		if(node_in_mst[i] == false && cost[i] < minimum_weight){
			minimum_weight = cost[i];
			minimum_weight_node = i;
		}
	}
	return minimum_weight_node;
}

/************************************************************************
* Function: void print_MST(int **, int *, int vertices)
* Input   : int **matrix : print_array
			int *previous_node : parent node array
			int vertices : number of vertices
* Output  : None
* Procedure: This function prints the Edges in MST and total weight of
			 MST.
************************************************************************/
void print_MST(int **graph, int *previous_node, int vertices){
	int sum = 0;
	printf("--------------------------------------------\n");
	printf("\nEdge\t\t Weight\n");
	printf("--------------------------------------------\n");
	for(int i = 1; i < vertices; i++){
		printf("%d--%d \t\t %d\n", previous_node[i], i, graph[previous_node[i]][i]);
		sum = sum + graph[previous_node[i]][i];
	}
	printf("-------------------------------------------\n");
	printf("Minimum Spanning Tree ----> %d\n", sum);
}

/************************************************************************
* Function: void prims_algorithm(int **, int vertices)
* Input   : int **graph : adjacency matrix
			int vertices : number of vertices
* Output  : None
* Procedure: This function is used to calculate MST using
			 PRIM'S ALGORITHM.
************************************************************************/
void prims_algorithm(int **graph, int vertices){
	/* previous_node array for keeping track of previous visited node */
	int *previous_node = (int *)malloc(sizeof(int) * vertices);
	/* cost array used to store shortest path from source node. */
	int *cost_node = (int *)malloc(sizeof(int) * vertices);
	/* stores the visited node in graph */
	bool *node_in_mst = (bool *)malloc(sizeof(bool) * vertices);
	/* intializing cost, parent and node_in_mst */
	for(int i = 0; i < vertices; i++){
		previous_node[i] = PARENT;													
		cost_node[i] = INFINITY;
		node_in_mst[i] = false;
	}
	int initial_node = START_NODE;
	cost_node[initial_node] = 0;
	int count = vertices;
	while(count > 1){
		/* Get minimum weight node from graph */
		int minimum_weight_node = get_minimum_weight_node(cost_node, node_in_mst, vertices);
		node_in_mst[minimum_weight_node] = true;
		/* Iterate for all adjacent nodes */
		for(int node = 0; node < vertices; node++){
			/* consider only those vertex which is not visited and has distance less than the distance in cost. */
			if(graph[minimum_weight_node][node] && node_in_mst[node] == false && graph[minimum_weight_node][node] < cost_node[node]){
				cost_node[node] = graph[minimum_weight_node][node];
				previous_node[node] = minimum_weight_node;
			}
		}
		count--;
	}
	/* Print Edges in MST */
	print_MST(graph, previous_node, vertices);
	/* Freeing memory */
	free(previous_node);
	/* Freeing memory */
	free(cost_node);
	/* Freeing memory */
	free(node_in_mst);
}

/************************************************************************
* Function: int main()
* Input   : None
* Procedure: 1. Calculate number of vertices randomly.
			 2. Allocate memory to adjacency matrix.
			 3. Intialize with randomly generated values.
			 4. Print Adjacency matrix.
			 5. Calculate MST using prim's algo.
			 6. Free memory.
************************************************************************/
int main(){
	srand(time(NULL));
	printf("---------- PRIM'S ALGORITHM -----------\n");
	printf("\n");
	/* Calculating number of vertices .*/
	int vertices = MIN_VERTICES + rand() % MIN_VERTICES;
	printf("NUMBER OF VERTICES IN UNDIRECTED COMPLETE GRAPH ARE %d\n", vertices);
	/* Allocating memory to adjacency matrix */
	int **adjacency_matrix = allocate_memory(vertices);
	/* Initializing adjacency matrix */
	init_adjacency_matrix(adjacency_matrix, vertices);
	printf("\n------ ADJACENCY MATRIX ------\n\n");
	print_matrix(adjacency_matrix, vertices);
	/* Finding MST in graph */
	prims_algorithm(adjacency_matrix, vertices);
	/* Freeing memory of adjacency matrix */
	free_memory(adjacency_matrix, vertices);
	return 0;
}
