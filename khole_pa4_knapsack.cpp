/********************************************************************
*  Author: Shreyas Khole.
*  Course: CS 575.
*  Date: 04/23/2014
*  Purpose: To implement the Knapsack Algorithm using Greedy Method.
*  Knapsack Problem: Select items according maximum profit and
					 that does not exceed the Knapsack Capacity and 
					 maximizes the benefit.
*
********************************************************************/

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Minimum number of items */
#define MIN_ITEM 4

/* Precision for flaot comparison */
#define PRECISION 0.01

/* Structure for holding knapsack item details. */
struct knapsack_item{
	int profit;
	int weight;
	bool selected;
	int item_number;
	float profit_per_unit;
};

/************************************************************************
* Function: void allocate_memory(int **, int, int)
* Input   : char **matrix : matrix.
			int row : number of rows of matrix
			int col : number of columns of matrix
* Output  : None
* Procedure: This function is used to allocate a memory to the matrix 
			 dynamically using calloc() function.
			 
************************************************************************/
int** allocate_memory(int row, int column){
	int **matrix;
	matrix = (int **)calloc(row, sizeof(int *));
	if(matrix == NULL){
		fprintf(stderr,"Error while allocating memory to matrix !!!");
		exit(0);
	}
	for(int i = 0; i < row; i++){
		matrix[i] = (int *)calloc(column, sizeof(int));
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
* Function: void print_knapsack(struct knapsack_item *, int, bool)
* Input   : struct knapsack_item *items : array of knapsack_item struct.
			int n : Number of items in knsapsack
			bool flag: Flag is used for printing the selected knapsack items.
* Output  : None
* Procedure: This function is used to print the knapsack items 
			 depending on flag. If flag is true, selected items are printed
			 else all items are printed.
************************************************************************/
void print_knapsack(struct knapsack_item *item, int n, bool flag){
	printf("-------------------------------------------------\n");
	printf("ITEM\t PROFIT\t WEIGHT\t PROFIT PER UNIT\n");
	printf("-------------------------------------------------\n");
	if(flag){
		int total_profit = 0;
		int total_weight = 0;
		for(int i = 0; i < n; i++){
			if((item + i)->selected){
				total_profit = total_profit + (item + i)->profit;
				total_weight = total_weight + (item + i)->weight;
				printf("%d\t %d\t %d\t %.2f\n", (item + i)->item_number, (item + i)->profit, (item + i)->weight, (item + i)->profit_per_unit);
			}
		}
		printf("\n\n");
		printf("Total Profit is %d \t Total Weight is %d\n", total_profit, total_weight);
	} else{
		for(int i = 0; i < n; i++){
			printf("%d\t %d\t %d\t %.2f\n", (item + i)->item_number, (item + i)->profit, (item + i)->weight, (item + i)->profit_per_unit);
		}
	}
}

/************************************************************************
* Function: void generate_item_list(struct knapsack_item *, int)
* Input   : struct knapsack_item *items : array of knapsack_item struct.
			int n : Number of items in knsapsack
* Output  : return knapsack capacity calculated by floor(total_weight * 0.6)
* Procedure: This function is used to generate the knapsack items 
			 with their profit and weight and return knapsack capacity.
************************************************************************/
int generate_item_list(struct knapsack_item *item, int n){
	int total_weight = 0;
	for(int i = 0; i < n; i++){
		(item + i)->profit = rand() % 21 + 10;
		(item + i)->weight = rand() % 16 + 5;
		(item + i)->selected = false;
		(item + i)->item_number = i + 1;
		(item + i)->profit_per_unit = (float)(item + i)->profit / (item + i)->weight;
		total_weight = total_weight + (item + i)->weight;
	}
	return (int)(total_weight * 0.6);
}

/************************************************************************
* Function: void deselect_items(struct knapsack_item *, int)
* Input   : struct knapsack_item *items : array of knapsack_item struct.
			int n : Number of items in knsapsack
* Output  : None
* Procedure: This function is used to deselect the items by previous method.
************************************************************************/
void deselect_items(struct knapsack_item *item, int n){
	for(int i = 0; i < n; i++){
		(item + i)->selected = false;
	}
}

/************************************************************************
* Function: void print_max_benefit_matrix(int **, int, int)
* Input   : int **b_matrix : max_benefit matrix
			int row : Number of rows
			int col : Number of columns
* Output  : None
* Procedure: This function is used to print max_benefit matrix.
************************************************************************/
void print_max_benefit_matrix(int **b_matrix, int row, int col){
	printf("\n ------ Max Benefit Matrix ------ \n\n");
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			printf("%d ", b_matrix[i][j]);
		}
		printf("\n");
	}
}

