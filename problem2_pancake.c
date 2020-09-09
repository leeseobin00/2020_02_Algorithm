//201935096 ¿Ãº≠∫Û 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_COUNT 30	//designate the number of receiveables as 30
#define MAX_LENGTH 120	//specify the length of the string to be input as 120
#define SWAP(a,b) {int t; t=a; a=b; b=t;}		//define to simplify SWAP

int count = 0, flip_count = 0, s = 0, e = MAX_COUNT;
int flip_locate[MAX_COUNT];	//to store where the flip occurs

//function name : printArr
//description : print n elements in a specific array
//input : array to print, number of elements to be displayed
//output : none
void printArr(int arr[], int n) {
	for (int i = 0; i < n; ++i)
		printf("%2d ", arr[i]);	//print array elements from 0 to n
	printf("\n");
}

//function name : flip
//description : the order of pancakes is reversed according to the conditions,
//				At this time, the flipped place is also stored in the flip_locate array
//input : array to reverse, the number at which the change begins
//output : none
void flip(int arr[], int i) {
	int start = 0, temp = i, boolean = 0;

	while (start < i) {
		for (int j = i; j >= 0; j--) {
			if (arr[j] != arr[i]) {
				boolean = -1;
			}
			else boolean = 1;
		}
		if ((temp == i) && (boolean == -1)) {
			//in this case, the same number is repeated, so no exchange is required
			flip_locate[flip_count++] = count - i;
		}
		SWAP(arr[i], arr[start]);	//change the order through SWAP while moving
		i--;
		start++;
	}
}

//function name : pancakeSort
//description : fine the location where the flip should occur 
//				and flip the pancake using the flip function
//input : array to reverse, number of arrays to check
//output : none
void pancakeSort(int arr[], int current) {
	if (indexOfMax(arr, current) != e) {
		//if max is not at the end, it should be moved to the front
		flip(arr, indexOfMax(arr, current));
		flip(arr, current - 1);
	}
	if (current == 2) {
		//if current is 2, only 2 elements remain, so the flip ends
		flip_locate[flip_count++] = 0;
		//at the end of flip_locate array, put 0 in the flip locate array
		return;
	}
	else {
		//use pancakeSort to proceed to the next flip
		e--;
		pancakeSort(arr, current - 1);
	}
}

//function name : Max
//description : find the largest value in the size of the array from start
//input : array to want to find max value, start point, size of array, maximum value of array
//output : max value of an array  
int Max(int arr[], int start, int size, int m) {
	if (size == start)
		return m;
	if (m >= arr[size - 1])
		return Max(arr, start, size - 1, m);
	return Max(arr, start, size - 1, arr[size - 1]);
}

//function name : indexOfMax
//description : find the index of the largest value of an array
//input : array you want to fine max value's index
//output : index of max value
int indexOfMax(int arr[], int n) {
	int mi, i;
	int m = Max(arr, 0, n, 0);

	for (i = n - 1; i >= 0; --i)
		if (arr[i] == m) {
			return i;
		}
}

int main(void) {
	int arr[MAX_COUNT];		//save diameters input from user
	int num = 0, i;

	printf("\nEnter the number of pancake (1 ~ 30) : ");
	//received the number of pancakes from the user
	scanf_s("%d", &count);

	if ((count < 1) || (count > 30)) {
		//if the pancakes is less than 1 or greater than 30, the following text is printed
		puts("Too many or too few pancakes!");
	}
	else {
		printf("\nEnter the diameter of pancake (1 ~ 10) : ");
		//received the diameters of pancakes from the user
		for (int i = 0; i < count; i++) {
			scanf_s("%d", &arr[i]);
			if ((arr[i] < 1) || (arr[i] > 10)) {
				puts("Pancakes are too big or too small!");
				//if the pancake's diameter is less than 1 or greater than 10, the following text is printed
				return;
			}
		}
	}
	e = count - 1;

	puts("\nbefore fliping : ");
	printArr(arr, count);	//print arr before flip
	puts("after fliping : ");
	pancakeSort(arr, count);
	printArr(arr, count);	//print arr after flip

	printf("\noutput>> ");
	printArr(flip_locate, flip_count);
	//outputs an array containing the poosition where the flip occured
	printf("\n");
}