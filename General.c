#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "General.h"

const char* optionStr[NofOptions] = { "Exit", "Read City information from file",
		"Show all Kindergartens", "Show a specific Kindergarten",
		"Save City information to file", "Add a Kindergarten", "Add a Child",
		"Birthday to a Child", "Count Hova childres",
		"Sort Kindergartens by name",
		"Sort Kindergartens by type and children numbers",
		"Sort children in a Kindergarten", "Kindergartens in Linked list" };

/**************************************************/
int menu()
/**************************************************/
/**************************************************/
{
	int option, i;
	printf("\n==========================");
	printf("\nSelect:\n");
	for (i = 0; i < NofOptions; i++)
		printf("\n\t%d. %s.", i, optionStr[i]);
	printf("\n");
	scanf("%d", &option);
	return option;
}

char* getStrExactLength(char* inpStr)
{
	char* theStr = NULL;
	size_t len;
	len = strlen(inpStr) + 1;
	//allocate a place for the string in the right location in the array 
	theStr = (char*) malloc(len * sizeof(char));
	//Copy the string to the right location in the array 
	if (theStr != NULL)
		strcpy(theStr, inpStr);
	return theStr;
}

int checkAllocation(const void* p)
{
	if (!p)
	{
		printf("ERROR! Not enough memory!");
		return 0;
	}
	return 1;
}

void insertionSort(void* arr, int typeSize, int count, int (*comperator)(const void* s1, const void* s2))
{
	int i, j;
	void* key = NULL;
	key = (char*) malloc(typeSize * sizeof(char));
	for (i = 1; i < count; i++) {
		memcpy(key, (char*) arr + i * typeSize, typeSize);

		for (j = i - 1; j >= 0 && comperator((char*) arr + j * typeSize, key) > 0; j--) {
			memcpy((char*) arr + (j + 1) * typeSize, (char*) arr + j * typeSize, typeSize);
		}
		memcpy((char*) arr + (j + 1) * typeSize, key, typeSize);
	}
	free(key);
}
