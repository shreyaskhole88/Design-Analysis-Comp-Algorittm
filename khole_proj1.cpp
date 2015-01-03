/********************************************************************
*  Author: Shreyas Khole.
*  Course: CS 575 Spring 14.
*  Date: 02/18/2014
*  Purpose: To learn the use of several sorting techniques such as
*				Selection Sort
*				Counting Sort
*				Merge Sort 
*				Randomized Quick Sort
*			and compute their instruction counts.
*
********************************************************************/
#include <stdio.h>
#include <stdlib.h>     												 /* srand, rand */
#include <time.h>       												 /* time */

#define MAX 1000														 // Maximum number of inputs.
#define COUNTING_RANGE 100												 // Range for counting sort.
#define INPUT_RANGE 20													 // Input Range.

void counting_sort(int[], int, int);
void merge_partition(int[], int);
void selection_sort(int[], int);
void quick_sort(int[], int, int);

bool star;														 		 // Global varibale flag for printing stars.

/************************************************************************
* Function: void display_star(int[], int)
* Input   : int array[] : Input array
			int n : size of array
* Output  : None
* Procedure: This function is used to print the stars for size of each
			 element of an array. 
************************************************************************/
void display_star(int a[], int n){
	for(int j = 0; j < n; j ++){
		for(int i = 0; i < a[j]; i++){
			printf("*");
		}
		printf("\n");
	}
	printf("-------------------------------------\n");
}

/************************************************************************
* Function: void display_counting_star(int[], int)
* Input   : int array[] : Input array
			int n : size of array
* Output  : None
* Procedure: This function is used to print the stars for size of each
			 element of an array. 
************************************************************************/
void display_counting_star(int a[], int n){
	for(int j = 0; j < n; j ++){
		int flag = false;
		for(int i = 0; i < j; i++){
			if(a[j] > 0){
				printf("*");
				flag = true;
			}
		}
		if(flag)
			printf("\n");
	}
	printf("-------------------------------------\n");
}

/************************************************************************
* Function: void print_array(int[], int)
* Input   : int array[] : Input array
			int size : size of array
* Output  : None
* Procedure: This function is used to print the elements of an array. 
************************************************************************/
void print_array(int array[], int size){
	int i = 0;
	for(i = 0; i < size; i++){
		printf("%d\t", array[i]);
	}
	printf("\n");
}

/************************************************************************
* Function: bool generate_random_number(int[], int, int)
* Input   : int array[] : Input array
			int size : size of array
			int sorting_method : sorthing technique selected by user
* Output  : int* array[]
* Procedure: This function is used to generate the random number and
			 store it in input array. 
************************************************************************/
int* generate_random_number(int array[],int size, int sort_method){
	/* Intializing the psuedo random generator. */
	srand(time(NULL));  
	if(sort_method == 2){												 // Condition to check for Counting Sort.
		printf("Inside genrate random number: couting sort\n");
		for(int i = 0; i < size; i++){
			array[i] = rand() % COUNTING_RANGE;							 // Generating random number and storing it to array[i].
		}
		if(size <= 20){
			star = true;
		}
	}else{
		if(size <= INPUT_RANGE){							 	 		 // Condition to check for input size < 20.
			star = true;
			for(int i = 0; i < size; i++){
				array[i] = rand() % 16;									 // Generating random number and storing it to array[i].
			}
		}else{
			for(int i = 0; i < size; i++){
				array[i] = rand();										 // Generating random number and storing it to array[i].
			}
		}
	}
	return array;
}

/************************************************************************
* Function: bool validate_input_size(int)
* Input   : int n : size of array
* Output  : bool error
* Procedure: This function is used to validate the size of input data
			 enter by the user. If size is NOT within the range of
			 1 to 1000, it returns false by printing error message.
************************************************************************/
bool validate_input_size(int n){
	bool error = false;
	if(n < 1 || n > MAX){												 // condition to check size of input data.
		printf("Number of input data is not within specified range.\n");
		error = true;
	}
	return error;
}

/************************************************************************
* Function: void get_input_size()
* Input   : None
* Output  : int size
* Procedure: This function is used to accept the number of input data
			 within range of 1 to 1000 and return the size valibale.
************************************************************************/
int get_input_size(){
	int size;
	printf("Please select the number of input data between 1 and 1000:");
	scanf("%d", &size);
	return size;
}