/************************************************************************
* Function: void find_selected_items(int **, struct knapsack_item *, int, bool)
* Input   : int **b_matrix : weight and item matrix
			struct knapsack_item *items : array of knapsack_item struct.
			int n : Number of items in knsapsack
			bool knapsack_capacity : knapsack capacity
* Output  : None
* Procedure: This function is used to print the selected knapsack items. 
			 
************************************************************************/
void find_selected_items(int **b_matrix, struct knapsack_item *item, int n, int knapsack_capacity){
	/* temporary weight*/
	int temp_weight = knapsack_capacity;
	int total_weight = 0;
	printf("\n\n---------------- SELECTED ITEMS -----------------\n");
	printf("ITEM\t PROFIT\t WEIGHT\n");
	printf("-------------------------------------------------\n");
	for(int i = n; i >= 1; i--){
		if(b_matrix[i][temp_weight] != b_matrix[i - 1][temp_weight] && (b_matrix[i][temp_weight] == b_matrix[i - 1][temp_weight - (item + i - 1)->weight] + (item + i - 1)->profit)){
   			printf("%d\t %d\t %d\n", (item + i - 1)->item_number, (item + i - 1)->profit, (item + i - 1)->weight);
   			temp_weight = temp_weight - (item + i - 1)->weight;
   			total_weight = total_weight + (item + i - 1)->weight;
  		}
	}
	int total_profit = b_matrix[n][knapsack_capacity];
	printf("\n\n");
	printf("Total Profit is %d \t Total Weight %d\n", total_profit, total_weight);
}

/************************************************************************
* Function: void brute_force_knapsack(struct knapsack_item *, int, int )
* Input   : struct knapsack_item *items : array of knapsack_item struct.
			int n : Number of items in knsapsack.
			int knapsack_capacity: knapsack_capacity
* Output  : None.
* Procedure: This function is used tosSelect a subset of the items that 
			 does not exceed the Knapsack Capacity and maximizes the benefit.
************************************************************************/
void brute_force_knapsack(knapsack_item *item, int n, int knapsack_capacity){
	/* best profit for each subset */
	int best_profit = 0;
	/* maximum number of subsets */
	int last = (int)pow(2,n);
	/* array of selected items from subset */
	knapsack_item *selected_items;
	/* Selected item number */
	int selected_count = 0;
	for(int i = 1; i < last; i++){
		/* total weight of subset */
		int total_weight = 0;
		/* total profit of subset*/
		int total_profit = 0;
		/* temporary items generated for subset */
		knapsack_item *temp_items = (knapsack_item *)calloc(n,sizeof(knapsack_item));
		/* temporary count */
		int temp_count = 0;
		int k = 0;
		for(int j = 0; j < n; j++){
			/* Bitwise operations. 
			  Right shifting bits 'i' by 'j' ">>"
			  and multiplying "&" by 1 */
			if (((i >> j) & 1) != 1){
				/* Skipping below statements when above condition is true*/
				continue;				
			}
			total_weight = total_weight + (item + j)->weight;
			total_profit = total_profit + (item + j)->profit;
			/* prinitng items in each subset with their profit and weight */ 
//			printf("item-%d \n", (item + j)->item_number);
			temp_count++;
			temp_items[k] = item[j];
			k++;
		}
//		printf(" Profit --> %d Weight --> %d\n", total_profit, total_weight);
		/* Checking total weight of subset is greater than knapsack capacity */
		if(total_weight <= knapsack_capacity){
			/* checking total profit is greater than previous best profit */
			if(total_profit >= best_profit){
				best_profit = total_profit;
				/* Selected items */
				selected_items = (knapsack_item *)calloc(sizeof(knapsack_item), temp_count);
				/* Number of selected items */
				selected_count = 0;
				for(int i = 0; i < temp_count; i++){
					selected_items[i] = temp_items[i];
					(selected_items + i)->selected = true;
					selected_count++;
				}
				/* freeing temp_items memory */
				free(temp_items);
			}
		}
	}
	printf("-------------- SELECTED ITEMS -----------------\n");
	/* Printing selected elements from knapsack */
	print_knapsack(selected_items, selected_count, true);
	/* Freeing selected items memory */
	free(selected_items);
	/* Deslecting items */
	deselect_items(item, n);
}

