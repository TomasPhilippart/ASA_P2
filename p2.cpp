#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>
#include <iostream>

#define INF 2147483647

using namespace std;

// capacities of the edges
int **capacity;

// how much flow has passed through an edge
int **flowPassed; 

// graph representation (adjacency list)
vector<int> *graph;

int *parent;
bool *visited;

int bfs(int source, int target) {

    for (int i = 0; i < target + 1; i++) {
        visited[i] = false;
        parent[i] = -1;
    }
    
    queue<int> q;
    q.push(source);
    visited[source] = true;

    int minFlow = INF;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // for every adjacent node
        for (size_t i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i];
            if (!visited[v]) {
                if (capacity[u][v] - flowPassed[u][v] > 0) {
                    parent[v] = u;
                    visited[v] = true;
                    
                    
                    if (v == target) {
                        while (v != source) { // backtrace to the source
                            minFlow = min(minFlow, capacity[parent[v]][v] - flowPassed[parent[v]][v]);
                            v = parent[v];
                        }
                        return minFlow;
                    }

                    q.push(v);
                }
            }
        }
    }
    return 0;
}


int edmonds_karp(int s, int t) {
    int maxFlow = 0;

    while(1) {
        // find augmenting path
        int flow = bfs(s, t);
        if (flow == 0) { 
            break;
        }

        maxFlow += flow;
        int current = t;
        // update the passed flow matrix
        while(current > 0) {
            int prev = parent[current];
            flowPassed[prev][current] += flow;
            flowPassed[current][prev] -= flow;
            current = prev;
        }
    }

    return maxFlow;
}

int main() {

    int n, k, i;
    cin >> n >> k;

    // Initialize data structures
    graph = new vector<int>[n+2];
    capacity = new int*[n+2];
    flowPassed = new int*[n+2];
    parent = new int[n+2];
    visited = new bool[n+2];
    
    for (i = 0; i < n+2; i++) {
        capacity[i] = new int[n+2];
        flowPassed[i] = new int[n+2];
    }

    for (i = 0; i < n+2; i++) {
        for (int j = 0; j < n+2; j++) {
            flowPassed[i][j] = 0;
        }
    }

    // Define x as the first index of the adjacency list and y and the end (source and target)
    int x = 0;
    int y = n + 1;

    int cost_xi, cost_yi, c_ij, j;

    for (i = 1; i <= n; i++) {
        cin >> cost_xi >> cost_yi;

        // X ---- cost_xi ----- pi
        graph[x].push_back(i);
        graph[i].push_back(x);

        capacity[x][i] = cost_xi;
        capacity[i][x] = cost_xi;

        // Y ---- cost_yi ----- pi
        graph[y].push_back(i);
        graph[i].push_back(y);

        capacity[i][y] = cost_yi;
        capacity[y][i] = cost_yi; 
    }

    for (int l = 0; l < k; l++) {
        cin >> i >> j >> c_ij;

        // i ---- c_ij ----- j
        graph[i].push_back(j);
        graph[j].push_back(i);

        capacity[i][j] = c_ij;
        capacity[j][i] = c_ij;
    }

    int maxFlow = edmonds_karp(x, y);
    cout << maxFlow << endl;

    return 0;
}
