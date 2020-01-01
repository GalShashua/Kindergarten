#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Child.h"
#include "General.h"


/**************************************************/
/*             Read a Child from a file           */
/**************************************************/
void readChild(FILE* fp, Child* pChild, int textMode)
{
	unsigned char byte1;
	unsigned char byte2;
	if (textMode == 0)
	{
		fread(&byte1, sizeof(unsigned char), 1, fp);
		fread(&byte2, sizeof(unsigned char), 1, fp);
		pChild->age = (byte2 >> 5) & 0x1F;
		pChild->id = byte1 | (byte2 & 0x1F) << 8;
	} else
	{
		//Child ID
		fscanf(fp, "%d", &pChild->id);
		fscanf(fp, "%d", &pChild->age);
	}
}


/**************************************************/
/*            show a Child				           */
/**************************************************/
void showChild(const Child* pChild)
{
	printf("\nID:%d  ", pChild->id);
	printf("Age:%d  ", pChild->age);
}


/**************************************************/
void getChildFromUser(Child* pChild, int id)
/**************************************************/
/**************************************************/
{
	pChild->id = id;
	puts("\nAge:\t");
	scanf("%d", &pChild->age);
}


/**************************************************/
/*Write a Child to the open file				*/
/**************************************************/
void 	writeChild(FILE* fp,const Child* pChild,int textMode)
{
	if(textMode == 0)
	{
		unsigned char byte1;
		unsigned char byte2;
		byte1 = pChild->id & 0xFF;
		fwrite(&byte1, sizeof(char), 1, fp);
		byte2 = (pChild->age << 5) | ((pChild->id >> 8) & 0x1F);
		fwrite(&byte2, sizeof(char), 1, fp);
	}
	else
	fprintf(fp,"%d %d\n",pChild->id, pChild->age);
}

int	findChildById(Child** pChildList, int count, int id)
{
	Child** found = NULL;
	Child temp = {id};
	Child* pointer = &temp;
	qsort(pChildList, count, sizeof(Child*), compareByIdChild);
	found = (Child**)bsearch(&pointer, pChildList, count, sizeof(Child*), compareByIdChild);
	if(found == NULL)
		return -1;
	else
		return found - pChildList;
}

void birthday(Child* pChild)
{
	pChild->age++;
}

//void	releaseChild(Child* pChild)
//{
//	//nothing to release
//}


int compareByIdChild(const void* num1, const void* num2)
{
	Child* n1 = *(Child**)num1;
	Child* n2 = *(Child**)num2;
	return n1->id-n2->id;
}
