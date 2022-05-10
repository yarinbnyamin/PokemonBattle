/*
 * BattleByCategory.c
 *
 *  Created on: Dec 14, 2021
 *      Author: yarin bnyamin 208896548
 */

#include "BattleByCategory.h"
#include "LinkedList.h"
#include "MaxHeap.h"
#include "Defs.h"

struct battle_s
{

	LinkedList list;  // linked list of types , each type is heap of elements in this type

	int numberOfCategories;
	getCategoryFunction getCategory;
	getAttackFunction getAttack;
	printFunction printElement;

};

int sameCategory (element heap, element category){
	return strcmp(getHeapId((MaxHeap)heap), (char*)category);
}

Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement){

	if(categories == NULL || equalElement == NULL || copyElement == NULL || freeElement == NULL || getCategory == NULL || getAttack == NULL || printElement == NULL)
		return NULL;

	Battle battle = (Battle)malloc(sizeof(struct battle_s));
	if(battle == NULL)
		return NULL;

	battle->list = createLinkedList(destroyHeap, equalHeap, printHeap, shallowCopyHeap, sameCategory);
	if(battle->list == NULL){
		free(battle);
		return NULL;
	}

	// insert the linked list a max heap for each category
	char* word= NULL;
	word = strtok(categories, ",");
	int i;
	status st;
	for(i=0; i< numberOfCategories; i++){
		st = appendNode(battle->list, createHeap(word, capacity, copyElement, freeElement, equalElement, printElement));
		if (st != success){ // failed to create heap or insert to list it's fatal error
			destroyList(battle->list);
			free(battle);
			return NULL;
		}

		word = strtok(NULL, ",");
	}


	battle->numberOfCategories = numberOfCategories;
	battle->getCategory = getCategory;
	battle->getAttack = getAttack;
	battle->printElement = printElement;

	return battle;

}

status destroyBattleByCategory(Battle b){
	// free all memory
	if(b == NULL)
		return failure;

	destroyList(b->list);
	free(b);
	return success;
}

status insertObject(Battle b, element elem){

	if(b == NULL || elem == NULL)
		return failure;

	element heap = searchByKeyInList(b->list, b->getCategory(elem));
	if(heap == NULL)  // not found the category
		return failure;

	return insertToHeap((MaxHeap)heap, elem);
}

void displayObjectsByCategories(Battle b){

	if(b == NULL)
		return;

	displayList(b->list);
}

element removeMaxByCategory(Battle b,char* category){

	if(b == NULL || category == NULL)
		return NULL;

	element heap = searchByKeyInList(b->list, category);
	if(heap == NULL)  // not found the category
		return NULL;

	return PopMaxHeap((MaxHeap)heap);
}

int getNumberOfObjectsInCategory(Battle b,char* category){

	if(b == NULL || category == NULL)
		return -1;

	element heap = searchByKeyInList(b->list, category);
	if(heap == NULL)  // not found the category
		return -1;

	return getHeapCurrentSize((MaxHeap)heap);
}

element fight(Battle b,element elem){

	if(b == NULL || elem == NULL || b->numberOfCategories == 0)
		return NULL;

	// choose the best elm that will result highest in battle
	int maxResult, curResult, attackFirst, attackSecond;
	element given = elem;  // rename for convenience

	Node node = getHead(b->list);  // each node is heap
	if(node == NULL)  // no list to pass on
		return NULL;

	element chosen = TopMaxHeap(getVal(node));
	node = getNext(node);
	while(chosen == NULL && node != NULL){
		chosen = TopMaxHeap(getVal(node));
		node = getNext(node);
	}
	if(chosen == NULL)  // no elm in each list
		return NULL;

	element c;
	maxResult = b->getAttack(chosen, given, &attackFirst, &attackSecond);

	// check if other pokemon is better option
	while(node != NULL){
		c = TopMaxHeap(getVal(node));
		node = getNext(node);

		if(c == NULL)
			continue;

		curResult = b->getAttack(c, given, &attackFirst, &attackSecond);

		if(curResult > maxResult){
			maxResult = curResult;
			chosen = c;
		}

	}


	// print results
	maxResult = b->getAttack(given, chosen, &attackFirst, &attackSecond);  // "reset" variables after changes
	printf("The final battle between:\n");
	b->printElement(given);
	printf("In this battle his attack is :%d\n\n", attackFirst);
	printf("against ");
	b->printElement(chosen);
	printf("In this battle his attack is :%d\n\n", attackSecond);

	if(maxResult == 0){
		printf("IT IS A DRAW.\n");
		return chosen;
	}

	printf("THE WINNER IS:\n");
	if(maxResult > 0){
		b->printElement(given);
		return given;
	}
	//else
	b->printElement(chosen);
	return chosen;



}


