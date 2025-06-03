#include "graph.hpp"
#include <cassert>

void testListGraph() {
    std::cout << "Testing constructor and size..." << std::endl;
    Graph g(3);
    assert(g.size() == 3);
    
    std::cout << "Testing addVertex..." << std::endl;
    g.addVertex();
    assert(g.size() == 4);
    g.addVertex();
    g.addVertex();
    assert(g.size() == 6);
    
    std::cout << "Testing addEdge..." << std::endl;
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    assert(g.adjacent(0, 1) == true);
    assert(g.adjacent(1, 2) == true);
    assert(g.adjacent(2, 0) == true);
    assert(g.adjacent(1, 0) == false);
    
    std::cout << "Testing neighbours..." << std::endl;
    std::vector<int> neighbours0 = g.neighbours(0);
    assert(neighbours0.size() == 1);
    assert(neighbours0[0] == 1);
    
    std::vector<int> neighbours1 = g.neighbours(1);
    assert(neighbours1.size() == 1);
    assert(neighbours1[0] == 2);
    
    std::cout << "Testing duplicate edge prevention..." << std::endl;
    g.addEdge(0, 1);
    neighbours0 = g.neighbours(0);
    assert(neighbours0.size() == 1);
    
    std::cout << "Testing removeEdge..." << std::endl;
    g.removeEdge(0, 1);
    assert(g.adjacent(0, 1) == false);
    neighbours0 = g.neighbours(0);
    assert(neighbours0.size() == 0);
    
    std::cout << "Testing vertex values..." << std::endl;
    assert(g.getVertexValue(0) == 0);
    g.setVertexValue(0, 42);
    assert(g.getVertexValue(0) == 42);
    g.setVertexValue(1, 100);
    assert(g.getVertexValue(1) == 100);
    
    std::cout << "Testing edge values..." << std::endl;
    assert(g.getEdgeValue(0, 1) == 0);
    g.setEdgeValue(0, 1, 25);
    assert(g.getEdgeValue(0, 1) == 25);
    g.setEdgeValue(1, 0, 50);
    assert(g.getEdgeValue(1, 0) == 50);
    assert(g.getEdgeValue(0, 1) == 25);
    
    std::cout << "Testing bounds checking for adjacent..." << std::endl;
    assert(g.adjacent(-1, 0) == false);
    assert(g.adjacent(0, -1) == false);
    assert(g.adjacent(10, 0) == false);
    assert(g.adjacent(0, 10) == false);
    
    std::cout << "Testing bounds checking for neighbours..." << std::endl;
    std::vector<int> invalid_neighbours = g.neighbours(-1);
    assert(invalid_neighbours.size() == 0);
    invalid_neighbours = g.neighbours(10);
    assert(invalid_neighbours.size() == 0);
    
    std::cout << "Testing bounds checking for vertex values..." << std::endl;
    assert(g.getVertexValue(-1) == 0);
    assert(g.getVertexValue(10) == 0);
    g.setVertexValue(-1, 999);
    g.setVertexValue(10, 999);
    assert(g.getVertexValue(-1) == 0);
    assert(g.getVertexValue(10) == 0);
    
    std::cout << "Testing bounds checking for edge values..." << std::endl;
    assert(g.getEdgeValue(-1, 0) == 0);
    assert(g.getEdgeValue(0, -1) == 0);
    assert(g.getEdgeValue(10, 0) == 0);
    assert(g.getEdgeValue(0, 10) == 0);
    g.setEdgeValue(-1, 0, 999);
    g.setEdgeValue(0, -1, 999);
    g.setEdgeValue(10, 0, 999);
    g.setEdgeValue(0, 10, 999);
    assert(g.getEdgeValue(-1, 0) == 0);
    assert(g.getEdgeValue(0, -1) == 0);
    assert(g.getEdgeValue(10, 0) == 0);
    assert(g.getEdgeValue(0, 10) == 0);
    
    std::cout << "Testing bounds checking for addEdge..." << std::endl;
    int initial_size = g.neighbours(0).size();
    g.addEdge(-1, 0);
    g.addEdge(0, -1);
    g.addEdge(10, 0);
    g.addEdge(0, 10);
    assert(g.neighbours(0).size() == initial_size);
    
    std::cout << "Testing removeVertex..." << std::endl;
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 1);
    g2.addEdge(3, 1);
    g2.setVertexValue(1, 777);
    
    g2.removeVertex(1);
    assert(g2.adjacent(0, 1) == false);
    assert(g2.adjacent(2, 1) == false);
    assert(g2.adjacent(3, 1) == false);
    assert(g2.neighbours(1).size() == 0);
    assert(g2.getVertexValue(1) == 0);
    assert(g2.getEdgeValue(0, 1) == 0);
    assert(g2.getEdgeValue(1, 0) == 0);
    
    std::cout << "Testing bounds checking for removeVertex..." << std::endl;
    g2.removeVertex(-1);
    g2.removeVertex(10);
    assert(g2.size() == 4);
    
    std::cout << "Testing self-loops..." << std::endl;
    Graph g3(2);
    g3.addEdge(0, 0);
    assert(g3.adjacent(0, 0) == true);
    g3.removeEdge(0, 0);
    assert(g3.adjacent(0, 0) == false);
    
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    testListGraph();
    return 0;
}