#include "game_field.h"
#include "ability.h"
#include "ability_manager.h"
#include "ship.h"
#include "ship_manager.h"
#include "exception.h"

void GameField::attack_cell(int x, int y, ShipManager& manager, AbilityManager& manager_ability) { 
    try{
        if (x < 0 || x >= width || y < 0 || y >= height) {
            throw OutOfBoundsException("Attack coordinates are out of range.", width, height);
        }
    
        for (int i = 0; i < count_ships; ++i) {
            Ship& ship = manager.get_ship(i);
            int ship_length = ship.get_length();
            bool is_vertical = ship.is_vertical_orientation();

            if (is_vertical) {
                if (x == ship.get_x()) {
                    for (int j = 0; j < ship_length; ++j) {
                        if (y == ship.get_y() + j) {
                            if(ship.get_segment_state(j) == 2) {
                                cout << "This segment has already been destroyed." << endl;
                                return;
                            }
                            ship.damage_segment(j);
                            if(double_damage) ship.damage_segment(j);
                            if (get_double_damage()) set_double_damage(false);
                            if(ship.is_destroy()) manager_ability.grand_random_ability();
                            cout << "Hit!" << endl;
                            return;
                        }
                    }
                }
            } else {
                if (y == ship.get_y()) {
                    for (int j = 0; j < ship_length; ++j) {
                        if (x == ship.get_x() + j) {
                            if(ship.get_segment_state(j) == 2) {
                                cout << "This segment has already been destroyed." << endl; 
                                return;
                            }
                            ship.damage_segment(j);
                            if(double_damage) ship.damage_segment(j);
                            if (get_double_damage()) set_double_damage(false);
                            if(ship.is_destroy()) manager_ability.grand_random_ability();
                            cout << "Hit!" << endl;
                            return;
                        }
                    }
                }
            }
        }

        field[y][x] = empty_state;
        if (get_double_damage()) set_double_damage(false);
        cout << "Miss!" << endl;
    } catch (OutOfBoundsException& e) {
        cout << "The field has a width of " << e.get_width_state() << " and a height of " << e.get_height_state() << endl; 
        cerr << e.what() << endl;
    } 
    
}

void GameField::print_with_fog_war(ShipManager& manager) {
    cout << "Field: " << endl;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            bool is_hit = false;

            for (int i = 0; i < count_ships; ++i) {
                Ship& ship = manager.get_ship(i);
                int ship_length = ship.get_length();
                bool is_vertical = ship.is_vertical_orientation();

                if (is_vertical) {
                    if (x == ship.get_x()) {
                        for (int j = 0; j < ship_length; ++j) {
                            if (y == ship.get_y() + j && ship.get_segment_state(j) != 0) {
                                is_hit = true;
                                break;
                            }
                        }
                    }
                } else {
                    if (y == ship.get_y()) {
                        for (int j = 0; j < ship_length; ++j) {
                            if (x == ship.get_x() + j && ship.get_segment_state(j) != 0) {
                                is_hit = true;
                                break;
                            }
                        }
                    }
                }
                if (is_hit) break;
            }

            if (field[y][x] == unknown_state) {
                cout << ".";
            } else if (field[y][x] == empty_state) {
                cout << "-";
            } else if (is_hit) {
                cout << "*"; 
            } else {
                cout << "."; 
            }
        }
        cout << endl;
    }
}


void GameField::print_all_ship() {
    cout << "Ships on the field: " << endl;
    for(int x = 0; x < height; x++) {
        for(int y = 0; y < width; y++) {
            if(field[x][y] == 2) {
                cout << "*";
            } else if (field[x][y] == 0 || field[x][y] == 1) {
                cout << ".";
            }
        }
        cout << endl;
    }
}
 
ShipManager GameField::calculation_count_ships() {
    int count_cell = width * height;
    int count_ships_cell = count_cell / 5;
    vector<int> ship_sizes;

    if (count_ships_cell >= 20) { 
        ship_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1}; 
        count_ships = 10;
    } else if (count_ships_cell >= 15) {
        ship_sizes = {3, 3, 2, 2, 1, 1, 1};
        count_ships = 7;
    } else {
        ship_sizes = {2, 2, 1, 1}; 
        count_ships = 4;
    }
    return ShipManager(ship_sizes.size(), ship_sizes);
}

void GameField::place_ship(Ship& ship, int x, int y, string orientation) {
    while (true) {
        try {
            if(orientation == "h") {
                ship.set_orientation(0);
            } else if (orientation == "v") {
                ship.set_orientation(1);
            } else if (orientation == "dont have") {

            } else {
                throw OrientationShipException("The ship must have horizontal(h) or vertical(v).");
            }

            int length = ship.get_length();

            if(x > width || y > height || x < 0 || y < 0 || x+length > width || y+length > height) {
                throw OutOfBoundsException("The coordinates are out of the field.", width, height);
            }
            
            for (int i = -1; i <= length; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int check_x = ship.is_vertical_orientation() ? x + j : x + i;
                    int check_y = ship.is_vertical_orientation() ? y + i : y + j;
                    
                    if (check_y >= 0 && check_y < height && check_x >= 0 && check_x < width) {
                        if (field[check_y][check_x] != unknown_state) {
                            cout << check_y << " " << check_x << endl;
                            throw InvalidShipPlacementException("The place is occupied or too close to another ship.", check_x, check_y);
                        }
                    }
                }
            }

            if (ship.is_vertical_orientation()) {
                for (int i = 0; i < length; ++i) {
                    field[y + i][x] = ship_state;
                }
            } else {
                for (int i = 0; i < length; ++i) {
                    field[y][x + i] = ship_state;
                }
            }
            ship.set_x(x);
            ship.set_y(y);
            break;
        } catch (OutOfBoundsException& e) {
            cout << "The field has a width of " << e.get_width_state() << " and a height of " << e.get_height_state() << endl; 
            cerr << e.what() << endl;
            cout << "Re-enter coordinates: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> x >> y;
        } 
        catch (InvalidShipPlacementException& e) {
            cout << "The ship is already located at coordinates x - " << e.get_x_state() << " y - " << e.get_y_state() << endl;
            cerr << e.what() << endl;
            cout << "Re-enter coordinates: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> x >> y;
        }
        catch (OrientationShipException& e) {
            cerr << e.what() << endl;
            cout << "Re-enter coordinates: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> x >> y;
        }
    }
}

int GameField::get_cell_status(int x, int y) {
    return field[x][y];
}


GameField& GameField::operator=(GameField&& other) noexcept {
    if (this == &other) return *this;

    for (int i = 0; i < height; ++i) {
        delete[] field[i];
    }
    delete[] field;

    width = other.width;
    height = other.height;
    field = other.field;
    count_ships = other.count_ships;

    other.field = nullptr;

    return *this;
}

GameField& GameField::operator=(const GameField& other) {
    if (this == &other) return *this;

    for (int i = 0; i < height; ++i) {
        delete[] field[i];
    }
    delete[] field;

    width = other.width;
    height = other.height;
    count_ships = other.count_ships;

    field = new cell_status*[height];
    for (int i = 0; i < height; ++i) {
        field[i] = new cell_status[width];
        copy(other.field[i], other.field[i] + width, field[i]);
    }
    
    return *this;
}