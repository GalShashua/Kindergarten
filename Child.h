#ifndef __CHILD__
#define __CHILD__


typedef struct
{
	int	 id;
	int  age;
}Child;


void 	readChild(FILE* fp, Child* pChild, int textMode);
void	getChildFromUser(Child* pChild, int id);
void	showChild(const Child* pChild);
void 	writeChild(FILE* fp,const Child* pChild,int textMode);
int		findChildById(Child** pChildList, int count, int id);
void	birthday(Child* pChild);
//void	releaseChild(Child* pChild);
int compareByIdChild(const void* num1, const void* num2);

#endif
