//201935096 ¿Ãº≠∫Û

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JOB 1000	//set the number of job to max according to the conditions 
#define MAX_FINE 10000	//set the payable fine to max according to the conditions

struct dress {	//declares a new variable structure
	int day;	//save how long day takes
	int fine;	//store total fine
	float daily_fine;	//obtain the daily fine from the day and fine entered
	int order;	//save the order entered, used to print the order
};

typedef struct dress Dress;

//function name: judgePositive
//description: determine if the value entered is positive
//input: entered value
//output: none
void judgePositive(int test) {
	if (test <= 0) {
		printf("The input begins with a single positive integer!\n");
		exit(0);	//end the program becaues it does not meet the condition
	}
}

//function name: compare
//description: compare the size of two values
//input: value of 2 data
//output: value that determines whether it is large or small
int compare(const void *A, const void *B) {
	Dress *ptrA = (Dress *)A;
	Dress *ptrB = (Dress *)B;

	if (ptrA->daily_fine <= ptrB->daily_fine)
		return 1;
	else if (ptrA->daily_fine > ptrB->daily_fine)
		return -1;
}

//function name: printOutput
//description: print result according to the conditions of the problem
//input: send an D to print out the value and see how many values you need to print
//output: none
void printOutput(Dress D[MAX_JOB], int n) {
	printf("\noutput>\n");
	for (int j = 0; j < n; j++) {
		printf("%d ", D[j].order + 1);
	}
	printf("\n\n");
}

int main(void) {
	int test = 0, job = 0;
	struct dress D[MAX_JOB];

	scanf("%d", &test);		//user entered how many test will take place
	judgePositive(test);	//determine if the value entered is positive
	printf("\n");

	for (int i = 0; i < test; i++) {	//rotating a repeating statement to run as much as test
		scanf("%d", &job);	//user entered how many jobs to do
		if ((job > MAX_JOB) || (job < 1)) {	//ensure number of jobs is within range
			printf("The number of jobs must be between 1 and 1,000!\n");
			exit(0);	//end the program becaues it does not meet the condition
		}

		for (int j = 0; j < job; j++) {
			//execute repeating statement because enter the amount of time and fines that takes as many days
			scanf("%d %d", &D[j].day, &D[j].fine);	//enter and store job and fine from the user
			if ((D[j].fine > MAX_FINE) || (D[j].fine < 1)) {	//ensure fine is within range
				printf("The payable fine must be entered between 1 and 10,000!\n");
				exit(0);	//end the program becaues it does not meet the condition
			}
			D[j].daily_fine = (float)D[j].fine / D[j].day;	//get daily fine from day and fine
			D[j].order = j;	//save the number of entries
		}

		qsort(D, job, sizeof(Dress), compare);	//change the order to suit the conditions
		printOutput(D, job);	//output results
	}
	return 0;	//end the program
}