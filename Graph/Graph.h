#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * @class Graph
 * @brief Graph class to represent undirected graph, finds connected components, largest component, and calculates diameter and radius
 */
class Graph {
private:
    vector<vector<int>> graph; ///< @brief Adjacency list representation of graph
    vector<int> largest_component; ///< @brief Vector to store largest component of the graph

    /**
     * @brief Performs Breadth First Search on the graph from a given start node
     * @param start The start node for BFS
     * @param visited Visited nodes vector
     * @param component Vector to store component nodes
     */
    void bfs(int start, vector<bool>& visited, vector<int>& component);

    /**
     * @brief Finds and returns all connected components of the graph
     * @return vector of connected components
     */
    vector<vector<int>> find_components();

    /**
     * @brief Calculates and returns the eccentricity of a given node
     * @param node Node to calculate the eccentricity
     * @return Eccentricity of the node
     */
    int eccentricity(int node);

public:
    /**
     * @brief Constructor that initializes graph from an input file
     * @param filename Name of the input file
     */
    Graph(const string& filename);

    /**
     * @brief Finds the largest component of the graph
     */
    void find_largest_component();

    /**
     * @brief Calculates and prints the diameter and radius of the largest component
     */
    void calculate_diameter_and_radius();

    /**
     * @brief Prints the largest component of the graph
     */
    void print_largest_component();
};