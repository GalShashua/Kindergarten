#ifndef LIST_H_
#define LIST_H_

typedef void* DATA;
typedef enum {False, True} BOOLEAN;

typedef struct node
{
	DATA key;
	struct node* next;
} NODE;

typedef struct
{
	NODE head;
} LIST;

BOOLEAN initList(LIST* pList);

NODE* insertList(NODE* pNode, DATA Value);

BOOLEAN deleteNode(NODE* pNode);

BOOLEAN freeList(LIST* pList);

void printList(LIST* pList, void (*print)(const void*));

#endif /* LIST_H_ */
