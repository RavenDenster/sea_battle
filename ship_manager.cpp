#include "ship_manager.h"


void ShipManager::print() {
    for(int i = 0; i < ships.size(); i++) {
        Ship& ship = *ships[i];
        int len_ship = ship.get_length();
        int count_destroy = 0;
        cout << "Ship " << i+1 <<": ";
        for(int i = 0; i < len_ship; i++) {
            int state = ship.get_segment_state(i);
            if(state == 0) {
                cout << "w"; // whole
            } else if (state == 1) {
                cout << "1h"; // 1 hit
            } else if (state == 2) {
                cout << "d"; // destroy 
                count_destroy++;
            }
            cout << " ";
        }
        if(count_destroy == len_ship) {
            cout << " " << "Ship destroy";
        }
        cout << endl;
    }
}