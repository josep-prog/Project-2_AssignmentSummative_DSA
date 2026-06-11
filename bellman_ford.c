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
    // Bank branch network (Branch A-J). Graph is undirected,
    // so each connection is listed in both directions.
    struct Edge edges[] = {
        {'A', 'B', 4},  {'B', 'A', 4},
        {'A', 'D', 16}, {'D', 'A', 16},
        {'B', 'C', 6},  {'C', 'B', 6},
        {'B', 'D', 6},  {'D', 'B', 6},
        {'B', 'J', 7},  {'J', 'B', 7},
        {'C', 'G', 9},  {'G', 'C', 9},
        {'D', 'E', 7},  {'E', 'D', 7},
        {'D', 'J', 3},  {'J', 'D', 3},
        {'E', 'F', 10}, {'F', 'E', 10},
        {'E', 'I', 2},  {'I', 'E', 2},
        {'F', 'I', 10}, {'I', 'F', 10},
        {'F', 'J', 3},  {'J', 'F', 3},
        {'G', 'H', 13}, {'H', 'G', 13},
    };
    int edgeCount = 26;
    int nodeCount = 10;
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
            printf("Unstable route detected via branch %c -> %c\n", edges[j].from, edges[j].to);
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
