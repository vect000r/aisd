#include "graph.hpp"
#include <cassert>
#include <algorithm>
#include <iostream>

void testGraph() {
    Graph g(5);
    g.addEdge(1, 2);
    g.addEdge(3, 4);
    
    assert(g.adjacent(1, 2) == true);
    assert(g.adjacent(3, 4) == true);
    assert(g.adjacent(2, 1) == false);
    assert(g.adjacent(4, 3) == false);
    assert(g.adjacent(1, 3) == false);
    assert(g.adjacent(0, 1) == false);
    assert(g.adjacent(1, 1) == false);
    std::cout << "Test adjacent() passed!" << std::endl;

    Graph g2(5);
    g2.addEdge(1, 2);
    g2.addEdge(1, 3);
    g2.addEdge(1, 4);
    g2.addEdge(2, 1);
    
    std::vector<int> n1 = g2.neighbours(1);
    std::sort(n1.begin(), n1.end());
    assert(n1.size() == 3);
    assert(n1[0] == 2);
    assert(n1[1] == 3);
    assert(n1[2] == 4);
    
    std::vector<int> n0 = g2.neighbours(0);
    assert(n0.size() == 0);
    
    std::vector<int> n2 = g2.neighbours(2);
    assert(n2.size() == 1);
    assert(n2[0] == 1);
    std::cout << "Test neighbours() passed!" << std::endl;

    Graph g3(5);
    assert(g3.getVertexValue(0) == 0);
    assert(g3.getVertexValue(1) == 0);
    
    g3.setVertexValue(0, 10);
    g3.setVertexValue(1, -5);
    
    assert(g3.getVertexValue(0) == 10);
    assert(g3.getVertexValue(1) == -5);
    assert(g3.getVertexValue(2) == 0);
    std::cout << "Test getVertexValue() and setVertexValue() passed!" << std::endl;

    Graph g4(5);
    g4.addEdge(1, 2);
    
    assert(g4.getEdgeValue(1, 2) == 0);
    
    g4.setEdgeValue(1, 2, 15);
    assert(g4.getEdgeValue(1, 2) == 15);
    
    g4.setEdgeValue(1, 2, 20);
    assert(g4.getEdgeValue(1, 2) == 20);
    std::cout << "Test getEdgeValue() and setEdgeValue() passed!" << std::endl;

    Graph g5(4);
    assert(g5.adjacent(0, 1) == false);
    g5.addEdge(0, 1);
    assert(g5.adjacent(0, 1) == true);
    assert(g5.adjacent(1, 0) == false);
    
    g5.addEdge(2, 3);
    assert(g5.adjacent(2, 3) == true);
    
    g5.addEdge(0, 0);
    assert(g5.adjacent(0, 0) == true);
    std::cout << "Test addEdge() passed!" << std::endl;

    Graph g6(4);
    g6.addEdge(0, 1);
    g6.addEdge(1, 2);
    g6.addEdge(2, 3);
    
    assert(g6.adjacent(0, 1) == true);
    g6.removeEdge(0, 1);
    assert(g6.adjacent(0, 1) == false);
    assert(g6.adjacent(1, 0) == false);
    
    assert(g6.adjacent(1, 2) == true);
    assert(g6.adjacent(2, 3) == true);
    std::cout << "Test removeEdge() passed!" << std::endl;

    Graph g7(3);
    g7.addEdge(0, 1);
    g7.setVertexValue(0, 5);
    
    int oldSize = g7.size();
    g7.addVertex(0);
    assert(g7.size() == oldSize + 1);
    assert(g7.getVertexValue(g7.size() - 1) == 0);
    assert(g7.adjacent(0, 1) == true);
    assert(g7.adjacent(0, g7.size() - 1) == false);
    
    g7.addVertex(42);
    assert(g7.getVertexValue(g7.size() - 1) == 42);
    std::cout << "Test addVertex() passed!" << std::endl;

    Graph g8(5);
    g8.addEdge(0, 1);
    g8.addEdge(1, 2);
    g8.addEdge(2, 3);
    g8.addEdge(3, 4);
    g8.setVertexValue(1, 10);
    g8.setVertexValue(2, 20);
    g8.setVertexValue(3, 30);
    
    int oldSize2 = g8.size();
    g8.removeVertex(1);
    assert(g8.size() == oldSize2 - 1);
    
    assert(g8.getVertexValue(1) == 20);
    assert(g8.getVertexValue(2) == 30);
    assert(g8.adjacent(1, 2) == true);
    assert(g8.adjacent(2, 3) == true);
    std::cout << "Test removeVertex() passed!" << std::endl;
}

int main() {
    testGraph();
    return 0;
}