/************************************************************************
* Function: void knapsack_dynamic(struct knapsack_item *, int, int )
* Input   : struct knapsack_item *items : array of knapsack_item struct.
			int n : Number of items in knsapsack.
			int knapsack_capacity: knapsack_capacity
* Output  : None.
* Procedure: This function is used to select items using dynamic programming
			 and that does not exceed the Knapsack Capacity and maximizes 
			 the benefit.
************************************************************************/
void knapsack_dynamic(struct knapsack_item *item, int knapsack_capacity, int n){
	/* Allocating memory to max_benefit_matrix */
	int **b_matrix = allocate_memory(n + 1, knapsack_capacity + 1);
	for (int i = 0; i <= n ; i++){
    	for (int j = 0; j <= knapsack_capacity; j++){
        	if (i==0 || j==0)
            	b_matrix[i][j] = 0;
        	else if ((item + i- 1)->weight <= j && b_matrix[i - 1][j - (item + i- 1)->weight] + (item + i - 1)->profit > b_matrix[i - 1][j]){
				b_matrix[i][j] = b_matrix[i - 1][j - (item + i- 1)->weight] + (item + i - 1)->profit;
			} else
            	b_matrix[i][j] = b_matrix[i - 1][j];
       	}
   	}
	print_max_benefit_matrix(b_matrix, n + 1, knapsack_capacity + 1);
	find_selected_items(b_matrix, item, n, knapsack_capacity);
	/* Free memory for b_matrix */
	free_memory(b_matrix, n + 1);
}

/************************************************************************
* Function: void greedy_max_profit_per_unit(struct knapsack_item *, int, int )
* Input   : struct knapsack_item *items : array of knapsack_item struct.
			int n : Number of items in knsapsack.
			int knapsack_capacity: knapsack_capacity
* Output  : None.
* Procedure: This function is used to select items according maximum 
			 profit per unit and that does not exceed the Knapsack 
			 Capacity and maximizes the benefit.
************************************************************************/
void greedy_max_profit_per_unit(struct knapsack_item *item, int knapsack_capacity, int n){
	/* temp_capacity after adding the item in knapsack */
	int temp_capacity = 0;
	/* Sorting the generated knapsack on profit_per_unit. */
	for(int i = 0; i < n - 1; i++){
		for(int j = i + 1; j < n; j++){
			if (((item + i)->profit_per_unit - PRECISION) < (item + j)->profit_per_unit){
		    	struct knapsack_item temp;
				temp = item[i];
				item[i] = item[j];
				item[j] = temp;
		   	}else if((item + i)->profit_per_unit == (item + j)->profit_per_unit){
		   		/* Checking if profit_per_unit is same, then selecting max profit item. */
		    	if((item + i)->profit < (item + j)->profit){
					struct knapsack_item temp;
					temp = item[i];
					item[i] = item[j];
					item[j] = temp;
				}
		   	}
		}
	}
	/* Print sorted knapsack items */
//	print_knapsack(item, n, false);
	for(int i = 0; i < n; i++){
		/* Calculating temp_capacity after adding item to knapsack */
		temp_capacity = temp_capacity + (item + i)->weight;
		/* Checking temp_capacity is less than knapsack_capacity */
		if(temp_capacity <= knapsack_capacity){
			/* Add an item to knapsack */
			(item + i)->selected = true;
		} else {
			/* Not selecting this item .*/
			temp_capacity = temp_capacity - (item + i)->weight;
		}
	}
	printf("\n\n----------- SELECTED ITEMS -------------\n\n");
	/* Printing selected knapsack */
	print_knapsack(item, n, true);
	/* Deslecting items */
	deselect_items(item, n);
}

