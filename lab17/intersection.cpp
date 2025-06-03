#include "graph.hpp"

int main(){
    Graph intersectionGraph(5);
    intersectionGraph.addVertex(1);
    intersectionGraph.addVertex(2);
    intersectionGraph.addVertex(3);
    intersectionGraph.addVertex(4);
    intersectionGraph.addVertex(5);
    intersectionGraph.addEdge(1, 2);
    intersectionGraph.addEdge(1, 3);
    intersectionGraph.addEdge(1, 4);
    intersectionGraph.addEdge(2, 1);
    intersectionGraph.addEdge(2, 3);
    intersectionGraph.addEdge(2, 4);
    intersectionGraph.addEdge(4, 1);
    intersectionGraph.addEdge(4, 2);
    intersectionGraph.addEdge(4, 3);
    intersectionGraph.addEdge(5, 1);
    intersectionGraph.addEdge(5, 2);
    intersectionGraph.addEdge(5, 3);
    intersectionGraph.addEdge(5, 4);

    intersectionGraph.generateDotFile("intersection_graph.dot");
}
