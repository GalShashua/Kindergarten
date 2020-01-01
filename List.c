#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Kindergarten.h"

// create list
BOOLEAN initList(LIST* pList) {
	if (pList == NULL) {
		return False;
	}
	pList->head.next = NULL;
	return True;
}

// add data to new node (after pNode)
NODE* insertList(NODE* pNode, DATA Value) {
	NODE* tmp;
	if (!pNode) {
		return NULL;
	}
	tmp = (NODE*) malloc(sizeof(NODE));
	if (tmp != NULL) {
		tmp->key = Value;
		tmp->next = pNode->next;
		pNode->next = tmp;
	}
	return tmp;
}

// delete specific node from linked list
BOOLEAN deleteNode(NODE* pNode)
{
	NODE* tmp;
	if (!pNode || !(tmp = pNode->next))
		return False;
	pNode->next = tmp->next;
	free(tmp);
	return True;
}


// free allocations for linked list
BOOLEAN freeList(LIST* pList)
{
	NODE *tmp;
	if (!pList)
		return False;
	for (tmp = &(pList->head); deleteNode(tmp);)
		;
	return True;
}


// specific list print for kindergarten
void printList(LIST* pList,  void (*print)(const void*))
{
	NODE *tmp;
	if (!pList)
		return;
	printf("\n");
	for (tmp = pList->head.next; tmp; tmp = tmp->next) {
		print(tmp->key);
		printf("\n");
	}
	printf("\n");
}
