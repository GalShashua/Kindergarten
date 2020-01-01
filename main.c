
#include <stdio.h>
#include <stdlib.h>
#include "General.h"
#include "Kindergarten.h"
#include "Child.h"
#include "City.h"

int main(int argc, char* argv[])
{
	City utz = { NULL, 0 };
	int uReq;

	//first time read
	readCity(&utz, atoi(argv[1]));
	do
	{
		uReq = menu();
		switch (uReq)
		{
		case READ_CITY:
			readCity(&utz, atoi(argv[1]));
			break;

		case SHOW_CITY:
			showCityGardens(&utz);
			break;

		case SHOW_GARDEN:
			showSpecificGardenInCity(&utz);
			break;

		case WRITE_CITY:
			saveCity(&utz, atoi(argv[1]));
			break;

		case ADD_GARDEN:
			cityAddGarden(&utz);
			break;

		case ADD_CHILD:
			addChildToSpecificGardenInCity(&utz);
			break;

		case CHILD_BIRTHDAY:
			birthdayToChild(&utz);
			break;

		case COUNT_GRADUATE:
			printf("There are %d children going to school next year\n",
					countChova(&utz));
			break;

		case SORT_BY_NAME:
			sortByName(&utz);
			break;

		case SORT_BY_TYPE:
			sortByType(&utz);
			break;

		case SORT_BY_ID:
			sortById(&utz);
			break;

		case LINKED_LIST:
			 kindergartensLinkedList(&utz);
			break;
		}
	} while (uReq != EXIT);

	releaseCity(&utz); //free all allocations

	return EXIT_SUCCESS;
}
