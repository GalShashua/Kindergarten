#ifndef __CITY__
#define __CITY__

#include "Kindergarten.h"
#include "List.h"

#define DATA_FILE_TXT "DataFile.txt"
#define DATA_FILE_BIN "DataFile.bin"


typedef struct
{
	Garden** pGardenList;
	int count;
}City;


void 	readCity(City* pCity, int textMode);
void	showCityGardens(City* pCity);
void	showSpecificGardenInCity(City* pCity);
void 	saveCity(City* pCity, int textMode);
void	cityAddGarden(City* pCity);
void	addChildToSpecificGardenInCity(City* pCity);
void	birthdayToChild(City* pCity);
int		countChova(City* pCity);
void	releaseCity(City* pCity);
void	sortByName(City* pCity);
void	sortByType(City* pCity);
void	sortById(City* pCity);
void 	kindergartensLinkedList(City* pCity);
LIST* 	createLinkedListForKindergartenType(City* pCity, int KinderType);
void	displayKindergartensFromList(LIST* list);

#endif
