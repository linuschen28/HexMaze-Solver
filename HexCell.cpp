#include "HexCell.h"

#include <cmath>

HexCell::HexCell(int Q, int R) {
    q = Q;
    r = R;
    path_dist_from_start = 0;
    for (int i = 0; i < 6; i++) {
        neighbours[i] = nullptr;
        links[i] = nullptr;
    }
}

void HexCell::link(HexCell* cell) {
    if (cell == nullptr) {
        return;
    }

    if (distance(cell) == 1) {
        int q_this = q;
        int r_this = r;
        int q_cell = cell->q;
        int r_cell = cell->r;
        int i;

        if (q_cell > q_this) {
            // 1 or 2
            if (r_this == r_cell) {
                i = 2;
            } else {
                i = 1;
            }
        } else if (q_this == q_cell) {
            // 0 or 3
            if (r_this > r_cell) {
                i = 0;
            } else {
                i = 3;
            }
        } else {
            // 4 or 5
            if (r_this == r_cell) {
                i = 5;
            } else {
                i = 4;
            }
        }

        links[i] = cell;
        if (i > 2) {
            cell->links[i - 3] = this;
        } else {
            cell->links[i + 3] = this;
        }
    }
}

int HexCell::get_neighbour_side(const HexCell* cell) const {
    for (int i = 0; i < 6; i++) {
        if (cell == neighbours[i]) {
            return i;
        }
    }
}

bool HexCell::is_linked(const HexCell* cell) const {
    if (cell == nullptr) return false;
    for (int i = 0; i < 6; i++) {
        if (cell == links[i]) return true;
    }
    return false;
}

int HexCell::distance(const HexCell* cell) const {
    if (cell == nullptr) {
        return -1;
    }

    int q1 = q;
    int r1 = r;
    
    int q2 = cell->q;
    int r2 = cell->r;
    int s2 = 0;

    q2 = q2 - q1;
    r2 = r2 - r1;
    s2 = -q2 -r2;

    int dist = fmax( abs(q2) , fmax( abs(r2), abs (s2)));
    
    return dist;
}

bool HexCell::is_edge() const {
    for (int i = 0; i < 6; i++) {
        if (neighbours[i] == nullptr) {
            return true;
        }
    }
    return false;
}