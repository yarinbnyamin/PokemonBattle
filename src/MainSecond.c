/*
 * MainSecond.c
 *
 *  Created on: Nov 14, 2021
 *      Author: yarin bnyamin 208896548
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pokemon.h"
#include "BattleByCategory.h"
#include "Defs.h"


int index_in_types(Type** types, int size, char* search){
	/* this function return the index of the string search in the list types
	  	  if not found return -1 */

	int i;
	for(i=0; i< size; i++){
		if(strcmp(types[i]->name, search) == 0)
			return i;
	}

	return -1;  // not found
}

status print_all_pokes(Battle pokes){
	/* this function print all the Pokemons in the system */

	if(pokes == NULL)
		return failure;

	displayObjectsByCategories(pokes);
	return success;
}

status print_all_types(Type** types, int num_types){
	/* this function print all the Types in the list */

	if(types == NULL)
		return failure;

	status done;

	int i;
	for(i=0; i<num_types; i++){
		done = print_type(types[i]);
		if(done == err)
			return err;
	}

	return success;
}

status new_poke(Type** types, int num_types, Pokemon** p, int pos_type){
	/* this function create new pokemon with type of types[pos_type] and return it */

	if(types == NULL || num_types == 0 || pos_type < 0)
		return err;

	char* name = (char*)malloc(300 * sizeof(char));
	char* species = (char*)malloc(300 * sizeof(char));
	if(name == NULL || species == NULL){
		free(name);
		free(species);
		return err;
	}
	double h, w;
	int att;

	printf("Please enter Pokemon name:\n");
	scanf("%s", name );
	printf("Please enter Pokemon species:\n");
	scanf("%s", species );
	printf("Please enter Pokemon height:\n");
	scanf("%lf", &h );
	printf("Please enter Pokemon weight:\n");
	scanf("%lf", &w );
	printf("Please enter Pokemon attack:\n");
	scanf("%d", &att );

	*p = create_pokemon(name, species, types[pos_type], h, w, att);
	free(name);
	free(species);

	if(*p == NULL)
		return err;
	return success;
}

status add_new_poke(Battle pokes, Type** types, int num_types, int max_capacity){
	/* this function add new pokemon to the system */

	/*if(pokes == NULL || types == NULL)  // in the forum we want ask the user for more details
		return failure;*/

	char* name = (char*)malloc(300 * sizeof(char));
	if(name == NULL)
		return err;

	printf("Please enter Pokemon type name:\n");
	scanf("%s", name );
	int pos1 = index_in_types(types, num_types, name);

	if(pos1 == -1){
		printf("Type name doesn't exist.\n");
		free(name);
		return failure;
	}

	// if type is full can't create new pokemon
	if(max_capacity - getNumberOfObjectsInCategory(pokes, name) == 0){
		printf("Type at full capacity.\n");
		free(name);
		return failure;
	}
	free(name);

	Pokemon* p = NULL;
	status st = new_poke(types, num_types, &p, pos1);
	if(p == NULL)
		return st;

	st = insertObject(pokes, p);
	if(st != success){
		free_pokemon(p);
		return st;
	}

	printf("The Pokemon was successfully added.\n");
	print_pokemon(p);

	return success;
}

status del_strongest_by_type(Battle pokes, Type** types, int num_types){
	/* this function remove the strongest pokemon of an type */

	/*if(pokes == NULL || types == NULL)  // in the forum we want ask the user for more details
			return failure;*/

	char* name = (char*)malloc(300 * sizeof(char));
	if(name == NULL)
		return err;

	printf("Please enter type name:\n");
	scanf("%s", name );
	int pos1 = index_in_types(types, num_types, name);
	if(pos1 == -1){
		printf("Type name doesn't exist.\n");
		free(name);
		return failure;
	}

	element poke = removeMaxByCategory(pokes, name);
	free(name);

	if(poke == NULL){
		printf("There is no Pokemon to remove.\n");
		return failure;
	}

	printf("The strongest Pokemon was removed:\n");
	print_pokemon(poke);
	return free_pokemon(poke);

}

status start_fight(Battle pokes, Type** types, int num_types){
	/* this function vreate new pokemon and find the best pokemon from the system to fight him */

	/*if(pokes == NULL || types == NULL)  // in the forum we want ask the user for more details
			return failure;*/

	char* name = (char*)malloc(300 * sizeof(char));
	if(name == NULL)
		return err;

	printf("Please enter Pokemon type name:\n");
	scanf("%s", name );
	int pos1 = index_in_types(types, num_types, name);
	free(name);

	if(pos1 == -1){
		printf("Type name doesn't exist.\n");
		return failure;
	}

	Pokemon* p = NULL;
	status st = new_poke(types, num_types, &p, pos1);
	if(p == NULL)
		return st;

	printf("You choose to fight with:\n");
	print_pokemon(p);
	element elm = fight(pokes, p);
	free_pokemon(p);

	if(elm == NULL){
		printf("There are no Pokemons to fight against you.\n");
		return failure;
	}

	return success;
}

status freeSys(Battle pokes, Type** types, int num_types){
	/* this function free all the allocated memory */

	destroyBattleByCategory(pokes);

	int i;
	if(types != NULL){
		for(i=0; i<num_types; i++)
			free_type(types[i]);
		free(types);
	}

	return success;
}