/************************************************************************
* Function: int main()
* Input   : None
* Output  : None
* Procedure: This is the main function of program. This function accepts
			 sorting method from user. This function uses the switch case
			 to select the appropraite sorting techniques depending on 
			 user input.
************************************************************************/
int main(){
	int sort_method;
	bool error_flag;
	while(1){
		int input_data_size;
		int input_data[MAX];
		star = false;
		printf("\t\t\t******Menu******\t\t\t\n");
		printf("\t\t\t1: Randomized Quick Sort\t\t\t\n");
		printf("\t\t\t2: Counting Sort\t\t\t\n");
		printf("\t\t\t3: Merge Sort\t\t\t\n");
		printf("\t\t\t4: Selection Sort\t\t\t\n");
		printf("\t\t\t5: Exit\t\t\t\n");
		printf("\n");
		printf("\t\t\tSelect Sorting Algorithm:");
		scanf("%d", &sort_method);
		printf("\n");
		switch(sort_method){
			case 1: 
				printf("-----You have selected Randomized Quick Sort-----\n");
				input_data_size = get_input_size();
				error_flag = validate_input_size(input_data_size);
				if(error_flag){
					break;
				}
				generate_random_number(input_data, input_data_size, sort_method);
				printf("----------Unsorted Array----------\n");
				print_array(input_data, input_data_size);
				printf("\n");
				quick_sort(input_data, 0, input_data_size - 1);
				printf("----------Sorted Array----------\n");
				print_array(input_data, input_data_size);
				printf("\n");
				break;
			case 2:
				printf("-----You have selected Counting Sort-----\n");
				input_data_size = get_input_size();
				error_flag = validate_input_size(input_data_size);
				if(error_flag){
					break;
				}
				generate_random_number(input_data, input_data_size, sort_method);
				printf("----------Unsorted Array----------\n");
				print_array(input_data, input_data_size);
				printf("\n");
				counting_sort(input_data, input_data_size, COUNTING_RANGE);
				printf("----------Sorted Array----------\n");
				print_array(input_data, input_data_size);
				printf("\n");
				break;
			case 3:
				printf("-----You have selected Merge Sort-----\n");
				input_data_size = get_input_size();
				error_flag = validate_input_size(input_data_size);
				if(error_flag){
					break;
				}
				generate_random_number(input_data, input_data_size, sort_method);
				printf("----------Unsorted Array----------\n");
				print_array(input_data, input_data_size);
				printf("\n");
				merge_partition(input_data, input_data_size);
				printf("----------Sorted Array----------\n");
				print_array(input_data, input_data_size);
				printf("\n");
				break;
			case 4:
				printf("-----You have selected Selection Sort-----\n");
				input_data_size = get_input_size();
				error_flag = validate_input_size(input_data_size);
				if(error_flag){
					break;
				}
				generate_random_number(input_data, input_data_size, sort_method);
				printf("----------Unsorted Array----------\n");
				print_array(input_data, input_data_size);
				printf("\n");
				selection_sort(input_data, input_data_size);
				printf("----------Sorted Array----------\n");
				print_array(input_data, input_data_size);
				printf("\n");
				break;
			case 5:
				exit(0);
			default:
				printf("\nYou have selected wrong option. Please select correct option from above. \n");
				break;
		}	
	
	}
	return 0;
}

/************************************************************************
* Function: int quick_partition()
* Input   : int array[] : Input array[]
			int left_count : left position of an array
			int right_count : right postion of an array
* Output  : None
* Procedure: This function is used to partition the array. It selects the
			 pivot value randomly. The pivot value is used for splitting 
			 the list. It will find the split point and at the same 
			 time moves other items to the appropriate side of the list. 
************************************************************************/
int quick_partition(int array[],int left_count, int right_count){
	int left_mark = 0;
	int right_mark = 0;
	int pivot_index = left_count + rand() % (right_count - left_count + 1);	 // Select pivot index randomly.
	
	// Swapping element of pivot_index with left_count.
	int temp = array[left_count];
	array[left_count] = array[pivot_index];
	array[pivot_index] = temp;

 	int pivot_value = array[left_count];									 // Selecting new spilt value.
 	left_mark = left_count + 1;
 	right_mark = right_count;
 	bool flag = false;
 	while(!flag){
 		while( array[left_mark] <= pivot_value ) 
   			left_mark++;
		while( array[right_mark] > pivot_value ) 
   			right_mark--;
   			if(right_mark < left_mark){
   				flag = true;
   			}else{
   				temp = array[left_mark];
 				array[left_mark] = array[right_mark];
 				array[right_mark] = temp;
   			}
 	}
 	array[left_count] = array[right_mark];
 	array[right_mark] = pivot_value;
 	return right_mark;
}

