#ifndef BOMBARD_H_
#define BOMBARD_H_

#include "ability.h"

class Bombard : public Ability {
public:
    void apply(GameField& filed, int x, int y, ShipManager& manager) override;
};

#endif
