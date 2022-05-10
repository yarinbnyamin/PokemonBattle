/*
 * Defs.h
 *
 *  Created on: Nov 19, 2021
 *      Author: yarin bnyamin 208896548
 */

#ifndef DEFS_H_
#define DEFS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum e_bool {false, true} bool;
typedef enum e_status {success, failure, err} status;

typedef void * element;

typedef element(*copyFunction) (element);
typedef status(*freeFunction) (element);
typedef status(*printFunction) (element);
typedef int(*equalFunction) (element, element); // 1 first bigger, 0 same, -1 second bigger
typedef char*(*getCategoryFunction) (element);
typedef int(*getAttackFunction) (element firstElem, element secondElem, int* attackFirst, int* attackSecond);
/* return the first attack - second attack. also produce the attack of each element,
 * The function transmits the information through the pointers received in the function. */

#endif /* DEFS_H_ */
