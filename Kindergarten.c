#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "Kindergarten.h"
#include "Child.h"
#include "General.h"

const char* GardenTypeName[NofTypes] = { "Chova", "Trom Chova", "Trom Trom Chova" };

//**************************************************
// Read data off all Kindergartens from file
//**************************************************
Garden** readAllGardensFromFile(char* fileNameTXT, char* fileNameBIN, int* pGardenCount, int textMode)
{
	int count, i;
	FILE *fp;
	Garden** gardens;
	*pGardenCount = 0;
	if (textMode == 0) //read from binary file
	{
		fp = fopen(fileNameBIN, "rb");
		fread(&count, sizeof(int), 1, fp);
	} else //read from text file
	{
		fp = fopen(fileNameTXT, "r");
		fscanf(fp, "%d", &count);
	}
	//Would like to do the allocation even if count ==0
	//so will not return NULL as error
	gardens = (Garden**) malloc(count * sizeof(Garden*));
	if (!checkAllocation(gardens))
		return NULL;
	for (i = 0; i < count; i++) {
		gardens[i] = (Garden*) malloc(sizeof(Garden));
		if (!checkAllocation(gardens[i]))
			return NULL;
		readGarden(fp, gardens[i], textMode);
	}
	fclose(fp);
	*pGardenCount = count;
	return gardens;
}

/**************************************************/
//         Read a Kindergarten from a file
/**************************************************/

void readGarden(FILE* fp, Garden* pGarden, int textMode)
{
	int StringLen;
	int i, type;
	char sTemp[100];
	unsigned char byte;

	if (textMode == 0) //read from binary file
	{
		fread(&StringLen, sizeof(int), 1, fp);	//length of garden name
		for (i = 0; i < StringLen; ++i)
		fread(&sTemp[i], sizeof(char), 1, fp);
		fread(&byte, sizeof(unsigned char), 1, fp);	//type
		pGarden->type = byte & 0x3;
		pGarden->childCount = byte >> 2;
		byte = pGarden->type | (pGarden->childCount << 6);
		pGarden->type = (GardenType) pGarden->type;
	} else
	{
		fscanf(fp, "%s", sTemp);
		fscanf(fp, "%d", &type);
		fscanf(fp, "%d", &pGarden->childCount);
		pGarden->type = (GardenType) type;
	}
	//Garden name
	pGarden->name = getStrExactLength(sTemp);
	//Child count
	if (pGarden->childCount == 0)
	{
		pGarden->childPtrArr = NULL;
		return;
	}
	pGarden->childPtrArr = (Child**) malloc(pGarden->childCount * sizeof(Child*));
	if (!checkAllocation(pGarden->childPtrArr))
		return;
	//Read each child
	for (i = 0; i < pGarden->childCount; i++)
	{
		pGarden->childPtrArr[i] = (Child*) malloc(sizeof(Child));
		if (!checkAllocation(pGarden->childPtrArr[i]))
			return;
		readChild(fp, pGarden->childPtrArr[i], textMode);
	}
}

/**************************************************/
/*            show all Kindergartens		      */
/**************************************************/
void showAllGardens(Garden** pGardenList, int count)
{
	int i, j = 0;
	printf("There are %d kindergarten in the city\n", count);
	for (i = 0; i < count; i++)
	{
		printf("\nKindergarten %d:\n", i + 1);
		showGarden(pGardenList[i]);
		printf("\n");
	}
	printf("\n");
	if (count > LINKED_NUM_CHECK) {
		variadicFunction(pGardenList[j]->name, pGardenList[j]->childCount,
				pGardenList[j + 1]->name, pGardenList[j + 1]->childCount,
				pGardenList[j + 2]->name, pGardenList[j + 2]->childCount, NULL);
	}
}

/**************************************************/
/*            show a Kindergarten		           */
/**************************************************/
void showGarden(const Garden* pGarden)
{
	int i;
	// Kindergarten name
	printf("Name:%s", pGarden->name);
	printf("\tType:%s", GardenTypeName[pGarden->type]);
	printf("\t%d Children:", pGarden->childCount);
	//all Children
	for (i = 0; i < pGarden->childCount; i++)
		showChild(pGarden->childPtrArr[i]);
}

void showGardenList(const void* p)
{
	const Garden* pGarden = (Garden*)p;
	showGarden(pGarden);
}

/**************************************************/
/*  write Kindergartens to a file					   */

/**************************************************/

