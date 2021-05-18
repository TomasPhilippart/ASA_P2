#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>
#include <iostream>

#define MAXN 100 // maximum no. of nodes in graph
#define INF 2147483646

using namespace std;

// represents the capacities of the edges
int **capacity;
// shows how much flow has passed through an edge
int **flowPassed; 
// shows the maximum flow to a node in the path built by the BFS
int *path_flow;
// represents the graph and it may contain negative edges
vector<int> *graph;

int *parent;

int bfs(int s, int t) {
    queue<int> q;
    parent[s] = -2;
    q.push(s);
    path_flow[s] = INF;

    while(!q.empty()) {
        int current = q.front();
        q.pop();

        for (int i = 0; i < graph[current].size(); i++) {
            int to = graph[current][i];
            if (parent[to] == -1) { // Unvisited
                if (capacity[current][to] - flowPassed[current][to] > 0) {
                    // update parent node
                    parent[to] = current;
                    // check min residual edge capacity
                    path_flow[to] = min(path_flow[current], capacity[current][to] - flowPassed[current][to]);

                    if (to == t) {
                        return path_flow[t];
                    }
                    // add future node to queue
                    q.push(to);
                }
            }
        }
    }
    return 0;
}

int edmonds_karp(int s, int t) {
    int maxFlow = 0;
    while(1) {
        //ind an augmented path and max flow corresponding to it
        int flow = bfs(s, t);
        // if no path available, flow will be 0
        if (flow == 0) { 
            break;
        }

        maxFlow += flow;
        int current = t;
        // we update the passed flow matrix
        while(current != s) {
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

    graph = new vector<int>[n+2];
    capacity = new int*[n+2];
    flowPassed = new int*[n+2];
    for (i = 0; i < n+2; i++) {
        capacity[i] = new int[n+2];
        flowPassed[i] = new int[n+2];
    }
    path_flow = new int[n+2];
    parent = new int[n+2];
    for (int i = 0; i < n + 2; i++) {
        path_flow[i] = 0;
        parent[i] = -1; // -> unvisited
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
    cout << "Max flow: " << maxFlow << endl;

    return 0;
}