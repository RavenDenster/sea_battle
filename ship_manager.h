#ifndef SHIP_MANAGER_H_
#define SHIP_MANAGER_H_

#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include "ship.h"

using namespace std;
class Ship;
class ShipManager {
private:
    vector<unique_ptr<Ship>> ships;
    int count;
public:
    ShipManager(int count, const vector<int>& sizes) : count(count) {
        if (count != sizes.size()) {
            throw invalid_argument("Count of ships must match sizes vector.");
        }
        for (int size : sizes) {
            ships.emplace_back(make_unique<Ship>(size, size % 2 == 0));
        }
    }

    void print();

    int get_ships_count() {return count;}

    Ship& get_ship(int index) const { return *ships[index]; }
};

#endif