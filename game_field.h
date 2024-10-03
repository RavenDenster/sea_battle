#ifndef GAME_FIELD_H_
#define GAME_FIELD_H_

#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>

using namespace std;

class Ship;
class ShipManager;
class AbilityManager;

class GameField {
enum cell_status {
    unknown_state,
    empty_state,
    ship_state
};
private:
    int width, height;
    cell_status** field;
    bool double_damage = false;
public:
    int count_ships;
    GameField(int width_f, int height_f) : width(width_f), height(height_f) {
        if(width_f > 20 || height_f > 20) {
            throw invalid_argument("Too big field.");
        }
        if(width_f < 5 || height_f < 5) {
            throw invalid_argument("Too small field.");
        }
        field = new cell_status*[height_f];
        for (int i = 0; i < height_f; ++i) {
            field[i] = new cell_status[width_f];
            fill(field[i], field[i] + width_f, unknown_state);
        }
    }

    GameField(const GameField& other) : width(other.width), height(other.height), count_ships(other.count_ships) {
        field = new cell_status*[height];
        for (int i = 0; i < height; ++i) {
            field[i] = new cell_status[width];
            copy(other.field[i], other.field[i] + width, field[i]);
        }
    }
    GameField(GameField&& other) noexcept : width(other.width), height(other.height), field(other.field), count_ships(other.count_ships) {
        other.field = nullptr;
    }

    GameField& operator=(const GameField& other);

 
    GameField& operator=(GameField&& other) noexcept;
    void place_ship(Ship& ship, int x, int y, string orientation);

    ShipManager calculation_count_ships();

    void print_all_ship();
    void print_with_fog_war(ShipManager& manager);
    int get_cell_status(int x, int y);

    void attack_cell(int x, int y, ShipManager& manager, AbilityManager& manager_ability);

    int get_height() const {return height;}
    int get_width() const {return width;}

    bool get_double_damage() {return double_damage;}
    void set_double_damage(bool value) {double_damage = value;}

    ~GameField() {
        for (int i = 0; i < height; ++i) {
            delete[] field[i];
        }
        delete[] field;
    }

};

#endif