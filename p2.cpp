#include<bits/stdc++.h>
using namespace std;


// pair<int, int> pairs node name with weight.
typedef pair<int, int> vertex;

// AdjacencyListType is just a name for vector<list <vertex>>
// The outermost vector is initialized to size v here.
// Think of the outermost vector as the leftmost side or, column in the visual representation
// shown in the books. The inner list is linked list containing nodes and weights. The
// inner vector stores pair<int, int> in each of its slot. Where pair<int, int> is used to
// show the adjacent node and the weight between the nodes. Basically each of the boxes.
typedef vector<list <vertex>> AdjacencyListType;


// If there are no adjacent node "NONE" is printed.
// Now get the node name and the pair by accessing the first and second property.
// Since I have paired node name with weight so, the first is name and next one is the weight
void printCompleteAdjacencyList( AdjacencyListType &adjList, int &v ){

    for(int i = 0; i < adjList.size(); ++i){

        int adjNodes = adjList[i].size();
        printf("Adjacent of: %d", i);

        if(adjNodes > 0){
            list<vertex>::iterator it = adjList[i].begin();
            while(it != adjList[i].end()){
                printf(" -> %d (w:%d)", (*it).first, (*it).second);
                ++it;
            }
        }else{
            printf(" -> NONE");
        }

        printf("\n");
    }

}

// Makes undirected weighed pair (a, b) with cost w
void makePair(AdjacencyListType &adjList, int a, int b, int w) {
	adjList[a].push_back(make_pair(b, w));
	adjList[b].push_back(make_pair(a, w));
	printf("makePair(%d, %d, %d)\n", a, b, w);

}

int main(){

	// Input format:
	// n k (n - number of processes, k - number of entries different than 0 in the matrix of communication costs)
	// n lines:
	// 		Xi Yi (i ... n), (execution costs of process i in X and Y processors)
	// k lines:
	// 		i j c (i, j - identifiers of process i and j, c - cost of communication between i and j)

	int n, k;
	cin >> n >> k;

	// Create the adjacency list structure
    AdjacencyListType adjList(n + 2); // n processes + 2 processors (X and Y)
	
	int cost_xi, cost_yi, c_ij, i, j;

	// Define x as the first index of the adjacency list and y and the end (source and target)
	int x = 0;
	int y = n + 1;

	for (i = 1; i <= n; i++) {
		cin >> cost_xi >> cost_yi;
		makePair(adjList, x, i, cost_xi);
		makePair(adjList, i, y, cost_yi);
	}

	for (int l = 0; l < k; l++) {
		cin >> i >> j >> c_ij;
		makePair(adjList, i, j, c_ij);
	}

    // Show the complete adjacency list structure
    printf("\nWhole Adjacency List:\n");
    printCompleteAdjacencyList(adjList, y);

    return 0;
}