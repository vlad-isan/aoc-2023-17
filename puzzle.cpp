//
// Created by Vlad Isan on 05/12/2023.
//

#include "puzzle.h"

int puzzle_sample_1(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-sample-1.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_1(file);
}

int puzzle_sample_2(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-sample-2.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_2(file);
}

int puzzle_1(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-1.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_1(file);
}

int puzzle_2(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-2.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_2(file);
}

int do_puzzle_1(std::ifstream &file) {
    Grid grid;
    std::string line;

    while (std::getline(file, line)) {
        GridRow row;

        for (auto &c: line) {
            row.push_back(std::stoull(std::string{c}));
        }

        grid.push_back(row);
    }

    auto dist = dijkstra(grid);

    return dist;
}

int do_puzzle_2(std::ifstream &file) {
    std::string line;

    while (std::getline(file, line)) {
        fmt::println("{}", line);
    }

    return 0;
}

uint64_t dijkstra(const Grid &grid) {
    int n = grid.size();
    int m = grid[0].size();

    std::vector<std::vector<int64_t>> dist(n, std::vector<int64_t>(m, INT64_MAX));

    std::priority_queue<Node, std::vector<Node>, std::greater<>> pq;
    std::map<NodeSeen, bool> seen;

    dist[0][0] = 0;
    pq.push({std::make_pair(0, 0), 0, {0, 0}, 0});

    std::vector<std::vector<int64_t>> dirs = {{0,  1},
                                              {0,  -1},
                                              {1,  0},
                                              {-1, 0}};

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        int64_t i = node.position.first;
        int64_t j = node.position.second;

        NodeSeen seenNode{.position = node.position, .dir = node.dir, .dir_count = node.dir_count};

        if (seen.contains(seenNode)) {
            continue;
        }

        seen.insert({seenNode, true});

        if (i == n - 1 && j == m - 1) {
            return node.distance;
        }

        std::vector<std::vector<int64_t>> next_dirs{};

        if (node.dir_count < 3) {
            next_dirs.push_back(node.dir);
        }

        for (auto &dir: dirs) {
            if (node.dir[0] == -dir[0] && node.dir[1] == -dir[1]) {
                continue;
            }

            if (node.dir == dir) {
                continue;
            }

            next_dirs.push_back(dir);
        }

        for (auto &dir: next_dirs) {
            // Don't allow to reverse direction
            if (node.dir[0] == -dir[0] && node.dir[1] == -dir[1]) {
                continue;
            }

            // Don't allow to move in the same direction more than 3 times
            if (node.dir == dir && node.dir_count == 3) {
                continue;
            }

            int64_t x = i + dir[0];
            int64_t y = j + dir[1];

            if (x >= 0 && x < n && y >= 0 && y < m) {
                pq.push({.position = {x, y}, .distance = node.distance + grid[x][y], .dir = dir, .dir_count = node.dir == dir ?
                                                                                              node.dir_count + 1 : 1});
            }
        }
    }

    return 0;
}
