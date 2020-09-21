//201935096 ¿Ãº≠∫Û

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW 10		//define a miximum Row value of 10 for the condition of the problem
#define MAX_COLUMN 100	//define a miximum Column value of 100 for the condition of the problem

struct table {	//create a structure to hold the table's information
	int value;	//save entered values
	int dp;		//save the smallest added value through the path
	int pre;	//save the row value of the last value to find out which path you followed
};

//function name: checkRange
//description: ensure that the entered value is within a given range
//input: the row value and column value of the table
//output: none
void checkRange(int r, int c) {
	if ((r < 1) || (r > MAX_ROW)) {	//set the range to match the conditions given to the problem
		printf("The value of row is too small or too large!\n");
		exit(0);	//exit the program
	}
	if ((c < 1) || (c > MAX_COLUMN)) {	//set the range to match the conditions given to the problem
		printf("The value of column is too small or too large!\n");
		exit(0);	//exit the program
	}
}

//function name: fineMin
//description: obtain the smallest value that comes in addition to the previous value and store it in dp
//input: information in table, the row value and column value of the table
//output: none
void findMin(struct table t[MAX_ROW][MAX_COLUMN], int row, int col) {
	int temp[3];	//find the smallest value in addition
	int min;	//to find the minimum value
	for (int a = 1; a < col; a++) {	
		for (int b = 0; b < row; b++) {
			temp[0] = t[b][a].value + t[(b + row - 1) % row][a - 1].dp;
			temp[1] = t[b][a].value + t[b][a - 1].dp;
			temp[2] = t[b][a].value + t[(b + row + 1) % row][a - 1].dp;
			min = temp[0];
			for (int i = 0; i < 3; i++) {
				if (min > temp[i]) {
					min = temp[i];
				}
			}
			if (min == temp[0]) //if statement used to store which row is in pre
				t[b][a].pre = (b + row - 1) % row;
			else if (min == temp[1])
				t[b][a].pre = b;
			else if (min == temp[2])
				t[b][a].pre = (b + row + 1) % row;
			t[b][a].dp = min;
		}
	}
}

//function name: printOutput
//description: output the value of the array and the value of the smallest path as a result of the acquisition
//input: the array and col and the minimal value of the path as a result of the calculation
//output: none
void printOutput(int resultArr[MAX_COLUMN], int col, int min) {
	printf("\nOutput>\n");
	for (int i = 0; i < col; i++) {
		printf("%d ", resultArr[i]);
	}
	printf("\n%d\n\n", min);
}


int main(void) {
	int row, col, min, min_row;	
	int resultArr[MAX_COLUMN] = { 0 };
	struct table T[MAX_ROW][MAX_COLUMN];

	scanf_s("%d %d", &row, &col);	//entered row and column value from user
	checkRange(row, col);	//check if the value is in range

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			scanf_s("%d", &T[i][j].value);	//enter value for each table via double for statement
		}
	}

	for (int i = 0; i < row; i++) {
		T[i][0].dp = T[i][0].value;	//enter each value in the 0th column in dp
		T[i][0].pre = 0;	//0th column has no value before it, so 0 is put in pre
	}

	findMin(T, row, col);	//find the minimum value for each dp
	min_row = 0;	//used to obtain the row value of the smallest of the last dp values
	min = T[0][col - 1].dp;	//used to obtain the smallest of the last dp values
	for (int i = 1; i < row; i++) {
		if (min > T[i][col - 1].dp) {
			min_row = i;
			min = T[i][col - 1].dp;
		}
	}

	for (int i = col - 1; i >= 0; i--) {	//reverse tracking of which route it came from
		resultArr[i] = T[min_row][i].value;	//store the value of the path passed it resultArr
		min_row = T[min_row][i].pre;	//track by changing the row calue of the preceding one back to min_row
	}

	printOutput(resultArr, col, min);	//output result value
	return 0;	//exit the program
}