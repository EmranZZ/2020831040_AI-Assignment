#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// Definition of a Node representing a location in the graph
struct Node {
    char name;  // Node identifier
    int cost;   // Cost to reach this node

    Node(char n, int c) : name(n), cost(c) {}

    // Overloading the greater-than operator for priority_queue
    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

// Definition of a Graph class to represent the connectivity between nodes
class Graph {
public:
    unordered_map<char, vector<pair<char, int>>> adjacencyList;

    // Function to add an undirected edge between two nodes with a given cost
    void addEdge(char from, char to, int cost) {
        adjacencyList[from].push_back({to, cost});
        adjacencyList[to].push_back({from, cost});
    }

    // Function to perform Uniform Cost Search from a start node to a goal node
    int uniformCostSearch(char start, char goal) {
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        unordered_map<char, int> visited;

        pq.push({start, 0});

        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();

            if (current.name == goal) {
                return current.cost;
            }

            if (visited.find(current.name) != visited.end()) {
                continue;
            }

            visited[current.name] = current.cost;

            for (const auto& neighbor : adjacencyList[current.name]) {
                if (visited.find(neighbor.first) == visited.end()) {
                    pq.push({neighbor.first, current.cost + neighbor.second});
                }
            }
        }

        return -1; 
    }
};

// Main function demonstrating the usage of the Graph class
int main() {
    // Create a Graph instance and add edges to represent the tree structure
    Graph graph;
    graph.addEdge('S', 'G', 12);
    graph.addEdge('S', 'A', 1);
    graph.addEdge('A', 'B', 3);
    graph.addEdge('A', 'C', 1);
    graph.addEdge('B', 'D', 3);
    graph.addEdge('C', 'D', 1);
    graph.addEdge('C', 'G', 2);
    graph.addEdge('D', 'G', 3);

    // Specify the start and goal nodes
    char start = 'S';
    char goal = 'G';

    // Perform Uniform Cost Search and display the result
    int result = graph.uniformCostSearch(start, goal);

    if (result != -1) {
        cout << "Minimum cost from " << start << " to " << goal << " is: " << result << endl;
    } else {
        cout << "Goal " << goal << " is not reachable from " << start << endl;
    }

    return 0;
}
