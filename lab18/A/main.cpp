#include "knight.hpp"

int main() {
    auto solution = findSolutionFor(8);
    if (!solution.empty()) {
        for (const auto& [row, col] : solution) {
            std::cout << "(" << row << ", " << col << ")\n";
        }
    } else {
        std::cout << "No solution found.\n";
    }
}