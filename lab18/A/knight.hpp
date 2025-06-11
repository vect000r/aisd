#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "graph.hpp"

std::vector<std::pair<int, int>> legalMovesFrom(int row, int col, int board_size);
int toVertex(int row, int col, int board_size);
std::pair<int, int> toCoord(int vertex, int board_size);
bool traverse(std::vector<int>& path, std::vector<bool>& visited, int current_vertex, int board_size);
std::vector<std::pair<int, int>> findSolutionFor(int board_size);


#endif