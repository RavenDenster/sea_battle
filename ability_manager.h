#ifndef ABILITY_MANAGER_H_
#define ABILITY_MANAGER_H_

#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random> 
#include <string> 
#include "double_damage.h"
#include "bombard.h"
#include "scanner.h"

class GameField; 
class ShipManager;
 
class AbilityManager {
private:
    queue<unique_ptr<Ability>> abilities;
 
public:
    AbilityManager() {
        vector<unique_ptr<Ability>> available_abilities;
        available_abilities.emplace_back(make_unique<DoubleDamage>());
        available_abilities.emplace_back(make_unique<Scanner>());
        available_abilities.emplace_back(make_unique<Bombard>());

        random_device rd;
        mt19937 g(rd());

        shuffle(available_abilities.begin(), available_abilities.end(), g);

        for(auto &ability : available_abilities) {
            abilities.push(move(ability));
        }
    }

    void apply_ability(GameField& field, int x, int y, ShipManager& manager);

    string next_abilities(bool flag_messge = false);

    void grand_random_ability();

};

#endif