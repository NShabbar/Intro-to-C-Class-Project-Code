all: rpg

rpg: Player.o Game.o Lab08_main.o
	gcc -Wall Player.c Game.c Lab08_main.c -o rpg
	
Player.o: Player.c UNIXBOARD.h Player.h
	gcc -Wall -c Player.c

Game.o: Game.c UNIXBOARD.h Game.h Player.h
	gcc -Wall -c Game.c

Lab08_main.0: Lab08_main.c UNIXBOARD.h Game.h
	gcc -Wall -c Lab08_main.c
	
clean:
	rm -f *.o
	rm -f rpg