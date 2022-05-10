/*
 * MaxHeap.h
 *
 *  Created on: Dec 14, 2021
 *      Author: yarin bnyamin 208896548
 */

#ifndef MAXHEAP_H_
#define MAXHEAP_H_
#include "Defs.h"

typedef struct a_MaxHeap *MaxHeap;
MaxHeap createHeap(char*, int, copyFunction, freeFunction, equalFunction, printFunction);
status destroyHeap(element);
status insertToHeap(MaxHeap, element);
status printHeap(element);
element PopMaxHeap(MaxHeap);
element TopMaxHeap(MaxHeap);
char* getHeapId(MaxHeap);
int getHeapCurrentSize(MaxHeap);
int equalHeap(element, element);  // compare by name
element shallowCopyHeap(element);
void maxHeapify(MaxHeap, int);  // sort the heap

#endif /* MAXHEAP_H_ */
