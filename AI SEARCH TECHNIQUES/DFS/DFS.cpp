#include <iostream>
#include <vector>
using namespace std;

const int N = 100;
vector<int> g[N];
bool visited[N];
vector<int> path;

// Simple DFS function to find the goal node
bool dfs(int vertex, int goalNode) {
    visited[vertex] = true;  // Mark the current node as visited
    path.push_back(vertex);  // Add the current node to the path

    // Check if we reached the goal node
    if (vertex == goalNode) return true;

    // Visit all unvisited neighbors
    for (int child : g[vertex]) {
        if (!visited[child]) {
            // Recursively call dfs on the child node
            if (dfs(child, goalNode)) return true; // If goal is found, return true
        }
    }

    // Backtrack if the goal is not found in this path
    path.pop_back();
    return false;
}


int main() {
    int node, edge;
    cout << "Enter number of nodes and edges: ";
    cin >> node >> edge;

    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < edge; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int goalNode;
    cout << "Enter goal node: ";
    cin >> goalNode;

    if (dfs(1, goalNode)) {  // Start DFS from node 1
        cout << "Path to goal node " << goalNode << ": ";
        for (int v : path) {
            cout << v << " ";
        }
        cout << endl;
    } else {
        cout << "Goal node " << goalNode << " not found in the graph." << endl;
    }

    return 0;
}