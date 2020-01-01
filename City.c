//Gal Shashua 315878397
//Melany Cygiel Gdud 324442243

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "City.h"
#include "General.h"
#include "Kindergarten.h"
#include "List.h"

void readCity(City* pCity, int textMode)
{
	if (pCity->pGardenList != NULL)
	{
		releaseCity(pCity);
		pCity->count = 0;
	}
	pCity->pGardenList = readAllGardensFromFile(DATA_FILE_TXT, DATA_FILE_BIN, &pCity->count, textMode);
	if (pCity->pGardenList == NULL)
		printf("Error reading city information\n");
}

void showCityGardens(City* pCity)
{
	showAllGardens(pCity->pGardenList, pCity->count);
}

void showSpecificGardenInCity(City* pCity)
{
	showGardenMenu(pCity->pGardenList, pCity->count);
}

void saveCity(City* pCity, int textMode)
{
	writeGardensToFile(pCity->pGardenList, pCity->count, DATA_FILE_TXT, DATA_FILE_BIN, textMode);
}

void cityAddGarden(City* pCity)
{
	pCity->pGardenList = addGarden(pCity->pGardenList, &pCity->count);
	if (pCity->pGardenList == NULL) //Allocation error
		printf("Error adding kindergarten\n");
}

void addChildToSpecificGardenInCity(City* pCity)
{
	addChildToGarden(pCity->pGardenList, pCity->count);
}

void birthdayToChild(City* pCity)
{
	handleBirthdayToChild(pCity->pGardenList, pCity->count);
}

int countChova(City* pCity)
{
	int i;
	int count = 0;
	for (i = 0; i < pCity->count; i++)
	{
		if (pCity->pGardenList[i]->type == Chova)
			count += pCity->pGardenList[i]->childCount;
	}
	return count;
}

void releaseCity(City* pCity)
{
	release(pCity->pGardenList, pCity->count);
}

void sortByName(City* pCity)
{
	insertionSort(pCity->pGardenList, sizeof(Garden*), pCity->count, compereByName);
}

void sortByType(City* pCity)
{
	insertionSort(pCity->pGardenList, sizeof(Garden*), pCity->count, compareByType);
}

void sortById(City* pCity)
{
	Garden* g;
	int i;
	int index = 0;
	g = getGardenAskForName(pCity->pGardenList, pCity->count);
	if (g == NULL) {
		printf("no such Kindergarten\n");
		return;
	}
	for (i = 0; i < pCity->count; i++)
	{
		if (g->name == pCity->pGardenList[i]->name)
			index = i;
	}
	insertionSort(pCity->pGardenList[index]->childPtrArr, sizeof(Child*),
			pCity->pGardenList[index]->childCount, compareByIdChild);
}

void kindergartensLinkedList(City* pCity)
{
	int KinderType;
	LIST* list;
	KinderType = getTypeOption();
	list = createLinkedListForKindergartenType(pCity, KinderType);
	if (list != NULL)
	{
		displayKindergartensFromList(list);
		freeList(list);
		free(list);
	}
}

LIST* createLinkedListForKindergartenType(City* pCity, int KinderType)
{
	int i;
	LIST temp;
	LIST* list;
	NODE* pNode;
	initList(&temp);
	pNode = &temp.head;
	for (i = 0; i < pCity->count; i++)
	{
		if (pCity->pGardenList[i]->type == KinderType)
			pNode = insertList(pNode, pCity->pGardenList[i]);
	}
	list = (LIST*) malloc(sizeof(temp));
	if (!checkAllocation(list))
		return NULL;
	memcpy(list, &temp, sizeof(temp));
	return list;
}

void displayKindergartensFromList(LIST* list)
{
	printList(list,showGardenList);
}
