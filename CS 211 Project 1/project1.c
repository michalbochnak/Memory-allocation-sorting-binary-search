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
// display values stored in int array
void DisplayValues(int *userValues, int numOfValues) {
	int i = 0;		// loop counter

	for (i = 0; i < numOfValues; i++) {
		printf("%d ", userValues[i]);
	}
	printf("\n");	// new line for output formatting
}


//-----------------------------------------------------------------------------
// make the copy of the user values
void ArrayCopy(int *userValues, int *copyOfUserValues, int numOfValues) {
	int i = 0;		// loop counter

	// copy user values into new array
	for (i = 0; i < numOfValues; i++) {
		copyOfUserValues[i] = userValues[i];
	}
}


//-----------------------------------------------------------------------------
// Selection sort
void SelectionSort(int *userValues, int numOfValues) {
	int i = 0;
	int j = 0;
	int minIndex = 0;	// stores index of minimum value during selection sort
	int temp = 0;		// copy for swapping

	for (i = 0; i < numOfValues; i++) {
		minIndex = i;	// assign current i for minIndex
		for (j = i + 1; j < numOfValues; j++) {
			if (userValues[j] < userValues[minIndex]) {
				minIndex = j;	// new minIndex found
			}
		}
		// swap the values
		temp = userValues[i];
		userValues[i] = userValues[minIndex];
		userValues[minIndex] = temp;
	}
}	// SelectionSort


//-----------------------------------------------------------------------------
// linear search 
int LinearSearch(int *userValues, int numOfValues,
	int searchedValue, int *numComparisons) {
	int index = 0;		// position in the array / loop counter

	for (index = 0; index < numOfValues; index++) {
		*numComparisons += 1;	// update numComparisons
		if (userValues[index] == searchedValue) {
			return index;
		}
	}
	return -1;		// not found
}


//-----------------------------------------------------------------------------
// Binary Search
int BinarySearch(int *userValues, int numOfValues,
	int searchedValue, int *numComparisons) {
	int low = 0;
	int high = numOfValues; 
	int middle = 0;

	while (low <= high) {
		*numComparisons += 1;	// update numComparisons
		middle = low + ((high - low) / 2);
		if (userValues[middle] == searchedValue) {
			return middle;	// found, return index
		}
		else if (searchedValue < userValues[middle]) {
			high = middle - 1;	// determine new high bound
		}
		else {
			low = middle + 1;	// determine low bound
		}
	}
	return -1;		// not found
}	// BinarySearch


//-----------------------------------------------------------------------------
// Double the array size
int *GrowArray(int *userValues, int *size) {
	int *temp;			// temp copy of the array
	int i = 0;			// loop counter
	// allocate doubled memory space for new array
	temp = (int *)malloc(*size * 2 * sizeof(int));
	// copy the array to the temp array
	for (i = 0; i < *size; i++) {		
		temp[i] = userValues[i];
	}
	free(userValues);
	*size = *size * 2;	// update the size variable
	return temp;		// return new, bigger array
}


//-----------------------------------------------------------------------------
int main() {
	int *userValues;
	int *sortedUserValues = NULL;
	int val = 0;				// stores read in value
	int sizeUserArray = 100;		// size of the array
	int sizeSearchArray = 100;		// size of the array
	int index = 0;				// index of actual element in array - needed? --------------
	int numOfValuesInArray = 0;	// stores number of values read in
	int numOfValuesToSearch = 0;// stores number of values to search for
	int *searchedValues;		// stores values to search for
	int numComparisons = 0;		
	int numComparisonsLin = 0;	// needed? -------------------------------------------------
	int numComparisonsBin = 0;	// needed? -------------------------------------------------
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


	// display userValues
	printf("\nuserValues: ");
	DisplayValues(userValues, numOfValuesInArray);

	// allocate memory for copy of userValues, make copy of userValues
	sortedUserValues = (int *)malloc(sizeUserArray * sizeof(int));
	ArrayCopy(userValues, sortedUserValues, numOfValuesInArray);
	
//	// display sortedUserValues
//	printf("CopyOfuserValues: ");
//	DisplayValues(sortedUserValues, numOfValuesInArray);
	
	// sort the array with SortedUserValues
	SelectionSort(sortedUserValues, numOfValuesInArray);
	// display sorted values
	printf("\nSorted: ");
	DisplayValues(sortedUserValues, numOfValuesInArray);

	// read in values to serach for
	printf("Enter values to search for: ");
//	scanf("%d", &searchedValue);
//	foundAtIndex = LinearSearch(userValues, numOfValues, searchedValue, &numComparisonsLin);

	
	// allocate memory for searchedUserValue
	searchedValues = (int *)malloc(sizeSearchArray * sizeof(int));
	scanf("%d", &val);			// read in first value to search for

	while (val != -999) {
		searchedValues[numOfValuesToSearch] = val;
		numOfValuesToSearch++;
//		DisplayValues(userValues, numOfValuesToSearch);
		// grow the array if actual size was reached
		if (numOfValuesToSearch == sizeSearchArray) {
			searchedValues = GrowArray(searchedValues, &sizeSearchArray);
		}
		scanf("%d", &val);
	}

	// search for entered values and print out resulting information
	for (i = 0; i < numOfValuesToSearch; i++) {
		//	linear search in unsorted array
		foundAtIndex = LinearSearch(userValues, numOfValuesInArray,
									searchedValues[i], &numComparisons);
		printf("*** Searching for: %d ***\n", searchedValues[i]);
		printf("Linear Search Results: ");
		if (foundAtIndex == -1) {
			printf("Not found. ");
		}
		else {
			printf("Found. ");
		}
		printf("Number of comparisons: %d. ", numComparisons);
		if (foundAtIndex != -1) {
			printf("Value was found at index %d.", foundAtIndex);
		}
		printf("\n");

		numComparisons = 0;			// reset numOfComparisons to 0
		//	binary search in sorted array
		foundAtIndex = BinarySearch(sortedUserValues, numOfValuesInArray,
			searchedValues[i], &numComparisons);
		printf("Binary Search Results: ");
		if (foundAtIndex == -1) {
			printf("Not found. ");
		}
		else {
			printf("Found. ");
		}
		printf("Number of comparisons: %d. ", numComparisons);
		if (foundAtIndex != -1) {
			printf("Value was found at index %d.", foundAtIndex);
		}
		printf("\n");
		numComparisons = 0;			// reset numOfComparisons to 0
	}	// for


	
	
//	BinarySearch(userValues, numOfValues, searchedValue, &numComparisonsBin);

//	printf("Number of comparisons for linear search: %d\n", numComparisonsLin);
//	printf("Number of comparisons for binary search: %d\n", numComparisonsBin);

	return 0;
}	// main
