#include "Graph.h"
#include <algorithm>
#include <queue>
#include <fstream>
#include <thread>
#include <mutex>

Graph::Graph(const string& filename) {
    ifstream edges(filename);

    // Check if file opens successfully
    if (!edges.is_open()) {
        cerr << "Error opening file" << endl;
        exit(1);
    }

    // Identify the largest node ID in the input file
    int max_node = -1;
    int to, from;
    while (edges >> to >> from) {
        max_node = max(max_node, max(to, from));
    }

    // Resize the adjacency list based on the maximum node ID
    size_t new_size = static_cast<size_t>(max_node) + 1;
    graph.resize(new_size);

    // Rewind the input file and read the edges again
    edges.clear();
    edges.seekg(0, ios::beg);

    // Populate the adjacency list
    while (edges >> to >> from) {
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    edges.close();
}

void Graph::bfs(int start, vector<bool>& visited, vector<int>& component) {
    visited[start] = true;
    component.push_back(start);

    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        // Visit all unvisited neighbors of the current node
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                component.push_back(neighbor);
                q.push(neighbor);
            }
        }
    }
}

vector<vector<int>> Graph::find_components() {
    vector<vector<int>> components;
    vector<bool> visited(graph.size(), false);

    // Perform a BFS from every unvisited node
    for (size_t i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            vector<int> component;
            bfs(i, visited, component);
            components.push_back(component);
        }
    }

    return components;
}

void Graph::find_largest_component() {
    vector<vector<int>> components = find_components();
    int max_size = 0;
    int max_i = 0;

    // Find the largest component
    for (int i = 0; i < components.size(); i++) {
        if (components[i].size() > max_size) {
            max_size = components[i].size();
            max_i = i;
        }
    }

    largest_component = components[max_i];
}

int Graph::eccentricity(int node) {

    vector<int> dist(graph.size(), -1);
    dist[node] = 0;

    queue<int> q;
    q.push(node);

    // Perform BFS to find maximum distance from the given node
    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : graph[current]) {
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[current] + 1;
                q.push(neighbor);
            }
        }
    }

    // Return the maximum distance
    return *max_element(dist.begin(), dist.end());
}

void Graph::calculate_diameter_and_radius() {
    find_largest_component();

    int diameter = -1;
    int radius = -1;
    for (int node : largest_component) {
        int ecc = eccentricity(node);
        if (diameter == -1 || ecc > diameter) {
            diameter = ecc;
        }
        if (radius == -1 || ecc < radius) {
            radius = ecc;
        }
    }

    // Print the diameter and radius of the largest component of the graph
    cout << "Diam(K): " << diameter << endl;
    cout << "Rad(K): " << radius << endl;
}

void Graph::print_largest_component() {
    find_largest_component();

    // Print the size of the largest component
    cout << "The size of the largest component K on the graph G: " << largest_component.size() << endl;
}