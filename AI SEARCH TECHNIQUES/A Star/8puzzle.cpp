#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

// Define the 8-puzzle state as a 3x3 vector
struct PuzzleState {
    vector<vector<int>> state;
    int x, y; // Position of the blank (0)
    int cost, level;
    string path;

    bool operator<(const PuzzleState& other) const {
        return (cost + level) > (other.cost + other.level);
    }
};

// Calculate Manhattan distance
int calculateManhattan(const vector<vector<int>>& current, const vector<vector<int>>& goal) {
    int distance = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (current[i][j] != 0) {
                for (int x = 0; x < 3; x++) {
                    for (int y = 0; y < 3; y++) {
                        if (current[i][j] == goal[x][y]) {
                            distance += abs(i - x) + abs(j - y);
                        }
                    }
                }
            }
        }
    }
    return distance;
}

// Check if the state is valid (within bounds)
bool isValid(int x, int y) {
    return x >= 0 && x < 3 && y >= 0 && y < 3;
}

// Print the 3x3 puzzle state
void printState(const vector<vector<int>>& state) {
    for (const auto& row : state) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << "- - -" << endl;
}

// Perform the A* algorithm
void solve8Puzzle(vector<vector<int>> start, vector<vector<int>> goal) {
    // Define possible moves for the blank space
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};

    priority_queue<PuzzleState> pq;
    map<vector<vector<int>>, bool> visited;

    int startX, startY;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (start[i][j] == 0) {
                startX = i;
                startY = j;
            }
        }
    }

    PuzzleState initial = {start, startX, startY, calculateManhattan(start, goal), 0, ""};
    pq.push(initial);

    while (!pq.empty()) {
        PuzzleState current = pq.top();
        pq.pop();

        if (current.state == goal) {
            cout << "Solution found with path: " << current.path <<" "<< endl;
            printState(current.state);
            return;
        }

        if (visited[current.state]) {
            continue;
        }
        visited[current.state] = true;

        for (int i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValid(newX, newY)) {
                vector<vector<int>> newState = current.state;
                swap(newState[current.x][current.y], newState[newX][newY]);

                if (!visited[newState]) {
                    int newCost = calculateManhattan(newState, goal);
                    pq.push({newState, newX, newY, newCost, current.level + 1, current.path + to_string(i)});
                }
            }
        }
    }

    cout << "No solution found." << endl;
}

int main() {
    vector<vector<int>> start = {
        {1, 3, 0},
        {4, 2, 6},
        {7, 5, 8}
    };

    vector<vector<int>> goal = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    solve8Puzzle(start, goal);
    return 0;
}

