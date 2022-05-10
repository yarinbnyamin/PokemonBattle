/*
 * LinkedList.h
 *
 *  Created on: Dec 14, 2021
 *      Author: yarin bnyamin 208896548
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include "Defs.h"


// Node
typedef struct a_Node *Node;
Node createNode(element);
element getVal(Node);
Node getNext(Node);

// LinkedList
typedef struct a_LinkedList *LinkedList;
LinkedList createLinkedList(freeFunction, equalFunction cmpByVal, printFunction, copyFunction, equalFunction cmpByKey);
status destroyList(element);
status appendNode(LinkedList, element);
status deleteNode(LinkedList, element);
status displayList(element);
element searchByKeyInList(LinkedList, element);
Node getHead(LinkedList);


#endif /* LINKEDLIST_H_ */
