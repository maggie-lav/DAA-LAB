#include <iostream>
#include <vector>
#include <queue>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Network {
    int nodeCount;
    vector<vector<int>> adjList;

public:
    Network(int n) {
        nodeCount = n;
        adjList.resize(n);
    }

    void addConnection(int a, int b) {
        adjList[a].push_back(b);
        adjList[b].push_back(a);   // Remove this for a directed graph
    }

    void depthFirstUtil(int current, vector<bool> &seen) {
        seen[current] = true;
        cout << current << " ";

        for (size_t i = 0; i < adjList[current].size(); i++) {
            int next = adjList[current][i];
            if (!seen[next])
                depthFirstUtil(next, seen);
        }
    }

    void depthFirstSearch(int source) {
        vector<bool> seen(nodeCount, false);
        depthFirstUtil(source, seen);
    }

    void breadthFirstSearch(int source) {
        vector<bool> seen(nodeCount, false);
        queue<int> pending;

        seen[source] = true;
        pending.push(source);

        while (!pending.empty()) {
            int curr = pending.front();
            pending.pop();

            cout << curr << " ";

            for (size_t i = 0; i < adjList[curr].size(); i++) {
                int nxt = adjList[curr][i];
                if (!seen[nxt]) {
                    seen[nxt] = true;
                    pending.push(nxt);
                }
            }
        }
    }
};

int main() {
    int nodes, links;

    cout << "Enter number of nodes: ";
    cin >> nodes;

    Network net(nodes);

    cout << "Enter number of links: ";
    cin >> links;

    cout << "Enter links (a b):" << endl;
    for (int i = 0; i < links; i++) {
        int a, b;
        cin >> a >> b;
        net.addConnection(a, b);
    }

    int source;
    cout << "Enter source node: ";
    cin >> source;

    // DFS timing
    auto dfsStart = high_resolution_clock::now();
    cout << endl << "DFS Traversal: ";
    net.depthFirstSearch(source);
    auto dfsEnd = high_resolution_clock::now();

    auto dfsDuration = duration_cast<nanoseconds>(dfsEnd - dfsStart);

    // BFS timing
    auto bfsStart = high_resolution_clock::now();
    cout << endl << endl << "BFS Traversal: ";
    net.breadthFirstSearch(source);
    auto bfsEnd = high_resolution_clock::now();

    auto bfsDuration = duration_cast<nanoseconds>(bfsEnd - bfsStart);

    cout << endl << endl << "Execution Time:";
    cout << endl << "DFS: " << dfsDuration.count() << " ns";
    cout << endl << "BFS: " << bfsDuration.count() << " ns";

    return 0;
}
