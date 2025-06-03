#include "graph.hpp"

void testDotFileGen(){
    
    Graph g(10);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);
    g.addVertex(6);
    g.addVertex(7);
    g.addVertex(8);
    g.addVertex(9);
    g.addVertex(10);

    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(3,4);
    g.addEdge(4,2);
    g.addEdge(5,6);
    g.addEdge(6,4);
    g.addEdge(7,1);
    g.addEdge(8,3);
    g.addEdge(9,5);

    g.generateDotFile("testgraph.dot");

}

void testSmallGraph() {
    Graph h(10);

    h.addVertex(1);
    h.addVertex(2);
    h.addVertex(3);

    h.addEdge(1, 2);
    h.addEdge(2, 3);
    h.addEdge(3, 1);

    h.generateDotFile("smallgraph.dot");
}




int main() {
    
    std::cout << "Generating dot file from example graph..." << std::endl;
    testDotFileGen();
    testSmallGraph();

    return 0;
}