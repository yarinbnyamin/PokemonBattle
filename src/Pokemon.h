/*
 * Pokemon.h
 *
 *  Created on: Nov 19, 2021
 *      Author: yarin bnyamin 208896548
 */

#ifndef POKEMON_H_
#define POKEMON_H_
#include "Defs.h"


typedef struct type_st {
    char*  name;
    int counter;
    int stronger_vs_me;
    struct type_st **effective_against_me;
    int weeker_vs_me;
    struct type_st **effective_against_other;
}Type;

Type* create_type(char*);
// add type other to the effective_against_me list of me
status add_stronger_vs_me(Type*, Type*);
// add type other to the effective_against_other list of me
status add_weeker_vs_me(Type*, Type*);
// delete type other to the effective_against_me list of me
status del_stronger_vs_me(Type*, Type*);
// delete type other to the effective_against_other list of me
status del_weeker_vs_me(Type*, Type*);
// print type
status print_type(Type*);
// free memory of type
void free_type(Type*);


typedef struct bio_info_st {
    double  height;
    double weight;
    int attack;
}Bio_Info;

Bio_Info* create_bio(double, double, int);
// print bio info
status print_bio(Bio_Info*);
// free memory of bio info
void free_bio(Bio_Info*);


typedef struct pokemon_st {
    char*  name;
    char*  species;
    Type* type;
    Bio_Info* bio;
}Pokemon;

Pokemon* create_pokemon(char*, char*, Type*, double, double, int);
// print pokemon
status print_pokemon(element);
// compare pokemon attack - 1 first stronger, 0 same, -1 second stronger
int cmp_pokemon_attack(element, element);
// free memory of pokemon
status free_pokemon(element);
// shallow copy pokemon
element shallow_copy_pokemon (element);
// return type of pokemon
char* pokemon_type(element);
// pokemon fight
int pokemon_fight(element firstElem, element secondElem, int* attackFirst, int* attackSecond);


#endif /* POKEMON_H_ */
