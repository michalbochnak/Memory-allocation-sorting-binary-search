/*
Programming Project 1
Author: Michal Bochnak
Professor: Patrick Troy
Class: CS 211 - Programming Practicum
UIC, Spring 2017
*/
//-----------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>


//-----------------------------------------------------------------------------
// display values stored in the user array, used for debugging puprposes
void DisplayValues(int *userValues, int numOfValues) {
	int i = 0;		// loop counter

					// loop thru array and display the elements
	for (i = 0; i < numOfValues; i++) {
		printf("%d ", userValues[i]);
	}
	printf("\n");	// new line for output formatting
}


//-----------------------------------------------------------------------------
// Makes the copy of the user values
void ArrayCopy(int *userValues, int *copyOfUserValues, int numOfValues) {
	int i = 0;		// loop counter

					// copy userValues into new array
	for (i = 0; i < numOfValues; i++) {
		copyOfUserValues[i] = userValues[i];
	}
}


//-----------------------------------------------------------------------------
// Selection sort
void SelectionSort(int *userValues, int numOfValues) {
	int i = 0;			// outer loop counter
	int j = 0;			// inner loop counter
	int minIndex = 0;	// stores index of minimum value during selection sort
	int temp = 0;		// copy for swapping

	for (i = 0; i < numOfValues; i++) {
		minIndex = i;	// assign current i for minIndex
		for (j = i + 1; j < numOfValues; j++) {
			if (userValues[j] < userValues[minIndex]) {
				minIndex = j;	// new minIndex found, assign to minIndex
			}
		}
		// swap the values
		temp = userValues[i];
		userValues[i] = userValues[minIndex];
		userValues[minIndex] = temp;
	}
}	// SelectionSort


	//-----------------------------------------------------------------------------
	// Linear search 
int LinearSearch(int *userValues, int numOfValues,
	int searchedValue, int *numComparisons) {
	int index = 0;				// position in the array / loop counter

								// iterate thru the array until searchedValue is found
	for (index = 0; index < numOfValues; index++) {
		*numComparisons += 1;	// update numComparisons
		if (userValues[index] == searchedValue) {
			return index;		// found, return index
		}
	}
	return -1;					// not found, return -1
}


//-----------------------------------------------------------------------------
// Binary Search
int BinarySearch(int *userValues, int numOfValues,
	int searchedValue, int *numComparisons) {
	int low = 0;			// low bound
	int high = numOfValues;	// high bound
	int middle = 0;			// middle point

							// while loop breaks down the array into halves, until the desired value is found
	while (low <= high) {
		*numComparisons += 1;	// update numComparisons
		middle = low + ((high - low) / 2);
		if (userValues[middle] == searchedValue) {
			return middle;		// found, return index
		}
		else if (searchedValue < userValues[middle]) {
			high = middle - 1;	// determine new high bound
		}
		else {
			low = middle + 1;	// determine new low bound
		}
	}
	return -1;		// not found
}	// BinarySearch


	//-----------------------------------------------------------------------------
	// Doubles the array size
int *GrowArray(int *userValues, int *size) {
	int *temp;			// temp copy of the array
	int i = 0;			// loop counter

						// allocate doubled memory space for new array
	temp = (int *)malloc(*size * 2 * sizeof(int));

	// copy the array to the temp array
	for (i = 0; i < *size; i++) {
		temp[i] = userValues[i];
	}
	free(userValues);	// free the memory
	*size = *size * 2;	// update the size variable
	return temp;		// return new, bigger array
}


//-----------------------------------------------------------------------------
int main() {
	int *userValues;			// stores unsorted values entered by user
	int *sortedUserValues;		// stores sorted values entered by user
	int *searchedValues;		// stores values to search for
	int val = 0;				// stores read in value
	int sizeUserArray = 50;		// size of the array of user values
	int sizeSearchArray = 50;	// size of the array storing searched values
	int numOfValuesInArray = 0;	// stores number of values read in
	int numOfValuesToSearch = 0;// stores number of values to search for
	int numComparisons = 0;		// num of comparisons for actual serach
	int foundAtIndex = 0;		// index at which value was found
	int i = 0;					// loop counter


								// initial allocation of memory for user values
	userValues = (int *)malloc(sizeUserArray * sizeof(int));

	printf("Enter integer values terminated by value of -999: ");
	scanf("%d", &val);			// read in first user value

	while (val != -999) {
		userValues[numOfValuesInArray] = val;
		numOfValuesInArray++;
		// grow the array if actual size was reached
		if (numOfValuesInArray == sizeUserArray) {
			userValues = GrowArray(userValues, &sizeUserArray);
		}
		scanf("%d", &val);
	}

	// allocate memory for copy of userValues, make copy of userValues
	sortedUserValues = (int *)malloc(sizeUserArray * sizeof(int));
	ArrayCopy(userValues, sortedUserValues, numOfValuesInArray);

	// sort the array using SortedUserValues
	SelectionSort(sortedUserValues, numOfValuesInArray);

	// allocate memory for searchedUserValue
	searchedValues = (int *)malloc(sizeSearchArray * sizeof(int));

	// read in values to serach for
	printf("Enter values to search for terminated by -999: ");
	scanf("%d", &val);			// read in first value to search for

	while (val != -999) {
		searchedValues[numOfValuesToSearch] = val;
		numOfValuesToSearch++;
		// grow the array if actual size was reached
		if (numOfValuesToSearch == sizeSearchArray) {
			searchedValues = GrowArray(searchedValues, &sizeSearchArray);
		}
		scanf("%d", &val);
	}

	// sort array witj values to search for,
	// so search results will be displayed in order
	SelectionSort(searchedValues, numOfValuesToSearch);

	printf("\n\n      * * * R E S U L T S * * *\n\n");

	// search for entered values and print out resulting information
	for (i = 0; i < numOfValuesToSearch; i++) {
		//	linear search in unsorted array
		foundAtIndex = LinearSearch(userValues, numOfValuesInArray,
			searchedValues[i], &numComparisons);
		printf("*** Searching for: %d ***\n", searchedValues[i]);
		printf("Linear Search: ");
		if (foundAtIndex == -1) {
			printf("Not found. ");
		}
		else {
			printf("Found.     ");
		}
		printf("Number of comparisons: %d. ", numComparisons);
		if (foundAtIndex != -1) {
			printf("Value was found at index %d.", foundAtIndex);
		}
		printf("\n");

		// binary search in sorted array
		numComparisons = 0;			// reset numOfComparisons to 0
		foundAtIndex = BinarySearch(sortedUserValues, numOfValuesInArray,
			searchedValues[i], &numComparisons);
		printf("Binary Search: ");
		if (foundAtIndex == -1) {
			printf("Not found. ");
		}
		else {
			printf("Found.     ");
		}
		printf("Number of comparisons: %d. ", numComparisons);
		if (foundAtIndex != -1) {
			printf("Value was found at index %d.", foundAtIndex);
		}
		printf("\n\n");
		numComparisons = 0;			// reset numOfComparisons to 0
	}	// for

		// free allocated memory
	free(userValues);
	free(sortedUserValues);
	free(searchedValues);

	return 0;
}	// main