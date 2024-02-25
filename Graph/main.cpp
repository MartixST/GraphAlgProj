#include "graph.h"

using namespace std;

int main() {
    string filename = "Graph.txt";

    // Create a Graph object using data from the input file
    Graph graph(filename);

    // Print the size of the graph's largest component
    graph.print_largest_component();

    // Calculate and print the diameter and radius of the graph's largest component
    graph.calculate_diameter_and_radius();

    return 0;
}