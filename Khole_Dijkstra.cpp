/********************************************************************
*  Author: Shreyas Khole.
*  Course: CS 575.
*  Date: 04/8/2014
*  Purpose: To implement the DIKSTRA's ALGORITHM using dynamic programming.
*  Dijkstra's Algorithm: Find the shortest path from source node to
						 destination node.
*
********************************************************************/

/* Includes */
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
#define SOURCE_NODE 0

/************************************************************************
* Function: void print_matrix(int**, int)
* Input   : int **matrix : Input Matrix
			int row : Number of rows in matrix
			int column : Number of columns in matrix
* Output  : None
* Procedure: This function is used to print the elements of a matrix. 
************************************************************************/
void print_matrix(int **matrix, int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
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
* Function: void parent_node(int)
* Input   : int i : size of heap
* Output  : return i/2
* Procedure: This function is used for getting the parent node in 
			 min heap. 
************************************************************************/
int parent_node(int i) {
	return i / 2;
}

/************************************************************************
* Function: void left_child(int)
* Input   : int i : parent node
* Output  : return 2*i
* Procedure: This function is used for getting the left child node of 
			 parent node in min heap. 
************************************************************************/
int left_child(int i) {
	return 2 * i;
}

/************************************************************************
* Function: void right_child(int)
* Input   : int i : size of heap
* Output  : return 2*i + 1
* Procedure: This function is used for getting the right child node of 
			 parent node in min heap. 
************************************************************************/
int right_child(int i) {
	return 2 * i + 1;
}

/************************************************************************
* Function: void exchange(int [], int [], int [], int i, int minimum)
* Input   : int distance[] : distance array
			int heap_node[] : array for storing the nodes (acts as a heap)
			int heap_index[] : this gives the index of node in a heap
			int i : node
			int minimum : replace node with this minimum node
* Output  : None
* Procedure: This function is used for swapping the minimum node and
			 given node in a heap.
************************************************************************/
void exchange(int distance[], int heap_node[], int heap_index[], int i, int minimum) {
	int distance_temp;
	int heap_node_temp;
	/* Exchange the distance in nodes i and minimum. */
	distance_temp = distance[i];
	distance[i] = distance[minimum];
	distance[minimum] = distance_temp;
	/* Exchange nodes in heap i and minimum. */
	heap_node_temp = heap_node[i];
	heap_node[i] = heap_node[minimum];
	heap_node[minimum] = heap_node_temp;
	/* Update the heap_index values. */
	heap_index[heap_node[i]] = i;
	heap_index[heap_node[minimum]] = minimum;
}

/************************************************************************
* Function: void heapify(int [], int [], int [], int i, int size)
* Input   : int distance[] : distance array
			int heap_node[] : array for storing the nodes (acts as a heap)
			int heap_index[] : this gives the index of node in a heap
			int i : node
			int size : size of heap.
* Output  : None
* Procedure: This function is responsible for maintaining the heap 
			 property of a heap. Heapify() works by swapping the current 
			 node with the minimum of its children, then it does a 
			 recursive call on the swapped node.
************************************************************************/
void heapify(int distance[], int heap_node[], int heap_index[], int i, int heap_size){
	int left = left_child(i);
	int right = right_child(i);
	int min;
	/* checking if left child is smaller than parent node i */
	if (left < heap_size && distance[left] < distance[i]){
		min = left;		
	}else{
		min = i;		
	}
	/* checking if right child is smaller than parent node i */
	if (right < heap_size && distance[right] < distance[min]){
		min = right;
	}
	/* Checking if min heap property is violated or not, if yes
	   exchanging nodes and again heapifying the heap. */
	if (min != i) {
		exchange(distance, heap_node, heap_index, i, min);
		heapify(distance, heap_node, heap_index, min, heap_size);
	}
}

/************************************************************************
* Function: void create_heap(int [], int [], int [], int size)
* Input   : int distance[] : distance array
			int heap_node[] : array for storing the nodes (acts as a heap)
			int heap_index[] : this gives the index of node in a heap
			int size : size of heap.
* Output  : None
* Procedure: This function builds a min-heap from an unordered array. 
			 The function begins with the largest non-leaf nodes and 
			 calls Heapify() on them. The heap is created on distance
			 array.
************************************************************************/
void create_heap(int distance[], int handle[], int heap_index[], int heap_size) {
	for (int i = parent_node(heap_size); i >= 0; --i){
		heapify(distance, handle, heap_index, i, heap_size);
	}
}

/************************************************************************
* Function: void create_heap(int [], int [], int [],int size)
* Input   : int distance[] : distance array
			int heap_node[] : array for storing the nodes (acts as a heap)
			int heap_index[] : this gives the index of node in a heap
			int size : size of heap.
* Output  : None
* Procedure: This function removes the element with the minimum value 
			 (i.e. the root node) and heapify the remaining heap.
			 Here, function will put the value at the end of heap.
************************************************************************/
int extract_min(int distance[], int heap_node[], int heap_index[], int heap_size) {
	int minimum_node = heap_node[0];
	exchange(distance, heap_node, heap_index, 0, heap_size-1);
	heapify(distance, heap_node, heap_index, 0, heap_size-1);
	return minimum_node;
}

/************************************************************************
* Function: void create_heap(int [], int [], int [], int i, int size, int new_distance)
* Input   : int distance[] : distance array
			int heap_node[] : array for storing the nodes (acts as a heap)
			int heap_index[] : this gives the index of node in a heap
			int i : node
			int size : size of heap
			int new_distance : new shortest path from source node.
* Output  : None
* Procedure: This function replaces the distance with shortest path and
			 heapify the min heap till min heap property is restored.
************************************************************************/
void decrease_key(int distance[], int handle[], int heap_index[], int i, int size, int new_key) {
	distance[i] = new_key;
	while (i > 0 && distance[parent_node(i)] > distance[i]) {
		exchange(distance, handle, heap_index, i, parent_node(i));
		i = parent_node(i);
	}
}

/************************************************************************
* Function: void print_shortest_path(int [], int dest)
* Input   : int parent[] : parent array
			int node : vertex in graph
* Output  : None
* Procedure: This function prints the shortest path from the 
			 source to dest.
************************************************************************/
int print_path(int parent[], int dest) {
	if (parent[dest] != PARENT)
		print_path(parent, parent[dest]);
	printf("Node %d ", dest);
}

/************************************************************************
* Function: void print_shortest_path(int [], int [], int size)
* Input   : int distance[] : distance array
			int heap_index[] : this gives the index of node in a heap
			int size : size of heap
* Output  : None
* Procedure: This function is used to print the shortest path from
			 source node with their length.
************************************************************************/
void print_shortest_path(int distance[], int heap_index[], int parent[], int size){
	printf("SOURCE \t DEST \t DISTANCE\t PATH\n");
	for (int i = 0; i < size; i++) {
    	printf(" %d\t %d\t %d\t\t", 0, i, distance[heap_index[i]]);
    	print_path(parent, i);
    	printf("\n");
  	}
}

/************************************************************************
* Function: void dijkstra_algorithm(int **, int vertices)
* Input   : int **graph : adjacency matrix
			int vertices : number of vertices
* Output  : None
* Procedure: This function is used to calculate shortest distance using
			 DIJKSTRA'S ALGORITHM.
************************************************************************/
void dijkstra_algorithm(int **graph, int vertices){
	/* Distance array used to store shortest path from source node. */
	int distance[vertices];
	/* parent array for keeping track of prvious visited node */
	int parent[vertices];
	/* Min heap using vertices, calculated from distance array*/
	int heap_node[vertices];
	/* Used to store index of each node in min heap. */
	int heap_index[vertices];
	/* initializing distance, heap_node and heap_index
	   TIME COMPLEXITY is O(no of vertices)*/
	for(int i = 0; i < vertices; i++){
		distance[i] = INFINITY;
		heap_node[i] = i;
		heap_index[i] = i;
		parent[i] = PARENT;
	}
	distance[SOURCE_NODE] = 0;
	/* Build min heap. */
	create_heap(distance, heap_node, heap_index, vertices);
	int size = vertices;
	/* Calculate shortest path for each node.
	   TIME COMPLEXITY O(vertices)*/
	while(size > 0){
		/* Get minimum value node/root from min heap as a shortest path node. */
		int near = extract_min(distance, heap_node, heap_index, size);
		size--;
		/* Adjacent vertices of near*/
		for(int v = 0; v <= size; v++){
			if (distance[heap_index[v]] > distance[heap_index[near]] + graph[near][v]){
				/* decrease key, exhcange new distance with previous one */
				decrease_key(distance, heap_node, heap_index, heap_index[v], size, distance[heap_index[near]] + graph[near][v]);
				/* Keeping track of parent element */
    			parent[v] = near;
			}
		}
	}
	/* Print shortes path. */
	print_shortest_path(distance, heap_index, parent, vertices);
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
void init_adjacency_matrix(int **graph, int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			int number = 1 + rand() % 10;
			if(i == j){
				graph[i][j] = 0;
			}else if(i < j){
				graph[i][j] = number;
			}else{
				graph[i][j] = graph[j][i];
			}
		}
	}
}

