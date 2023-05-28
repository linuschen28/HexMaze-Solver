#include "HexBoard.h"

#include <iostream>

#include "queue.h"
#include "stack.h"

HexBoard::HexBoard(int radius) {
    longest_path_dist = 0;
    this->radius = radius;
    create_board();
    configure_cells();
}

void HexBoard::create_board() {
    int max_dist = radius - 1;
    int num_cells = 6 * ((max_dist * (max_dist + 1))/2) + 1;
    int q = max_dist;
    int r;
    int column_size = ((2 * max_dist) + 1) - max_dist;

    while (num_cells > 0) {
        while (q >= 0) {
            r = -max_dist;
            for (int c = r; c < r + column_size; c++) {
                HexCell* cell = new HexCell(q, c);
                pair<int, int> coord (q, c);
                cells.insert({coord, cell});
                num_cells--;
                // if (num_cells == 0) return;
            }
            q--;
            column_size++;
        }
        column_size -= 2;
        while (q >= -max_dist) {
            r = max_dist;
            for (int c = r; c > r - column_size; c--) {
                HexCell* cell = new HexCell(q, c);
                pair<int, int> coord (q, c);
                cells.insert({coord, cell});
                num_cells--;
                // if (num_cells == 0) return;
            }
            q--;
            column_size--;
        }
    }
}

void HexBoard::configure_cells() {
    for (auto kv : cells) {
        int kv_q = kv.second->q;
        int kv_r = kv.second->r;
        // N
        for (auto n : cells) {
            if (n.second->q == kv_q && n.second->r == kv_r - 1) {
                kv.second->neighbours[N] = n.second;
            }
        }
        // NE
        for (auto ne : cells) {
            if (ne.second->q == kv_q + 1 && ne.second->r == kv_r - 1) {
                kv.second->neighbours[NE] = ne.second;
            }
        }
        // SE
        for (auto se : cells) {
            if (se.second->q == kv_q + 1 && se.second->r == kv_r) {
                kv.second->neighbours[SE] = se.second;
            }
        }
        // S
        for (auto s : cells) {
            if (s.second->q == kv_q && s.second->r == kv_r + 1) {
                kv.second->neighbours[S] = s.second;
            }
        }
        // SW
        for (auto sw : cells) {
            if (sw.second->q == kv_q - 1 && sw.second->r == kv_r + 1) {
                kv.second->neighbours[SW] = sw.second;
            }
        }
        // NW
        for (auto nw : cells) {
            if (nw.second->q == kv_q - 1 && nw.second->r == kv_r) {
                kv.second->neighbours[NW] = nw.second;
            }
        }
    }
}

void HexBoard::generate_maze(pair<int, int> start_coord, double branch_prob) {
    this->start_coord = start_coord;
    // this.end_coord = ...;
    longest_path_dist = 0;

    Stack<pair<int, int>> stack;

    stack.push(start_coord);

    map<pair<int, int>, bool> visited;
    visited.insert({start_coord, true});

    HexCell* cell;

    int path_acc = 0;

    while (!stack.isEmpty()) {
        pair<int, int> curr_cell = stack.peek();

        if (cells.find(curr_cell) == cells.end()) {
            // do smth ???
        } else {
            cell = cells[curr_cell];
        }

        HexCell* neigh_cell = chooseNeighbour(cell, visited, branch_prob);

        if (neigh_cell != nullptr) {
            cell->link(neigh_cell);
            pair<int, int> neigh_coord = {neigh_cell->q, neigh_cell->r};
            visited.insert({neigh_coord, true});

            neigh_cell->path_dist_from_start = cell->path_dist_from_start + 1;

            if (neigh_cell->path_dist_from_start > longest_path_dist) {
                longest_path_dist = neigh_cell->path_dist_from_start;
            }

            if (neigh_cell->is_edge() && neigh_cell->path_dist_from_start > path_acc) {
                    path_acc = neigh_cell->path_dist_from_start;
                    end_coord = neigh_coord;
            }

            stack.push(neigh_coord); 
        } else {
            stack.pop();
        }
    }


}

void HexBoard::solve_maze() {
    // initialize curr_cell to HexCell with start coord
    HexCell* curr_cell = cells[start_coord];

    // curr_path is the current path we are on
    vector<pair<int, int>> curr_path;
    // add start_coord to curr_path
    curr_path.push_back(start_coord);

    // all visited coords
    map<pair<int, int>, bool> visited;

    Stack<vector<pair<int, int>>> paths_stack;

    rec_solve(curr_cell, curr_path, visited, paths_stack);
}

void HexBoard::rec_solve(HexCell* &curr_cell, vector<pair<int, int>> &curr_path, map<pair<int, int>, bool> &visited, Stack<vector<pair<int, int>>> &paths_stack) {
    // initialize curr_cell_coord to start coord
    pair<int, int> curr_cell_coord = {curr_cell->q, curr_cell->r};
    
    if (curr_cell_coord != end_coord) {
        // set current cell coord as visited
        visited.insert({curr_cell_coord, true});
        // find number of paths from that cell
        int num_paths = 0;
        for (HexCell* c : curr_cell->links) {
            if (c != nullptr) num_paths++;
        }

        if (num_paths == 2 || curr_cell_coord == start_coord) {
            // single path case
            for (HexCell* p : curr_cell->links) {
                
                if (p != nullptr && visited.find({p->q, p->r}) == visited.end()) {
                    curr_path.push_back({p->q, p->r});
                    rec_solve(p, curr_path, visited, paths_stack);
                }
            }
        } else if (num_paths < 2) {
            vector<pair<int, int>> new_path = paths_stack.pop();
            pair<int, int> temp_coord = new_path.back();
            HexCell* temp_cell = cells[temp_coord];
            rec_solve(temp_cell, new_path, visited, paths_stack); // stack pop
        } else {
            // multi path stack case
            for (HexCell* p : curr_cell->links) {
                if (p != nullptr && visited.find({p->q, p->r}) == visited.end()) {
                    // make temp_path the current path + one cell into the possible path
                    curr_path.push_back({p->q, p->r});
                    vector<pair<int, int>> temp_path = curr_path;
                    curr_path.pop_back();
                    // add temp_path to the stack
                    paths_stack.push(temp_path);
                }
            }
            vector<pair<int, int>> new_path = paths_stack.pop();
            pair<int, int> temp_coord = new_path.back();
            HexCell* temp_cell = cells[temp_coord];
            rec_solve(temp_cell, new_path, visited, paths_stack); // stack pop
        }
    } else {
        solution = curr_path;
    }
}