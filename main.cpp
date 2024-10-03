#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include <SFML/Graphics.hpp>
#include "ship_manager.h"
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <random> 
#include <string>
#include "ship.h"
#include "ability_manager.h"
#include "game_field.h"

using namespace std;

class Ship;
class ShipManager;
class AbilityManager;

int main() {
    try {
        int width_field;
        int height_filed;
        cout <<  "Enter field width: ";
        cin >> width_field;

        cout <<  "Enter field height: ";
        cin >> height_filed;

        GameField field(width_field, height_filed);
        AbilityManager manager_ability;
        
        ShipManager manager = field.calculation_count_ships();
        int count_ships = field.count_ships;

        for(int i = 0; i < count_ships; i++) {
            Ship& ship1 = manager.get_ship(i);
            int x;
            int y;
            string orientation;
            cout << "Enter coordinate ship and orientation: ";
            cin >> x >> y;
            while(!cin) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter numbers: ";
                cin >> x >> y;
            }
            if(cin.peek() == '\n') {
                orientation = "dont have";
            } else {
                cin >> orientation;
            }
            field.place_ship(ship1, x, y, orientation);
        }
        field.print_all_ship();
        
        while(true) {
            string comand;
            cout << "Enter command: ";
            cin >> comand;
            if(comand == "attack") {
                int x, y;
                cout << "Coordinate for attack: ";
                cin >> x >> y;
                field.attack_cell(x, y, manager, manager_ability);
            } else if (comand == "state_ships") {
                manager.print();
            } else if (comand == "end") {
                exit(0);
            } else if (comand == "field_all") {
                field.print_all_ship();
            } else if (comand == "field") {
                field.print_with_fog_war(manager);
            } else if (comand == "abilities") {
                manager_ability.next_abilities();
            } else if (comand == "apply_ability") {
                string message = manager_ability.next_abilities(1);
                if(message == "DoubleDamage") {
                    manager_ability.apply_ability(field, 0, 0, manager);
                } else if (message == "Scanner") {
                    int x, y;
                    cout << "Coordinate for ability: ";
                    cin >> x >> y;
                    manager_ability.apply_ability(field, x, y, manager);
                } else if (message == "Bombard") {
                    manager_ability.apply_ability(field, 0, 0, manager);
                }
            } else if (comand == "help") {
                cout << "attack - attack someone cell" << "\n" << "state_ships - detailed status of each class" << "\n" << "end - end of program" 
                << "\n" << "field_all - see the fielf woth ships" << "\n" << "field - view the playong field "<< "\n" 
                << "abilities - view current ability" << "\n" << "apply_ability - cast the next ability in the queue" << endl;
            }
        }
    } catch (const exception& e) {
        cerr << e.what() << '\n';
    }

    return 0;
}


// 4 5
// 0 0
// 2 3
// 7 7
// 2 8
// 8 2
// 0 7 v
// 0 5
// 6 0
// 8 5

// 736
