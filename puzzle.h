//
// Created by Vlad Isan on 05/12/2023.
//

#ifndef PUZZLE_H
#define PUZZLE_H

#include <algorithm>
#include <array>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <ranges>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "fmt/core.h"

using GridRow = std::vector<int64_t>;
using Grid = std::vector<GridRow>;

struct Node {
    std::pair<int64_t, int64_t> position;
    int64_t distance;
    std::vector<int64_t> dir;
    int64_t dir_count;

    bool operator>(const Node &rhs) const {
        return this->distance > rhs.distance;
    }
};

struct NodeSeen {
    std::pair<int64_t, int64_t> position;
    std::vector<int64_t> dir;
    int64_t dir_count;

    bool operator<(const NodeSeen &other) const {
        if (this->position != other.position) {
            return position < other.position;
        }

        if (this->dir != other.dir) {
            return dir < other.dir;
        }

        return dir_count < other.dir_count;
    }
};

int puzzle_sample_1(const std::string &base_file_path);

int puzzle_sample_2(const std::string &base_file_path);

int puzzle_1(const std::string &base_file_path);

int puzzle_2(const std::string &base_file_path);

int do_puzzle_1(std::ifstream &file);

int do_puzzle_2(std::ifstream &file);

uint64_t dijkstra(const Grid &grid);
uint64_t dijkstra_2(const Grid &grid);

#endif //PUZZLE_H