void writeGardensToFile(Garden** pGardenList, int gardenCount, char* fileNameTXT, char* fileNameBIN, int textMode) {
	int i;
	FILE *fp;
	if (textMode == 0)
	{
		if ((fp = fopen(fileNameBIN, "wb")) == NULL) {
			printf("Cannot Open File '%s'", fileNameBIN);
			return;
		}
		fwrite(&gardenCount, sizeof(int), 1, fp);
	} else
	{
		if ((fp = fopen(fileNameTXT, "wt")) == NULL)
		{
			printf("Cannot Open File '%s'", fileNameTXT);
			return;
		}
		fprintf(fp, "%d\n", gardenCount);
	}
	for (i = 0; i < gardenCount; i++)
		writeGarden(fp, pGardenList[i], textMode);

	fclose(fp);
}

/**************************************************/
/*Write a Kindergarten to the open file						*/
/**************************************************/
void writeGarden(FILE* fp, const Garden* pGarden, int textMode)
{
	int i;
	unsigned char byte;
	int nameLength = 0;
	if (textMode == 0)
	{
		nameLength = strlen(pGarden->name) + 1; //get name length +1 for \0
		fwrite(&nameLength, sizeof(int), 1, fp);
		for (i = 0; i < nameLength; i++) //write the name
			fwrite(&pGarden->name[i], sizeof(char), 1, fp);
		byte = (pGarden->childCount & 0x3F) << 2 | (pGarden->type & 0x3);
		fwrite(&byte, sizeof(unsigned char), 1, fp);
	} else
	{
		//Kindergarten Name
		fprintf(fp, "%s", pGarden->name);
		fprintf(fp, "  %d", pGarden->type);
		//Children
		fprintf(fp, " %d\n", pGarden->childCount);
	}
	for (i = 0; i < pGarden->childCount; i++)
		writeChild(fp, pGarden->childPtrArr[i], textMode);
}

//*************************************************
// menu option to add Child to a Kindergarten
//*************************************************
void addChildToGarden(Garden** pGardenList, int gardenCount)
{
	Garden* pGarden;
	if (pGardenList == NULL)
	{
		printf("There are no Kindergartens yet\n");
		return;
	}
	pGarden = getGardenAskForName(pGardenList, gardenCount);
	if (pGarden == NULL)
	{
		printf("no such Kindergarten\n");
		return;
	}
	pGarden->childPtrArr = (Child**) realloc(pGarden->childPtrArr,(pGarden->childCount + 1) * sizeof(Child*));
	if (!checkAllocation(pGarden->childPtrArr))
	{
		pGarden->childCount = 0;
		return;
	}
	pGarden->childPtrArr[pGarden->childCount] = (Child*) malloc(sizeof(Child));
	getChildCheckIdFromUser(pGarden->childPtrArr[pGarden->childCount], pGarden);
	pGarden->childCount++;
}

/**************************************************/
/* Add a Kindergarten  - we need to allocate more space   */
/* in the list.									*/
/**************************************************/
Garden** addGarden(Garden** pGardenList, int* pGardenCount)
{
	pGardenList = (Garden**) realloc(pGardenList,
			(*pGardenCount + 1) * sizeof(Garden*));
	if (!checkAllocation(pGardenList))
	{
		*pGardenCount = 0;
		return NULL;
	}
	Garden* temp = (Garden*) malloc(sizeof(Garden));
	getGardenFromUser(temp, pGardenList, *pGardenCount);
	pGardenList[*pGardenCount] = temp;
	(*pGardenCount)++;
	return pGardenList;

}

void showGardenMenu(Garden** pGardenList, int count)
{
	Garden* pGarden;
	pGarden = getGardenAskForName(pGardenList, count);
	if (pGarden != NULL)
		showGarden(pGarden);
	else
		printf("No such Kindergarten\n");
}

Garden* getGardenAskForName(Garden** pGardenList, int count)
{
	char sTemp[100];
	Garden* pGarden;

	//Kindergarten name
	puts("\nGive me the Kindergarten Name:\t");
	scanf("%s", sTemp);
	getchar(); //remove \n

	//In this exe the find will not be efficient
	pGarden = findGardenByName(pGardenList, count, sTemp);

	return pGarden;
}

Garden* findGardenByName(Garden** pGardenList, int count, const char* name)
{
	//linear search
	int i;
	for (i = 0; i < count; i++)
	{
		if (strcmp(pGardenList[i]->name, name) == 0)
			return pGardenList[i];
	}
	return NULL;
}

