//201935096 ¿Ãº≠∫Û

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NUM 1000	//define up to 1000 inputs under problem conditions
#define MAX_WEIGHT 10000	//define up to 10000 weight can be entered under problem conditions
#define MAX_IQ 10000	//define up to 10000 iq can be entered under problem conditions

struct elephant {	//define a new variable structure
	int weight;		//elephant contains weight, iq, and order
	int iq;
	int order;
};

typedef struct elephant Elephant;	//to write a struct elephant simply as an Elephant
typedef Elephant* ElephantPtr;	//to write a struct elephant * simply as an ElephantPtr

//function name : countLine
//description : count how many objects are in the file you entered
//input : pointer of the entered file
//output : number of lines
int countLine(FILE * fp) {
	int count = 0;	//count the number of lines
	char temp[20];	//save the input temporarily
	while (fgets(temp, sizeof(temp), fp) != NULL) {	//use while to get input until the end of file
		count++;	//receive input line by line and count line
	}
	rewind(fp);	//initialize the file pointer because the input needs to be retrieved from the file again
	return count;	//return the number of lines as the main function
}

//function name : changeValue
//description : used to change the order to satisfy the condition
//input : pointer with object you want to change and two index to replace
//output : none
void changeValue(ElephantPtr e, int index, int i) {
	int temp1, temp2, temp3;	//store values for a while to change values

	temp1 = (e + index)->order;	//reordering
	(e + index)->order = (e + i)->order;
	(e + i)->order = temp1;

	temp2 = (e + index)->iq;	//change iq
	(e + index)->iq = (e + i)->iq;
	(e + i)->iq = temp2;

	temp3 = (e + index)->weight;	//change weight
	(e + index)->weight = (e + i)->weight;
	(e + i)->weight = temp3;
}

//function name : print
//description : number of conditions met, and order printed according to conditions
//input : pointer of the list to print and the number of objects that meet the conditions
//output : none
void print(int* list, int count) {
	printf("%d\n", count);	//output the number of conditions
							//that satisfy the conditions in the first line for the problem
	for (int i = 0; i < count; i++) {
		printf("%d\n", list[i]);	//outputs the order of satisfying the condition
	}
}

//function name : sortWeight
//description : list the order according to the weight of the elephant
//input : pointer of an elephant entered and the total number of elephants
//output : none
void sortWeight(ElephantPtr e, int l) {
	int min = 0, idx = 0;
	for (int i = 0; i < l - 1; i++) {
		min = (e + i)->weight;	//insert first value in min to compare the values
		idx = i;	//equally insert i into index

		for (int j = i + 1; j < l; j++) {	//i + 1 to its length turn for statement
			if ((e + j)->weight < min) {
				//compare the weight and min value of the order and fine when the weights is smaller
				min = (e + j)->weight;	//if smaller, change min and i values to corresponding values
				idx = j;
			}
		}
		changeValue(e, idx, i);	//change the actual value by invoking changValue
	}
}

//function name : compareIQ
//description : //comparing the IQ of an elephant
//input : pointer of an elephant entered and the total number of elephants
//output : none
void compareIQ(ElephantPtr e, int len) {
	int count = 0, iq = 0;
	int* list = (int*)malloc(sizeof(int) * len);	//allocate space according to length through malloc
	for (int i = 0; i < len; i++) {	//spin for statement from 0 to length to compare iq
		if (i == 0) {	//if i is 0, it is the first input value
			list[count] = (e + i)->order;	//enter the order in the 0th of the list because it is the first time if i is 0
			iq = (e + i)->iq;	//save for comparing iq in the following order
			count++;	//increase by 1 as value is added
			continue;
		}
		if (iq < (e + i)->iq) {	//run when the corresponding iq is greater than the stored iq
			if (count < 2) {	//run if less than 2 counts
				count = 0;	//the corresponding iq is larger, so change the count to 0 and then insert
				list[count] = (e + i)->order;
				iq = (e + i)->iq;
				count++;	//increase by 1 as value is added
			}
		}
		else {
			list[count] = (e + i)->order;
			iq = (e + i)->iq;
			count++;	//increase by 1 as value is added
		}
	}
	print(list, count);	//invoke print function to output the valus in the list that satisfy the conditions
}

//function name : readFile
//description : read the weight and iq of the elephant from the entered file and stored in the structure
//input : elephant pointer to save, pointer to read file
//output : none
void readFile(ElephantPtr e, FILE* fp) {
	char input[20];	//store the values entered from the file
	int num = 0;	//to move by the number of entered
	int temp;	//keep it for a while before you add a value
	while (fgets(input, sizeof(input), fp) != NULL) {	//use while to get input until the end of file
		temp = atoi(strtok(input, " "));	//cut to where spacing appears and change to int
		(e + num)->weight = temp;	//assign a changed value to that weight
		if ((e + num)->weight > MAX_WEIGHT) {	//determing if the MAX WEIGHT is exceeded according to the conditions
			printf("The elephant is too heavy!\n");
			exit(0);	//terminating the program
		}
		temp = atoi(strtok(NULL, " "));	//cut to where spacing appears and change to int
		(e + num)->iq = temp;	//assign a changed value to that IQ
		if ((e + num)->iq > MAX_IQ) {	//determing if the MAX IQ is exceeded according to the conditions
			printf("The elephant is too smart!\n");
			exit(0);	//terminating the program
		}
		(e + num)->order = num + 1;	//assign the number of entries to the order
		num++;	//move to next
	}
}

int main(void) {
	FILE* fp = fopen("input.txt", "r");	//open the file in read mode from input.txt
	if (fp == NULL) {	//if fp is NULL, the file could not be opened, so if clause is executed
		printf("File could not be opened!\n");	//print file is not open
		return -1;	//terminating the program
	}

	int length = countLine(fp);	//find length through countLine function
	if (length > MAX_NUM) {	//ensure that the total number does not exceed MAX NUM 
							//according to the conditions of the problem
		printf("Put too many object!\n");
		return -1;	//terminating the program
	}

	ElephantPtr e = (ElephantPtr)malloc(sizeof(Elephant) * length);
	//allocate spave according to length to e through malloc

	readFile(e, fp);		//invoke readFile function to enter values from file
	sortWeight(e, length);	//arrange in order of weight to find that the conditions are met
	compareIQ(e, length);	//call compareIQ to find the iq that satisfieds the conditions

	fclose(fp);	//closes input.txt
	free(e);	//free the space allocated as malloc
	return 0;	//terminating the program
}