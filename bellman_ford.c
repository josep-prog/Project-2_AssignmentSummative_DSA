#include <stdio.h>
#include <limits.h>

#define MAX_NODES 26
#define MAX_EDGES 100

struct Edge {
    char from, to;
    int cost;
};

// Recursively print the path from Branch A to the given node using prev[]
void printPath(char prev[], int node) {
    if (prev[node] == -1) {
        printf("%c", 'A' + node);
        return;
    }
    printPath(prev, prev[node] - 'A');
    printf(" -> %c", 'A' + node);
}

int main() {
    struct Edge edges[] = {
        {'A', 'B', 5},
        {'A', 'C', 3},
        {'B', 'D', 2},
        {'C', 'B', 1},
        {'C', 'D', 4},
        {'D', 'E', -2},
        {'E', 'B', 1},
    };
    int edgeCount = 7;
    int nodeCount = 5;
    int dist[MAX_NODES];
    char prev[MAX_NODES];  // to store path
    
    // Step 1: Initialize distances (A=0, others=infinity)
    for (int i = 0; i < nodeCount; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[0] = 0;  // A = index 0
    
    // Step 2: Relax edges (nodeCount - 1 times)
    for (int i = 0; i < nodeCount - 1; i++) {
        for (int j = 0; j < edgeCount; j++) {
            int u = edges[j].from - 'A';
            int v = edges[j].to - 'A';
            int w = edges[j].cost;
            
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = edges[j].from;
            }
        }
    }
    
    // Step 3: Check for negative-weight cycles
    int hasNegativeCycle = 0;
    for (int j = 0; j < edgeCount; j++) {
        int u = edges[j].from - 'A';
        int v = edges[j].to - 'A';
        int w = edges[j].cost;
        
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            hasNegativeCycle = 1;
            break;
        }
    }
    
    // Step 4: Print results
    if (hasNegativeCycle) {
        printf("WARNING: Negative-weight cycle detected!\n");
        printf("Unstable transaction routes exist.\n");
    } else {
        printf("Shortest path from Branch A to each branch:\n\n");
        for (int i = 0; i < nodeCount; i++) {
            printf("Branch %c: ", 'A' + i);
            if (dist[i] == INT_MAX)
                printf("not reachable\n");
            else {
                printf("cost = %d, path = ", dist[i]);
                printPath(prev, i);
                printf("\n");
            }
        }
    }
    
    return 0;
}
