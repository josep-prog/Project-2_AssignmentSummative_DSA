#include <stdio.h>
#include <stdlib.h>

#define MAX 7

// Graph as adjacency matrix with costs
int graph[MAX][MAX] = {
    {0, 11, 0, 0, 0, 0, 22},
    {11, 0, 17, 0, 0, 0, 0},
    {0, 17, 0, 22, 0, 10, 0},
    {0, 0, 22, 0, 25, 0, 0},
    {0, 0, 0, 25, 0, 6, 0},
    {0, 0, 10, 0, 6, 0, 5},
    {22, 0, 0, 0, 0, 5, 0},
};

char hubs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

int main() {
    char suspect;
    int start;
    
    printf("Enter suspected compromised hub (A, B, C, D, E, F, G): ");
    scanf(" %c", &suspect);
    
    // Convert letter to index (A=0, B=1, ...)
    start = suspect - 'A';
    
    if (start < 0 || start >= MAX) {
        printf("Invalid hub.\n");
        return 1;
    }
    
    printf("\nDirectly connected workstations (1-hop neighbors) from %c:\n", suspect);
    
    int maxNeighbor = -1;
    int maxTime = -1;

    // BFS setup: queue + visited set
    int queue[MAX];
    int front = 0, rear = 0;
    int visited[MAX] = {0};

    visited[start] = 1;
    queue[rear++] = start;

    // Process the start node and visit its neighbors (BFS level 1)
    int u = queue[front++];
    for (int i = 0; i < MAX; i++) {
        if (graph[u][i] != 0 && !visited[i]) {
            visited[i] = 1;
            queue[rear++] = i;

            printf("%c (time: %d minutes)\n", hubs[i], graph[u][i]);

            // Check if this is the highest time
            if (graph[u][i] > maxTime) {
                maxTime = graph[u][i];
                maxNeighbor = i;
            }
        }
    }
    
    if (maxNeighbor != -1) {
        printf("\nHighest risk exposure: %c with data transfer time %d minutes\n", 
               hubs[maxNeighbor], maxTime);
    } else {
        printf("\nNo direct connections found.\n");
    }
    
    return 0;
}
