#include "graph.hpp"
#include "knight.hpp"
#include <vector>
#include <utility>
#include <optional>

std::vector<std::pair<int, int>> legalMovesFrom(int row, int col, int board_size) {
    std::vector<std::pair<int, int>> moves;
    std::vector<std::pair<int, int>> offsets = {
        {-1, -2}, { 1, -2},
        {-2, -1}, { 2, -1},
        {-2,  1}, { 2,  1},
        {-1,  2}, { 1,  2}
    };

    for (const auto& offset : offsets) {
        int move_row = row + offset.first;
        int move_col = col + offset.second;
        if (0 <= move_row && move_row < board_size &&
            0 <= move_col && move_col < board_size) {
            moves.emplace_back(move_row, move_col);
        }
    }
    return moves;
}

// Helper to convert (row, col) to vertex index
int toVertex(int row, int col, int board_size) {
    return row * board_size + col;
}

// Helper to convert vertex index to (row, col)
std::pair<int, int> toCoord(int vertex, int board_size) {
    return {vertex / board_size, vertex % board_size};
}

bool traverse(std::vector<int>& path, std::vector<bool>& visited, int current_vertex, int board_size) {
    int total_squares = board_size * board_size;
    if (path.size() == total_squares) {
        return true;
    }
    auto [row, col] = toCoord(current_vertex, board_size);
    for (auto [next_row, next_col] : legalMovesFrom(row, col, board_size)) {
        int next_vertex = toVertex(next_row, next_col, board_size);
        if (!visited[next_vertex]) {
            visited[next_vertex] = true;
            path.push_back(next_vertex);
            if (traverse(path, visited, next_vertex, board_size)) {
                return true;
            }
            path.pop_back();
            visited[next_vertex] = false;
        }
    }
    return false;
}

std::vector<std::pair<int, int>> findSolutionFor(int board_size) {
    int total_squares = board_size * board_size;
    std::vector<int> path;
    std::vector<bool> visited(total_squares, false);

    // Start from (0, 0)
    int start_vertex = 0;
    path.push_back(start_vertex);
    visited[start_vertex] = true;

    if (traverse(path, visited, start_vertex, board_size)) {
        std::vector<std::pair<int, int>> result;
        for (int v : path) {
            result.push_back(toCoord(v, board_size));
        }
        return result;
    } else {
        return {}; // No solution found
    }
}