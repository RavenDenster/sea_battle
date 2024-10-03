ready : main.o game_field.o ship_manager.o ship.o ability.o ability_manager.o double_damage.o scanner.o bombard.o
	g++ main.o game_field.o ship_manager.o ship.o ability.o ability_manager.o double_damage.o scanner.o bombard.o -o ready

main.o : main.cpp
	g++ -c main.cpp -o main.o

game_field.o : game_field.cpp ship_manager.h ship.h 
	g++ -c game_field.cpp -o game_field.o

ship_manager.o : ship_manager.cpp game_field.h ship.h exception.h
	g++ -c ship_manager.cpp -o ship_manager.o

ship.o : ship.cpp game_field.h ship_manager.h
	g++ -c ship.cpp -o ship.o

ability.o : ability.cpp ability.h
	g++ -c ability.cpp -o ability.o

ability_manager.o : ability_manager.cpp ability_manager.h
	g++ -c ability_manager.cpp -o ability_manager.o

double_damage.o : double_damage.cpp double_damage.h ability.h
	g++ -c double_damage.cpp -o double_damage.o

scanner.o : scanner.cpp scanner.h ability.h
	g++ -c scanner.cpp -o scanner.o

bombard.o : bombard.cpp bombard.h ability.h
	g++ -c bombard.cpp -o bombard.o

.PHONY: clean
clean:
	rm -rf *.o ready