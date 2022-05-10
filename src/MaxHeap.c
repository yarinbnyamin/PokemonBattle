/*
 * MaxHeap.c
 *
 *  Created on: Dec 14, 2021
 *      Author: yarin bnyamin 208896548
 */

#include "MaxHeap.h"
#include "Defs.h"


struct a_MaxHeap
{
	char* id;
	int max_size;
	int cur_size;
	element* list;

	copyFunction copy;
	freeFunction freeFunc;
	equalFunction cmpByVal;
	printFunction print;

};

MaxHeap createHeap(char* id, int max_size, copyFunction copy, freeFunction freeFunc, equalFunction cmpByVal, printFunction print){

	if(id == NULL || copy == NULL || freeFunc == NULL || cmpByVal == NULL || print == NULL)
		return NULL;

	MaxHeap heap = (MaxHeap)malloc(sizeof(struct a_MaxHeap));
	if(heap == NULL)
		return NULL;

	heap->id = (char*)malloc((strlen(id)+1) * sizeof(char));
	if(heap->id == NULL){
		free(heap);
		return NULL;
	}
	strcpy(heap->id, id);

	heap->list = (element*)malloc(sizeof(element)*max_size);
	if(heap->list == NULL){
		free(heap->id);
		free(heap);
		return NULL;
	}

	heap->max_size = max_size;
	heap->cur_size = 0;
	heap->copy = copy;
	heap->freeFunc = freeFunc;
	heap->cmpByVal = cmpByVal;
	heap->print = print;

	return heap;
}

status destroyHeap(element h){

	if(h == NULL)
		return failure;

	MaxHeap heap = (MaxHeap)h;

	int i;
	for(i=0;i<heap->cur_size;i++)
		heap->freeFunc(heap->list[i]);

	free(heap->list);
	free(heap->id);
	free(heap);
	return success;

}

status insertToHeap(MaxHeap heap, element elm){

	if(heap == NULL || elm == NULL || heap->cur_size == heap->max_size)
		return failure;

	element new = heap->copy(elm);
	if(new == NULL)
		return err;

	heap->list[heap->cur_size] = new;
	heap->cur_size++;

	// sort the list
	int i;
	for(i = ((heap->cur_size-2)/2);i >= 0;i=(i-1)/2){
		maxHeapify(heap, i);
		if(i == 0)
			break;
	}

	return success;

}

status printHeap(element h){

	if(h == NULL)
		return failure;

	MaxHeap heap = (MaxHeap)h;

	printf("%s:\n", heap->id);
	if(heap->cur_size == 0){
		printf("No elements.\n\n");
		return success;
	}

	// copy to new heap
	MaxHeap copy_heap = createHeap(heap->id, heap->max_size, heap->copy, heap->freeFunc, heap->cmpByVal, heap->print);
	if(copy_heap == NULL)
		return err;

	int i;
	for(i=0;i<heap->cur_size;i++)
		insertToHeap(copy_heap, heap->list[i]);

	//print
	for(i=0;i<heap->cur_size;i++){
		element elm = PopMaxHeap(copy_heap);
		printf("%d. ", i+1);
		heap->print(elm);
	}

	destroyHeap(copy_heap);
	return success;
}

element PopMaxHeap(MaxHeap heap){
	if(heap == NULL || heap->cur_size == 0)
		return NULL;

	element max = heap->list[0];

	heap->cur_size--;
	if(heap->cur_size == 0)
		return max;

	heap->list[0] = heap->list[heap->cur_size];
	maxHeapify(heap, 0);

	return max;
}

element TopMaxHeap(MaxHeap heap){
	if(heap == NULL || heap->cur_size == 0)
		return NULL;

	return heap->list[0];
}

char* getHeapId(MaxHeap heap){
	if(heap == NULL)
		return NULL;
	return heap->id;
}

int getHeapCurrentSize(MaxHeap heap){
	if(heap == NULL)
		return -1;
	return heap->cur_size;
}

int equalHeap(element heap1, element heap2){  // compare by name

	if(heap1 == NULL || heap2 == NULL)
		return -1;

	return strcmp(((MaxHeap)heap1)->id, ((MaxHeap)heap2)->id);

}

element shallowCopyHeap(element heap){
	return heap;
}

void maxHeapify(MaxHeap heap, int i){
	// sort the heap
	int largest = i;
	element temp;

	int left = (2*(i+1)-1);
	int right = (2*(i+1));

	if (left < heap->cur_size && heap->cmpByVal(heap->list[left],heap->list[i]) == 1) // check left child
		largest = left;
	if (right < heap->cur_size && heap->cmpByVal(heap->list[right],heap->list[largest]) == 1)// check right child
		largest = right;
	if(largest != i){ // if child bigger than swap
		temp = heap->list[i];
		heap->list[i] = heap->list[largest];
		heap->list[largest] = temp;
		maxHeapify(heap, largest);
	}

}

