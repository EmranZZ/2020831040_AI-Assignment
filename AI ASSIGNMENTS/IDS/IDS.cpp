#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Node {
    int state;
    Node* parent;

    Node(int s, Node* p = nullptr) : state(s), parent(p) {}
};

vector<int> get_successors(int state) {
    // Replace this function with your logic to generate successors based on the current state
    // It should return a vector of possible successor states.
    // Example: return {state1, state2, ...};
    return {};
}

Node* depth_limited_search(Node* node, int goal, int depth_limit) {
    if (node->state == goal) {
        return node;
    } else if (depth_limit == 0) {
        return nullptr;
    } else {
        for (int child_state : get_successors(node->state)) {
            Node* child_node = new Node(child_state, node);
            Node* result = depth_limited_search(child_node, goal, depth_limit - 1);
            if (result != nullptr) {
                return result;
            }
            delete child_node;
        }
        return nullptr;
    }
}

Node* iterative_deepening_search(int start, int goal) {
    int depth_limit = 0;
    while (true) {
        Node* result = depth_limited_search(new Node(start), goal, depth_limit);
        if (result != nullptr) {
            return result;
        }
        depth_limit++;
    }
}

int main() {
    // Example usage:
    int start_state = 1;
    int goal_state = 10;

    Node* result_node = iterative_deepening_search(start_state, goal_state);

    if (result_node != nullptr) {
        // Reconstruct and print the path
        vector<int> path;
        Node* current_node = result_node;
        while (current_node != nullptr) {
            path.insert(path.begin(), current_node->state);
            current_node = current_node->parent;
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
