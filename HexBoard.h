#ifndef HEXBOARD_H
#define HEXBOARD_H

#include <algorithm>
#include <cmath>
#include <map>
#include <random>
#include <vector>

#include "HexCell.h"
#include "stack.h"

using std::map;
using std::pair;
using std::vector;
using namespace util;

class HexBoard {
public:
    // variables

    // Longest path distance from the centre to any cell.
    int longest_path_dist;

    // Radius of the maze
    int radius;

    // The start coordinate of the maze
    pair<int, int> start_coord;

    // The end coordinate of the maze
    pair<int, int> end_coord;

    // Solution of the maze. Contains pairs representing the path from the centre to the exit
    vector<pair<int, int>> solution;

    // A mapping from the coordinates of the cells to a pointer to the cell.
    map<pair<int, int>, HexCell*> cells;

    // functions
    HexBoard(int radius);


    void generate_maze(pair<int, int> start_coord, double branch_prob);

    void solve_maze();

    // Frees all dynamically allocated memory associated with the board.
    ~HexBoard();

private:
    void create_board();

    void configure_cells();

    vector<pair<int, int>> get_neigh_coords(const pair<int, int>& coord) const;

    HexCell* chooseNeighbour(HexCell* cell, const map<pair<int, int>, bool>& visited, double branch_prob) const;

    void rec_solve(HexCell* &curr_cell, vector<pair<int, int>> &curr_path, map<pair<int, int>, bool> &visited, Stack<vector<pair<int, int>>> &paths_stack);
};

#endif