/************************************************************************
* Function: void greedy_min_weight(struct knapsack_item *, int, int )
* Input   : struct knapsack_item *items : array of knapsack_item struct.
			int n : Number of items in knsapsack.
			int knapsack_capacity: knapsack_capacity
* Output  : None.
* Procedure: This function is used to select items according minimum 
			 weight and that does not exceed the Knapsack 
			 Capacity and maximizes the benefit.
************************************************************************/
void greedy_min_weight(struct knapsack_item *item, int knapsack_capacity, int n){
	/* temp_capacity after adding the item in knapsack */
	int temp_capacity = 0;
	/* Sorting the generated knapsack on minimum weight. */
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if((item + i)->weight > (item + j)->weight){
				struct knapsack_item temp;
				temp = item[i];
				item[i] = item[j];
				item[j] = temp;
			}else if((item + i)->weight == (item + j)->weight){
				/* Checking if weight is same, then selecting max profit item. */
				if((item + i)->profit < (item + j)->profit){
					struct knapsack_item temp;
					temp = item[i];
					item[i] = item[j];
					item[j] = temp;
				}
			}			
		}
	}
	/* Print sorted knapsack items */
//	print_knapsack(item, n, false);
	for(int i = 0; i < n; i++){
		/* Calculating temp_capacity after adding item to knapsack */
		temp_capacity = temp_capacity + (item + i)->weight;
		/* Checking temp_capacity is less than knapsack_capacity */
		if(temp_capacity <= knapsack_capacity){
			/* Add an item to knapsack */
			(item + i)->selected = true;
		} else {
			/* Not selecting this item .*/
			temp_capacity = temp_capacity - (item + i)->weight;
		}
	}
	printf("\n\n----------- SELECTED ITEMS -------------\n");
	/* Printing selected knapsack */
	print_knapsack(item, n, true);
	/* Deslecting items */
	deselect_items(item, n);
}

/************************************************************************
* Function: void greedy_max_weight(struct knapsack_item *, int, int )
* Input   : struct knapsack_item *items : array of knapsack_item struct.
			int n : Number of items in knsapsack.
			int knapsack_capacity: knapsack_capacity
* Output  : None.
* Procedure: This function is used to select items according maximum 
			 weight and that does not exceed the Knapsack 
			 Capacity and maximizes the benefit.
************************************************************************/
void greedy_max_weight(struct knapsack_item *item, int knapsack_capacity, int n){
	/* temp_capacity after adding the item in knapsack */
	int temp_capacity = 0;
	/* Sorting the generated knapsack on minimum weight. */
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if((item + i)->weight < (item + j)->weight){
				struct knapsack_item temp;
				temp = item[i];
				item[i] = item[j];
				item[j] = temp;
			}else if((item + i)->weight == (item + j)->weight){
				/* Checking if weight is same, then selecting max profit item. */
				if((item + i)->profit < (item + j)->profit){
					struct knapsack_item temp;
					temp = item[i];
					item[i] = item[j];
					item[j] = temp;
				}
			}			
		}
	}
	/* Print sorted knapsack items */
//	print_knapsack(item, n, false);
	for(int i = 0; i < n; i++){
		/* Calculating temp_capacity after adding item to knapsack */
		temp_capacity = temp_capacity + (item + i)->weight;
		/* Checking temp_capacity is less than knapsack_capacity */
		if(temp_capacity <= knapsack_capacity){
			/* Add an item to knapsack */
			(item + i)->selected = true;
		} else {
			/* Not selecting this item .*/
			temp_capacity = temp_capacity - (item + i)->weight;
		}
	}
	printf("\n\n----------- SELECTED ITEMS -------------\n");
	/* Printing selected knapsack */
	print_knapsack(item, n, true);
	/* Deslecting items */
	deselect_items(item, n);
}

/************************************************************************
* Function: void greedy_max_profit(struct knapsack_item *, int, int )
* Input   : struct knapsack_item *items : array of knapsack_item struct.
			int n : Number of items in knsapsack.
			int knapsack_capacity: knapsack_capacity
* Output  : None.
* Procedure: This function is used to select items according maximum 
			 profit and that does not exceed the Knapsack 
			 Capacity and maximizes the benefit.
************************************************************************/
void greedy_max_profit(struct knapsack_item *item, int knapsack_capacity, int n){
	/* temp_capacity after adding the item in knapsack */
	int temp_capacity = 0;
	/* Sorting the generated knapsack on minimum weight. */
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if((item + i)->profit < (item + j)->profit){
				struct knapsack_item temp;
				temp = item[i];
				item[i] = item[j];
				item[j] = temp;
			}else if((item + i)->profit == (item + j)->profit){
				/* Checking if weight is same, then selecting max profit item. */
				if((item + i)->weight > (item + j)->weight){
					struct knapsack_item temp;
					temp = item[i];
					item[i] = item[j];
					item[j] = temp;
				}
			}
		}
	}
	/* Print sorted knapsack items */
