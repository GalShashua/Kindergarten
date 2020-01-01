#ifndef __KINDERGARTEN__
#define __KINDERGARTEN__
#include "Child.h"

#define LINKED_NUM_CHECK 3

typedef enum
{
	Chova,
	TromChova,
	TromTromChova,
	NofTypes
} GardenType;

const char* GardenTypeName[NofTypes];

typedef struct
{
	char* name;
	GardenType  type;
	Child** childPtrArr;
	int		childCount;
}Garden;


Garden**	readAllGardensFromFile(char* fileNameTXT, char* fileNameBIN, int* pGardenCount, int textMode);
void	readGarden(FILE* fp, Garden* pGarden, int readMode);
GardenType	getTypeOption();

void	showAllGardens(Garden** pGardenList, int count);
void	showGarden(const Garden* pGarden);
void showGardenList(const void* p);

void	writeGardensToFile(Garden** pGardenList, int gardenCount, char* fileNameTXT, char* fileNameBIN, int textMode);
void	writeGarden(FILE* fp, const Garden* pGarden, int readMode);

void	addChildToGarden(Garden** pGardenList, int gardenCount);
Garden**	addGarden(Garden** pGardenList, int* pGardenCount);

void	showGardenMenu(Garden** pGardenList, int count);
Garden*	getGardenAskForName(Garden** pGardenList, int count);

Garden*	findGardenByName(Garden** pGardenList, int count,const char* name);

Child*	getChildAskForId(Garden* pGarden);

void	getGardenFromUser(Garden* pGarden, Garden** pGardenList, int count);
void	getChildCheckIdFromUser(Child* pChild,const Garden* pGarden);

void	handleBirthdayToChild(Garden** pGardenList, int count);

void	release(Garden** pGardenList, int count);

int compereByName(const void* name1 , const void* name2);
int compareByType(const void* type1, const void* type2);

void variadicFunction(char* str, int val, ...);


#endif
