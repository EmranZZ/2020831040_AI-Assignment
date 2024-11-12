#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Node structure to represent a state in the search tree
struct Node {
    int state;
    Node* parent;

    Node(int s, Node* p = nullptr) : state(s), parent(p) {}
};

// Function to perform Depth-Limited Search
Node* depthLimitedSearch(int start, int goal, int depthLimit) {
    stack<Node*> nodeStack;
    nodeStack.push(new Node(start));

    while (!nodeStack.empty()) {
        Node* current = nodeStack.top();
        nodeStack.pop();

        if (current->state == goal) {
            return current;  // Goal found
        }

        if (current->state < depthLimit) {
            // Generate and push successors onto the stack
            for (int successor : getSuccessors(current->state)) {
                nodeStack.push(new Node(successor, current));
            }
        }
    }

    return nullptr;  // Goal not found within depth limit
}

// Function to get successors of a state (replace this with your specific logic)
vector<int> getSuccessors(int state) {
    // Replace this function with your logic to generate successors based on the current state
    // It should return a vector of possible successor states.
    // Example: return {state1, state2, ...};
    return {};
}

int main() {
    int startState = 1;
    int goalState = 10;
    int depthLimit = 5;

    Node* result = depthLimitedSearch(startState, goalState, depthLimit);

    if (result != nullptr) {
        // Print the path from the start state to the goal state
        vector<int> path;
        while (result != nullptr) {
            path.insert(path.begin(), result->state);
            result = result->parent;
        }

        cout << "Path from start to goal: ";
        for (int state : path) {
            cout << state << " ";
        }
        cout << endl;
    } else {
        cout << "Goal not found within the depth limit." << endl;
    }

    return 0;
}
