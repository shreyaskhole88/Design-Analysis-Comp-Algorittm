/********************************************************************
*  Author: Shreyas Khole.
*  Course: CS 575.
*  Date: 03/18/2014
*  Purpose: To implement the Tromino Tiling Problem by 
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

/* Representing Tromino Tile. */
#define FILL 'O'
/* Representing Hole. */
#define EMPTY 'X'
/* Representing Initial Space. */
#define INITIAL '$'

/*
* Structure for holding hole coordinates.
*/
struct Hole{
	int x_coordinate;
	int y_coordinate;
};

/*
* Declaring 2D array/matrix of type char.
* This variable is used to as a tromino 
* board.
*/
char **board;

/************************************************************************
* Function: void print_tile(char **, int)
* Input   : char **a : 2D array.
			int m: size of matrix
* Output  : None
* Procedure: This function is used to print the 2D array.
*			 
************************************************************************/
void print_tile(char **a, int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%c\t", a[i][j]);
		}
		printf("\n\n");
	}
}

/************************************************************************
* Function: void get_power(int)
* Input   : int index : index
* Output  : None
* Procedure: This function is used to find the 2^index.
*			 
************************************************************************/
int get_power(int index){
    int temp;
    if( index == 0)
       return 1;
    temp = get_power(index/2);       
    if (index % 2 == 0)
        return temp * temp;
    else
    {
        if(index > 0)
            return 2 * temp * temp;
        else
            return (temp * temp) / 2;
    }
}

/************************************************************************
* Function: void get_hole(int)
* Input   : int n: length of tromino board.
* Output  : Hole* : retruns hole with x_coordinate and y_coordinate
*
* Procedure: This function is used to generate the hole randomly
			 in tromino board.
*			 
************************************************************************/
Hole* get_hole(int n){
	Hole *hole = (Hole *)malloc(sizeof(Hole *));
	/* Intializing the psuedo random generator. */
	srand(time(NULL));
	hole->x_coordinate = rand() % n;
	hole->y_coordinate = rand() % n;
	return hole;
}

/************************************************************************
* Function: void create_tromino_tile(int)
* Input   : int index: index.
* Output  : Hole* : retruns hole with x_coordinate and y_coordinate
*
* Procedure: This function is used to create/initialize the tromino 
			 board with initial space and hole.
*			 
************************************************************************/
Hole* create_tromino_tile(int index){
	int number_of_tiles = get_power(index);
	/* Allocating memory to first matrix */
	board = (char **)calloc(number_of_tiles, sizeof(char *));					
	for(int i = 0; i < number_of_tiles; i++){
		board[i] = (char *) calloc(number_of_tiles, sizeof(char));
	}
	Hole *hole = get_hole(number_of_tiles);
	printf("\t------Original Board with Randomly Generated Hole: (%d,%d)------\n\n",hole->x_coordinate, hole->y_coordinate);
	for(int i = 0; i < number_of_tiles; i++){
		for(int j = 0; j< number_of_tiles; j++){
			if(i == hole->x_coordinate && j == hole->y_coordinate){
				board[i][j] = EMPTY;
			}else{
				board[i][j] = INITIAL;				
			}
		}
	}
	print_tile(board, number_of_tiles);
	return hole;
}

