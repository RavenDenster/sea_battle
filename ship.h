#ifndef SHIP_H_
#define SHIP_H_

#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>

using namespace std;

class Ship {
enum ship_state {
    whole_state,
    damaged_state,
    destroyed_state
};

private:
    int length;
    bool is_vertical;
    int x, y;

public:
    vector<ship_state> segments;
    Ship(int length, bool is_vertical) : length(length), is_vertical(is_vertical) {
        if (length < 1 || length > 4) {
            throw invalid_argument("Ship length must be between 1 and 4.");
        }
        segments.resize(length, whole_state);
    }

    void damage_segment(int index);
    int get_segment_state(int index) const;

    int get_length() const { return length; }
    bool is_vertical_orientation() const { return is_vertical; }
    void set_orientation(bool trigger) { is_vertical = trigger; }
    bool is_destroy();
     
    int get_x() const {return x;}
    void set_x(int new_x) {x = new_x;}
    int get_y() const {return y;}
    void set_y(int new_y) {y = new_y;}
};

#endif