PokemonsBattles: Pokemon.o LinkedList.o MaxHeap.o BattleByCategory.o MainSecond.o
	gcc Pokemon.o LinkedList.o MaxHeap.o BattleByCategory.o MainSecond.o -o PokemonsBattles
	
Pokemon.o: Pokemon.c Pokemon.h Defs.h
	gcc -c Pokemon.c

LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c
	
MaxHeap.o: MaxHeap.c MaxHeap.h Defs.h
	gcc -c MaxHeap.c
	
BattleByCategory.o: BattleByCategory.c BattleByCategory.h LinkedList.h MaxHeap.h Defs.h
	gcc -c BattleByCategory.c
	
MainSecond.o: MainSecond.c Pokemon.h BattleByCategory.h Defs.h
	gcc -c MainSecond.c

clean:
	rm -f *.o PokemonsBattles