int main(int argc,char*argv[]){

	if(argv == NULL){
		printf("Didn't got args.\n");
		return -1;
	}

	int num_types = atoi(argv[1]);
	int capacity_types = atoi(argv[2]);
	FILE *fp = fopen(argv[3],"r");

	if(fp == NULL){
		printf("File path not good.\n");
		return -1;
	}

	int i, pos1, pos2;
	char* line = (char*)malloc(300*sizeof(char));
	char* word= NULL;

	char* name = (char*)malloc(300 * sizeof(char));
	char* species = (char*)malloc(300 * sizeof(char));
	char* categories = (char*)malloc(300 * sizeof(char));

	if(line == NULL || name == NULL || species == NULL || categories == NULL){
		free(line);
		free(name);
		free(species);
		free(categories);

		printf("No memory available.\n");
		return -1;
	}

	double h, w;
	int att;

	Type** types = NULL;
	Battle pokes = NULL;

	if(num_types != 0){
		types = (Type**)malloc(num_types * sizeof(Type*));

		if(types == NULL){
			free(line);
			free(name);
			free(species);
			free(categories);

			printf("No memory available.\n");
			return -1;
		}
	}

	// extract data from file
	fgets(line, 300,fp);
	if(strcmp(line,"Types\r\n") == 0 && num_types > 0){  // types to array
		fgets(line, 300,fp);
		line[strlen(line)-2] = '\0';  // remove last \r\n

		strcpy(categories, line);
		pokes = createBattleByCategory(capacity_types, num_types, categories, cmp_pokemon_attack, shallow_copy_pokemon, free_pokemon, pokemon_type, pokemon_fight, print_pokemon);
		if(pokes == NULL){
			free(line);
			free(name);
			free(species);
			free(categories);
			free(types);

			printf("No memory available.\n");
			return -1;
		}

		word = strtok(line, ",");
		for(i=0; i< num_types; i++){
			types[i] = create_type(word);
			word = strtok(NULL, ",");
		}
		fgets(line, 300,fp);

		while(strcmp(line,"Pokemons\r\n") != 0){

			for(i=0; i< strlen(line); i++)
				if(line[i] == '\t' || line[i] == '-' || line[i] == ':' || line[i] == ',' || line[i] == '\n' || line[i] == '\r')
					line[i] = ' ';

			word = strtok(line, " ");
			pos1 = index_in_types(types, num_types, word);
			word = strtok(NULL, " ");  // drop effective
			word = strtok(NULL, " ");  // drop against
			word = strtok(NULL, " ");
			if(strcmp(word,"me") == 0){  // effective against me
				word = strtok(NULL, " ");
				while(word != NULL)
				{
					pos2 = index_in_types(types, num_types, word);
					add_stronger_vs_me(types[pos1], types[pos2]);
					word = strtok(NULL, " ");
				}
			}else{  // effective against other
				word = strtok(NULL, " ");
				while(word != NULL)
				{
					pos2 = index_in_types(types, num_types, word);
					add_weeker_vs_me(types[pos1], types[pos2]);
					word = strtok(NULL, " ");
				}
			}

			fgets(line, 300,fp);
		}

	}

	if(strcmp(line,"Pokemons\r\n") == 0){ // pokemons to array

		i=0;
		while(fgets(line, 300,fp) != NULL){

			if(line[strlen(line)-1] == '\n') // i < num_pokes-1
				line[strlen(line)-2] = '\0';  // remove last \r\n

			word = strtok(line, ",");  // pokemon name
			strcpy(name, word);
			word = strtok(NULL, ",");  // pokemon species
			strcpy(species, word);
			word = strtok(NULL, ",");  // pokemon height
			h = atof(word);
			word = strtok(NULL, ",");  // pokemon weight
			w = atof(word);
			word = strtok(NULL, ",");  // pokemon attack
			att = atoi(word);
			word = strtok(NULL, ",");  // pokemon type
			pos1 = index_in_types(types, num_types, word);

			insertObject(pokes, create_pokemon(name, species, types[pos1], h, w, att));

		}
	}

	fclose(fp);
	free(name);
	free(species);
	free(line);
	free(categories);

	status done = failure;  // check if we got error (err)

	char choice = '0';

	while(choice != '6')
	{
		printf("Please choose one of the following numbers:\n");
		printf("1 : Print all Pokemons by types\n");
	    printf("2 : Print all Pokemons types\n");
		printf("3 : Insert Pokemon to battles training camp\n");
		printf("4 : Remove strongest Pokemon by type\n");
		printf("5 : Fight\n");
		printf("6 : Exit\n");

		scanf(" %c", &choice);

		switch( choice )
		{
			case '1':  // Print all Pokemons by types
				done = print_all_pokes(pokes);
				break;
			case '2':  // Print all Pokemons types
				done = print_all_types(types, num_types);
				break;
			case '3':  // Insert Pokemon to battles training camp
				done = add_new_poke(pokes, types, num_types, capacity_types);
				break;
			case '4':  // Remove strongest Pokemon by type
				done = del_strongest_by_type(pokes, types, num_types);
				break;
			case '5':  // Fight
				done = start_fight(pokes, types, num_types);
				break;
			case '6':  // Exit
				done = freeSys(pokes, types, num_types);  // free memory
				printf("All the memory cleaned and the program is safely closed.\n");
				break;
			default:  // Not a valid option
				printf("Please choose a valid number.\n");
				break;
		}

		if(done == err){
			freeSys(pokes, types, num_types);  // free memory
			printf("No memory available.\n");
			return -1;
		}

	}
	return 0;

}
