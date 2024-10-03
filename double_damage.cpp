#include "double_damage.h"
#include "game_field.h"
#include "ship_manager.h"

void DoubleDamage::apply(GameField& field, int x, int y, ShipManager& manager) {
    field.set_double_damage(true);
    cout << "Next hit deals double damage" << endl;
}