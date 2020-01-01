#ifndef __PROTOTYPE__
#define __PROTOTYPE__

typedef enum
{
	EXIT,
	READ_CITY,
	SHOW_CITY,
	SHOW_GARDEN,
	WRITE_CITY,
	ADD_GARDEN,
	ADD_CHILD,
	CHILD_BIRTHDAY,
	COUNT_GRADUATE,
	SORT_BY_NAME,
	SORT_BY_TYPE,
	SORT_BY_ID,
	LINKED_LIST,
	NofOptions
} MenuOptions;


int		menu();
char*	getStrExactLength(char* inpStr);
int		checkAllocation(const void* p);
void 	insertionSort(void* arr,int size,int count, int(*comperator)(const void* s1, const void* s2));




#endif
