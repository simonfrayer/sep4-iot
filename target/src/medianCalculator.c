#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "./include/medianCalculator.h"


// compare method for the quicksort
static int medianCalculator_compare(const void *a, const void *b)
{
    return (*(int16_t *)a - *(int16_t *)b);
}

// so this is O(n log n)
// it could be liner with the use of a heap
int16_t medianCalculator_calculateMedian(int16_t arr[], int size)
{
    	//printf("Getting median\n");

	// make a copy of co2s
	int16_t arrayCopy[10] = {-404, -404, -404, -404, -404, -404, -404, -404, -404, -404};

	memcpy(arrayCopy, arr, 10 * sizeof(int16_t));

	// sort the array
	qsort(arrayCopy, 10, sizeof(int16_t), medianCalculator_compare);

	// print the sorted array
	for (int i = 0; i < 10; i++)
	{
		printf("%d, ", arrayCopy[i]);
	}
	printf("\n");

	// calculate the amount of elements that are outside of the range
	// they represent some sort of error / initial value
	int amountOfErrors = 0;
	for (int i = 0; i < 10; i++)
	{
		if (arrayCopy[i] < -400)
		{
			amountOfErrors++;
		}
	}

	//printf("Amount of errors: %d\n", amountOfErrors);

	// get the median
	if (amountOfErrors == 10)
	{
		// if all the elements are errors
		// return the initial value
		return -666;
	}

	// if odd number of errors
	// return the middle element
	if (amountOfErrors % 2 == 1)
	{
		return arrayCopy[(10 + amountOfErrors - 1) / 2];
	}

	// if even number of errors
	// return the average of the two middle elements
	//printf("The two middle elements are: %d and %d\n", arrayCopy[(10 + amountOfErrors) / 2 - 1], arrayCopy[(10 + amountOfErrors) / 2]);
	return (arrayCopy[(10 + amountOfErrors) / 2 - 1] + arrayCopy[(10 + amountOfErrors) / 2]) / 2;
}