/************************************************************************
* Function: int main()
* Input   : None
* Procedure: 1. Calculate number of vertices randomly.
			 2. Allocate memory to adjacency matrix.
			 3. Intialize with randomly generated values.
			 4. Print Adjacency matrix.
			 5. Calculate shortest path between source node and all 
			    other nodesusing dijkstra's algo,
			 6. Free memory.
************************************************************************/
int main(){
	srand(time(NULL));
	int vertices = MIN_VERTICES + rand() % 6;
	printf("---------- DIJKSTRA'S ALGORITHM -----------\n");
	printf("\n");
	printf("NUMBER OF VERTICES IN UNDIRECTED COMPLETE GRAPH ARE %d\n", vertices);
	/* Allocating memory to adjacency matrix */
	int **adjacency_matrix = allocate_memory(vertices);
	/* Initializing adjacency matrix */
	init_adjacency_matrix(adjacency_matrix, vertices);
	/* Printing adjacency matrix */
	printf("\n------ ADJACENCY MATRIX ------\n\n");
	print_matrix(adjacency_matrix, vertices);
	/* Finding shortest path */
	dijkstra_algorithm(adjacency_matrix, vertices);
	/* Freeing memory of adjacency matrix */
	free_memory(adjacency_matrix, vertices);
	return 0;
}