/************************************************************************
* Function: void tromino_tile(char **, int, int, int, int, int)
* Input   : char **tile: tromino board
			int x_start: starting x coordinate
			int y_start: starting y coordinate
			int index: index
			int x_point: x coordinate of hole
			int y_point: y coordinate of hole
* Output  : None.
*
* Procedure: This function is used to fill the tromino board 
			 using tromino tile using divide and conquer approach.
			 This function finds the hole in appropriate quadrant and
			 creates the imaginary holes and starts filling the tromino
			 tile.
*			 
************************************************************************/
void tromino_tile(char **tile, int x_start, int y_start, int index, int x_point, int y_point){
	int center = get_power(index)/2;
	if(index == 1){
		/* Trivial Condition */
		if(x_point <= x_start + center - 1 && y_point <= y_start + center - 1){
			/* hole is in first quadrant */
			tile[x_start + center - 1][y_start + center] = FILL;
			tile[x_start + center][y_start + center - 1] = FILL;
			tile[x_start + center][y_start + center] = FILL;
		}else if(x_point <= x_start + center - 1 && y_point > y_start + center - 1){
			/* hole is in second quadrant */
			tile[x_start + center - 1][y_start + center - 1] = FILL;
			tile[x_start + center][y_start + center - 1] = FILL;
			tile[x_start + center][y_start + center] = FILL;
		}else if(x_point > x_start + center - 1 && y_point <= y_start + center - 1){
			/* hole is in third quadrant */
			tile[x_start + center - 1][y_start + center - 1] = FILL;
			tile[x_start + center - 1][y_start + center] = FILL;
			tile[x_start + center][y_start + center] = FILL;
		}else{
			/* hole is in fourth quadrant */
			tile[x_start + center - 1][y_start + center - 1] = FILL;
			tile[x_start + center - 1][y_start + center] = FILL;
			tile[x_start + center][y_start + center - 1] = FILL;
		}
	}else{
		if(x_point <= x_start + center - 1 && y_point <= y_start + center - 1){
			/* hole is in first quadrant */
			tile[x_start + center - 1][y_start + center] = FILL;
			tile[x_start + center][y_start + center - 1] = FILL;
			tile[x_start + center][y_start + center] = FILL;
			tromino_tile(tile,x_start,y_start, index - 1, x_point, y_point);
			tromino_tile(tile,x_start,y_start + center, index - 1, x_start + center - 1, y_start + center);
			tromino_tile(tile, x_start + center, y_start, index - 1, x_start + center, y_start + center - 1);
			tromino_tile(tile, x_start + center, y_start + center, index - 1, x_start + center, y_start + center);
		}else if(x_point <= x_start + center - 1 && y_point > y_start + center - 1){
			/* hole is in second quadrant */
			tile[x_start + center - 1][y_start + center - 1] = FILL;
			tile[x_start + center][y_start + center - 1] = FILL;
			tile[x_start + center][y_start + center] = FILL;
			tromino_tile(tile,x_start,y_start, index - 1, x_start + center - 1, y_start + center - 1);
			tromino_tile(tile,x_start,y_start + center, index - 1, x_point, y_point);
			tromino_tile(tile, x_start + center, y_start, index - 1, x_start + center, y_start + center - 1);
			tromino_tile(tile, x_start + center, y_start + center, index - 1, x_start + center, y_start + center);
		}else if(x_point > x_start + center - 1 && y_point <= y_start + center - 1){
			/* hole is in third quadrant */
			tile[x_start + center - 1][y_start + center - 1] = FILL;
			tile[x_start + center - 1][y_start + center] = FILL;
			tile[x_start + center][y_start + center] = FILL;
			tromino_tile(tile,x_start,y_start, index - 1, x_start + center - 1, y_start + center - 1);
			tromino_tile(tile,x_start,y_start + center, index - 1, x_start + center - 1, y_start + center);
			tromino_tile(tile, x_start + center, y_start, index - 1, x_point, y_point);
			tromino_tile(tile, x_start + center, y_start + center, index - 1, x_start + center, y_start + center);
		}else{
			/* hole is in fourth quadrant */
			tile[x_start + center - 1][y_start + center - 1] = FILL;
			tile[x_start + center - 1][y_start + center] = FILL;
			tile[x_start + center][y_start + center - 1] = FILL;
			tromino_tile(tile,x_start,y_start, index - 1, x_start + center - 1, y_start + center - 1);
			tromino_tile(tile,x_start,y_start + center, index - 1, x_start + center - 1, y_start + center);
			tromino_tile(tile, x_start + center, y_start, index - 1, x_start + center, y_start + center - 1);
			tromino_tile(tile, x_start + center, y_start + center, index - 1, x_point, y_point);
		}
	}
}

/************************************************************************
* Function: int main(int, char* [])
* Input   : int argc - number of input parameters
			char *arg[] - index.
* Procedure: Main function accepts the 1 parameter - index.
			 1. Check if size of index ( 1 <= index <= 6).
			 2. Initialise tromino board.
			 3. Perform tromino tiling.
			 4. Print Tromino Board.
************************************************************************/
int main(int argc, char *arg[]){
	printf("\t-------Tromino Tiling Problem------- \n\n");
	if(argc != 2){
		fprintf(stderr, "Error while accpeting input character\n");
	}else{
		int index = atoi(arg[1]);
		if(index < 1){
			fprintf(stderr, "Power is less than 1\n");
		}else if(index > 6){
			fprintf(stderr, "Power is greater than 6");
		}else {
			Hole *hole = create_tromino_tile(index);
			tromino_tile(board, 0, 0, index, hole->x_coordinate, hole->y_coordinate);
			printf("\t-------- After Tiling --------- \n\n");
			print_tile(board,get_power(index));
		}
	}
	return 0;
}
