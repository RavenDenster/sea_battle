#ifndef SCANNER_H_
#define SCANNER_H_

#include "ability.h"

class Scanner : public Ability {
public:
    void apply(GameField& field, int x, int y, ShipManager& manager) override;
};

#endif