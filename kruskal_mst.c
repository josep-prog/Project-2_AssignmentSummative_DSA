#include <stdio.h>
#include <stdlib.h>

// Simple struct for an edge
struct Edge {
    char from, to;
    int cost;
};

// For cycle detection
int parent[100];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY)
        parent[rootX] = rootY;
}

// Compare function for sorting edges by cost
int compare(const void *a, const void *b) {
    return ((struct Edge*)a)->cost - ((struct Edge*)b)->cost;
}

int main() {
    char hubs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    int hubCount = 7;

    // Graph as adjacency matrix with costs (from figure1.png)
    int graph[7][7] = {
        {0, 11, 0, 0, 0, 0, 22},
        {11, 0, 17, 0, 0, 0, 0},
        {0, 17, 0, 22, 0, 10, 0},
        {0, 0, 22, 0, 25, 0, 0},
        {0, 0, 0, 25, 0, 6, 0},
        {0, 0, 10, 0, 6, 0, 5},
        {22, 0, 0, 0, 0, 5, 0},
    };

    // Build the edge list from the adjacency matrix
    struct Edge edges[100];
    int edgeCount = 0;
    for (int i = 0; i < hubCount; i++) {
        for (int j = i + 1; j < hubCount; j++) {
            if (graph[i][j] != 0) {
                edges[edgeCount].from = hubs[i];
                edges[edgeCount].to = hubs[j];
                edges[edgeCount].cost = graph[i][j];
                edgeCount++;
            }
        }
    }

    // Initialize parent for union-find
    for (int i = 0; i < hubCount; i++)
        parent[i] = i;
    
    // Sort edges by cost (smallest first)
    qsort(edges, edgeCount, sizeof(struct Edge), compare);
    
    printf("Selected fiber-optic links for MST:\n");
    int totalCost = 0;
    int edgesUsed = 0;
    
    // Kruskal's algorithm
    for (int i = 0; i < edgeCount && edgesUsed < hubCount - 1; i++) {
        int u = edges[i].from - 'A';
        int v = edges[i].to - 'A';
        
        if (find(u) != find(v)) {
            unionSet(u, v);
            printf("%c -- %c  (cost %d)\n", edges[i].from, edges[i].to, edges[i].cost);
            totalCost += edges[i].cost;
            edgesUsed++;
        }
    }
    
    printf("\nTotal installation cost: %d million dollars\n", totalCost);
    return 0;
}
