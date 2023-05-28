#ifndef DRAWMAZE_H
#define DRAWMAZE_H

#include <algorithm>
#include <cmath>
#include <map>
#include <vector>

#include "HexBoard.h"
#include "util/PNG.h"

using std::pair;
using std::vector;
using namespace util;

struct MazeParams {
    double a_size;
    double b_size;
    double height;
};

struct CellParams {
    double cx;
    double cy;
    int x_fw;
    int x_nw;
    int x_ne;
    int x_fe;
    int y_n;
    int y_m;
    int y_s;
};

namespace DrawMaze {
    MazeParams get_draw_params(int size);
    CellParams get_cell_params(int size, int maze_radius, MazeParams maze_params, HexCell* cell);

    PNG draw_maze(const HexBoard& maze, int size, string colour_mode);

    PNG draw_solution(const HexBoard& maze, int size, string colour_mode);

    pair<int, int> axial_to_offset(pair<int, int> axial_coord);

    vector<RGBAPixel> spectrum(int n);
};

#endif