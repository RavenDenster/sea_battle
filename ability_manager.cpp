#include "ability_manager.h"
#include "ship.h"
#include "ship_manager.h"
#include "ability.h"
#include "exception.h"

void AbilityManager::apply_ability(GameField& field, int x, int y, ShipManager& manager) {
    try {
        if(!abilities.empty()) {
            abilities.front()->apply(field, x, y, manager);
            abilities.pop();
        } else {
            throw NoAbilitiesException("No abilities available.");
        }
    } catch (NoAbilitiesException& e) {
        cerr << e.what() << endl;
    }
} 

string AbilityManager::next_abilities(bool flag_messge) {
    string message;
    if(!abilities.empty()) {
        if(!flag_messge) {
            cout << "Следующая способность: ";
        }
        if (dynamic_cast<DoubleDamage*>(abilities.front().get())) {
            message = "DoubleDamage";
        } else if (dynamic_cast<Scanner*>(abilities.front().get())) {
            message = "Scanner";
        } else if (dynamic_cast<Bombard*>(abilities.front().get())) {
            message = "Bombard";
        }
        cout << message << endl;
    } else {
        cout << "No abilities available." << endl;
    }

    return message;
}
 
void AbilityManager::grand_random_ability() {
    srand(time(NULL));
    vector<unique_ptr<Ability>> new_ability;
    int random = rand(); 

    if(random % 3 == 0) {
        new_ability.emplace_back(make_unique<DoubleDamage>());
    } else if (random % 3 == 1) {
        new_ability.emplace_back(make_unique<Scanner>());
    } else if (random % 3 == 2) {
        new_ability.emplace_back(make_unique<Bombard>());
    }
    abilities.push(move(new_ability[0]));
    cout << "Получена новая способность." << endl;
} 