Child* getChildAskForId(Garden* pGarden)
{
	int id;
	int index;
	printf("Enter child id\n");
	scanf("%d", &id);
	//The search will be inefficient - so sort
	index = findChildById(pGarden->childPtrArr, pGarden->childCount, id);
	if (index == -1)
		return NULL;
	return pGarden->childPtrArr[index];
}

void getGardenFromUser(Garden* pGarden, Garden** pGardenList, int count)
{
	int i;
	char sTemp[100];
	int bOK = 0;
	int countC;

	do
	{
		//Kindergarten name
		puts("\nName:\t");
		scanf("%s", sTemp);
		getchar(); //remove second word if exsist
		if (findGardenByName(pGardenList, count, sTemp) != NULL)
			printf("This Kindergarten already in list\n");
		else
			bOK = 1;
	} while (!bOK);

	pGarden->name = getStrExactLength(sTemp);

	pGarden->type = getTypeOption();

	//Children
	puts("\nEnter children Details:\t");

	puts("\nChildren count:");
	scanf("%d", &countC);
	if (countC == 0) {
		pGarden->childCount = 0;
		pGarden->childPtrArr = NULL;
		return;
	}

	//create the list of children in the correct size
	pGarden->childPtrArr = (Child**) malloc(countC * sizeof(Child*));
	if (!checkAllocation(pGarden->childPtrArr)) {
		pGarden->childPtrArr = NULL;
		return;
	}

	pGarden->childCount = 0;
	for (i = 0; i < countC; i++) {
		pGarden->childPtrArr[i] = (Child*) malloc(sizeof(Child));
		getChildCheckIdFromUser(pGarden->childPtrArr[i], pGarden);
		pGarden->childCount++;
	}

}

/**************************************************/
/* Init a child from use. Ask for Id, check it is */
/* new and after call the function to ask for all other */
/* information										*/
/**************************************************/
void getChildCheckIdFromUser(Child* pChild, const Garden* pGarden)
{
	int id, bOK = 0;
	do {
		puts("\nID No.:\t");
		scanf("%d", &id);
		if (findChildById(pGarden->childPtrArr, pGarden->childCount, id) != -1)
			printf("This child is in the Kindergarten\n");
		else
			bOK = 1;
	} while (!bOK);

	getChildFromUser(pChild, id);
}

void handleBirthdayToChild(Garden** pGardenList, int count) {
	Garden* pGarden;
	Child* pChild;

	pGarden = getGardenAskForName(pGardenList, count);
	if (pGarden == NULL) {
		printf("No such Kindergarten\n");
		return;
	}

	pChild = getChildAskForId(pGarden);
	if (pChild == NULL) {
		printf("No such child\n");
		return;
	}
	birthday(pChild);
}

GardenType getTypeOption()
{
	int i, type;
	printf("Garden type:\n");
	do {
		for (i = 0; i < NofTypes; i++)
			printf("Enter %d for %s\n", i, GardenTypeName[i]);
		scanf("%d", &type);
	} while (type < 0 || type >= NofTypes);
	return (GardenType) type;
}

// release the Children list
//release the name ptr of each Kindergarten
//release the Kindergarten list
void release(Garden** pGardenList, int count)
{
	int i;
	for (i = 0; i < count; i++)
	{
		free(pGardenList[i]->childPtrArr);
		free(pGardenList[i]->name);
		free(pGardenList[i]);
	}
	free(pGardenList);

}

int compereByName(const void* name1, const void* name2)
{
	const Garden* n1 = *(Garden**) name1;
	const Garden* n2 = *(Garden**) name2;
	return (strcmp(n1->name, n2->name));
}

int compareByType(const void* type1, const void* type2)
{
	int ret;
	const Garden* t1 = *(Garden**) type1;
	const Garden* t2 = *(Garden**) type2;
	ret = t1->type - t2->type;
	if (ret == 0)
	{
		if (t1->childCount > t2->childCount)
			ret = 1;
	    else if (t1->childCount < t2->childCount)
			ret = -1;
	}
	return ret;
}

void variadicFunction(char* str, int val, ...)
{
	va_list list;
	va_start(list, val);
	while (str != NULL)
	{
		printf("\n %s", str);
		printf("----> %d", val);
		str = va_arg(list, char*);
		val = va_arg(list, int);
	}
	va_end(list);
}