/************************************************************************
* Function: int quick_sort()
* Input   : int array[] : Input array[]
			int start : start pointer of array
			int end : end pointer of array
* Output  : None
* Procedure: This function is used to sort the input array using
			 Randomized Quick Sort Algorithm. This algorithm uses the
			 divide and conquer technique to sort the array. The pivot
			 value will be used to divid the list in subsequent calls to
			 quick sort. This function uses recursive calls.
************************************************************************/
void quick_sort( int array[], int start, int end ){
	int pivot = 0;														 // Split Point.
	if ( start < end ){
		pivot = quick_partition( array, start, end );					 // Getting pivot position
		quick_sort( array, start, pivot-1 );							 // Recursive call
		quick_sort( array, pivot+1, end );								 // Recursive call
	}
	if(star){
		display_star(array, end + 1);
	}
}

/************************************************************************
* Function: int counting_sort()
* Input   : int array[] : Input array[]
			int size : size of array
			int scale: specifies range of input elements
* Output  : None
* Procedure: This function is used to sort the input array using
			 Counting Sort Algorithm. This algorithm maintains the
			 count of number of keys in temp[] variable.
************************************************************************/
void counting_sort(int array[], int size, int scale){
	int temp[scale];
	for(int i = 0; i < scale; i++){                     				 // Creating auxillary array.
		temp[i] = 0;
	}
	for(int j = 0; j < size; j++ ){
		temp[array[j]] = temp[array[j]] + 1;							 // Increasing the count at temp[] element.
	}
	int count = 0;
	for(int j =0; j < scale; j++){
		while(temp[j] > 0){
			array[count] = j;											 // restoring to array.
			temp[j] = temp[j] - 1;
			count++;
		}
	}
}

/************************************************************************
* Function: int merge_sort()
* Input   : int left_array[] : left partition of array
			int right_array[] : right partition of array
			int array[]
			int left_count: size of left array[]
			int right_count: size of right_array[]
			int count : size of array
* Output  : None
* Procedure: This function is used to sort the input array using
			 Merge Sort Algorithm. This function is used to merge the
			 left partitioned and right partitioned array by cmparing
			 the elements of each.
************************************************************************/
void merge_sort(int left_array[], int right_array[], int array[], int left_count, int right_count, int count){
	int i = 0;
	int j = 0;
	int k = 0;
	while(i < left_count && j < right_count ){
		if(left_array[i] < right_array[j]){
			array[k] = left_array[i];									 // Copying element of left_array[i] at array[k].
			i++;
		}else{
			array[k] = right_array[j];									 // Copying element of right_array[i] at array[k].
			j++;
		}
		k++;
	}
	while(i < left_count){												 // Copying remaining elements from left_array[].
		array[k] = left_array[i];
		i++;
		k++;
	}
	while(j < right_count){												 // Copying remaining elements from right_array[].
		array[k] = right_array[j];
		j++;
		k++;
	}
	if(star){															 // Printing stars for sorted array. 
		display_star(array, count);
	}
}


/************************************************************************
* Function: int merge_partition()
* Input   : int array[] : Input array[]
			int size : size of array
* Output  : None
* Procedure: This function is used to sort the input array using
			 Merge Sort Algorithm. This function divides the input array
			 recursively until the size of array becomes 1. It call the
			 merge_sort() function to merge the small arrays in 
			 sorting order.
************************************************************************/
void merge_partition(int array[], int size){
	int count = size;
	if(count < 2){														 // Condition of checking size of array.
		return;
	}
	int mid = count/2;													 // Calculating the mid of an array.
	int left_array[mid];												 // Declaring left_array subarray of size mid.
	int right_array[count - mid];										 // Declaring right_array subarray of size count -mid.
	for(int i = 0; i < mid; i++){
		left_array[i] = array[i];										 // Copying elements from array[] to left_array[].
	}
	for(int j = mid; j < count; j++){
		right_array[j - mid] = array[j];								 // Copying elements from array[] to right_array[].
	}
	merge_partition(left_array, mid);									 // Recursive call left_array[].y
	merge_partition(right_array, count - mid);							 // Recursive call for right_array[].
	merge_sort(left_array, right_array, array, mid, count - mid, count); // Merging left and right array into array.
}

/************************************************************************
* Function: int selection_sort()
* Input   : int array[] : Input array[]
			int size : size of array
* Output  : None
* Procedure: This function is used to sort the input array using
			 Selection Sort Algorithm. This algorithm looks for the 
			 smallest element, and after completing the pass, it places 
			 to proper location.
************************************************************************/
void selection_sort(int array[], int size){
	int fill_slot;
	int location;
	int min_position;                                                  // position of smallest element in an array
	for(fill_slot = 0; fill_slot < size - 1; fill_slot++){
		min_position = fill_slot;
		for(int location = fill_slot + 1; location < size; location++){
			if(array[location] < array[min_position]){
				min_position = location;								 // Udating minimum location.
			}
		}
		// Swapping
		int temp = array[fill_slot];
		array[fill_slot] = array[min_position];
		array[min_position] = temp;
		if(star){
			display_star(array, size);
		}
	}
}
