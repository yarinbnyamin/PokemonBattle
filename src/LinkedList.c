/*
 * LinkedList.c
 *
 *  Created on: Dec 14, 2021
 *      Author: yarin bnyamin 208896548
 */

#include "LinkedList.h"
#include "Defs.h"


// Node
struct a_Node
{
	element val;
	Node next;
};


Node createNode(element val){
	Node n = (Node)malloc(sizeof(struct a_Node));
	if(n == NULL)
		return NULL;
	n->val = val;
	n->next = NULL;
	return n;

}

element getVal(Node node){
	return node->val;
}

Node getNext(Node node){
	return node->next;
}

// LinkedList
struct a_LinkedList
{
	Node head;
	Node tail;
	int size;
	freeFunction freeFunc;
	equalFunction cmpByVal;
	printFunction print;
	copyFunction copy;
	equalFunction cmpByKey;

};

LinkedList createLinkedList(freeFunction freeFunc, equalFunction cmpByVal, printFunction print, copyFunction copy, equalFunction cmpByKey){

	if(freeFunc == NULL || cmpByVal == NULL || print == NULL || copy == NULL || cmpByKey == NULL)
		return NULL;

	LinkedList list = (LinkedList)malloc(sizeof(struct a_LinkedList));
	if(list == NULL)
		return NULL;

	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	list->freeFunc = freeFunc;
	list->cmpByVal = cmpByVal;
	list->print = print;
	list->copy = copy;
	list->cmpByKey = cmpByKey;

	return list;
}

status destroyList(element l){
	// free all memory
	if(l == NULL)
		return failure;

	LinkedList list = (LinkedList)l;

	Node cur = list->head;
	Node next;

	while(cur != NULL){
		next = cur->next;
		list->freeFunc(cur->val);
		free(cur);
		cur = next;
	}

	free(list);
	return success;

}

status appendNode(LinkedList list, element elm){

	if(list == NULL || elm == NULL)
		return failure;

	Node new = createNode(list->copy(elm));
	if(new == NULL)
		return err;

	if(list->size == 0){
		list->head = new;
		list->tail = new;
	}else{
		list->tail->next = new;
		list->tail = new;
	}

	list->size++;
	return success;

}

status deleteNode(LinkedList list, element elm){

	if(list == NULL || elm == NULL)
		return failure;

	Node cur = list->head;

	// if in the head
	if(list->cmpByVal(cur->val, elm) == 0){
		if(list->size == 1)
			list->tail = NULL;
		list->head = cur->next;
		list->freeFunc(cur->val);
		free(cur);
		list->size--;
		return success;
	}

	// if not in the head search it

	Node before = cur;
	cur = cur->next;

	while(cur != NULL){
		if(list->cmpByVal(cur->val, elm) == 0){
			if(cur->next == NULL)
				list->tail = before;
			before->next = cur->next;
			list->freeFunc(cur->val);
			free(cur);
			list->size--;
			return success;
		}

		before = cur;
		cur = cur->next;
	}

	// if elm not found in the list
	return failure;

}

status displayList(element l){

	if(l == NULL)
		return failure;

	LinkedList list = (LinkedList)l;

	Node cur = list->head;
	while(cur != NULL){
		list->print(cur->val);
		cur = cur->next;
	}
	return success;
}

element searchByKeyInList(LinkedList list, element elm){

	if(list == NULL || elm == NULL)
		return NULL;

	Node cur = list->head;
	while(cur != NULL){
		if(list->cmpByKey(cur->val, elm) == 0)
			return cur->val;

		cur = cur->next;
	}
	return NULL;

}

Node getHead(LinkedList list){
	return list->head;
}