//	print_knapsack(item, n, false);
	for(int i = 0; i < n; i++){
		/* Calculating temp_capacity after adding item to knapsack */
		temp_capacity = temp_capacity + (item + i)->weight;
		/* Checking temp_capacity is less than knapsack_capacity */
		if(temp_capacity <= knapsack_capacity){
			/* Add an item to knapsack */
			(item + i)->selected = true;
		} else {
			/* Not selecting this item .*/
			temp_capacity = temp_capacity - (item + i)->weight;
		}
	}
	printf("----------- SELECTED ITEMS -------------\n");
	/* Printing selected knapsack */
	print_knapsack(item, n, true);
	/* Deslecting items */
	deselect_items(item, n);
}

/************************************************************************
* Function: int main()
* Input   : None
* Procedure: 1. Calculate number of items randomly.
			 2. Allocate memory to array of struct knapsack_items
			 3. Generate knapsack_items and calculate knapsack capacity.
			 4. Print knapsack items.
			 5. Knapsack algorithm with brute force approach.
			 6. Knapsack algorithm with Dynamic programming.
			 7. Knapsack algorithm with Greedy Max profit with unit.
			 8. Knapsack algorithm with Greedy Max weight.
			 9. Knapsack algorithm with Greedy min weight.
			 10. Knapsack algorithm with Greedy Max profit.
			 11. Free memory.
************************************************************************/
int main(){
	srand(time(NULL));
	printf("#########################################################\n");
	printf("              KNAPSACK ITEM DETAILS                      \n");
	printf("#########################################################\n\n");
	/* Calculate number of items randomly. */
	int number_of_items = rand() % 5 + MIN_ITEM;
	printf("Number of items : %d\n", number_of_items);
	/* Allocating memory to struct pointer */
	struct knapsack_item *item = (knapsack_item*) malloc(sizeof(knapsack_item) * number_of_items);
	/* Generate knapsack_items and calculate knapsack capacity. */
	int knapsack_capacity = generate_item_list(item, number_of_items);
	printf("Capacity of knapsack is %d\n", knapsack_capacity);
	/* Print knapsack items. */
	print_knapsack(item, number_of_items, false);
	printf("\n#########################################################\n");
	printf("          Knapsack With Brute Force Approach             \n");
	printf("#########################################################\n\n");
	/* Knapsack algorithm with brute force. */
	brute_force_knapsack(item, number_of_items, knapsack_capacity);
	printf("\n#########################################################\n");
	printf("           Knapsack With Dynamic Programming              \n");
	printf("#########################################################\n\n");
	/* Knapsack algorithm with dynamic appraoch. */
	knapsack_dynamic(item, knapsack_capacity, number_of_items);
	printf("\n#########################################################\n");
	printf("       Knapsack With Greedy Maximum Profit Per Unit       \n");
	printf("#########################################################\n\n");
	/* Knapsack algorithm with greedy_max_profit_per_unit appraoch. */
	greedy_max_profit_per_unit(item, knapsack_capacity, number_of_items);
	printf("\n#########################################################\n");
	printf("           Knapsack With Greedy Maximum Weight              \n");
	printf("#########################################################\n\n");
	/* Knapsack algorithm with greedy_max_weight appraoch. */
	greedy_max_weight(item, knapsack_capacity, number_of_items);
	printf("\n#########################################################\n");
	printf("           Knapsack With Greedy Minimum Weight              \n");
	printf("#########################################################\n\n");
	/* Knapsack algorithm with greedy_max_weight appraoch. */
	greedy_min_weight(item, knapsack_capacity, number_of_items);
	printf("\n#########################################################\n");
	printf("           Knapsack With Greedy Maximum Profit              \n");
	printf("#########################################################\n\n");
	/* Knapsack algorithm with greedy_max_profit_per_unit appraoch. */
	greedy_max_profit(item, knapsack_capacity, number_of_items);
	/* Free memory for item* */
	free(item);
}
