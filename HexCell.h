#ifndef HEXCELL_H
#define HEXCELL_H

#include <vector>

#include "util/RGBAPixel.h"

// Sides
const int N = 0;
const int NE = 1;
const int SE = 2;
const int S = 3;
const int SW = 4;
const int NW = 5;

class HexCell {
public:
    // Axial coordinates of the cell
    int q, r;

    // Path distance between the cell and the start coordinate in the maze
    int path_dist_from_start;

    // Neighbours are adjacent cells
    HexCell* neighbours[6];

    // Links are connected neighbours, i.e. there are no walls between them
    HexCell* links[6];

    HexCell(int Q, int R);

    void link(HexCell* cell);

    int get_neighbour_side(const HexCell* cell) const;

    bool is_linked(const HexCell* cell) const;

    int distance(const HexCell* cell) const;

    bool is_edge() const;
};

#endif