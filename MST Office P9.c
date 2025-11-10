#include <stdio.h>
#include <limits.h> // For INT_MAX

#define MAX_OFFICES 100

int graph[MAX_OFFICES][MAX_OFFICES];
int num_offices;

void prim_mst() {
    int parent[MAX_OFFICES]; // Stores the parent of each office in the MST
    int key[MAX_OFFICES];    // Stores the minimum cost to connect to the MST
    int mst_set[MAX_OFFICES]; // True if office is included in MST, False otherwise

    // Initialize key values to infinity, mst_set to false
    for (int i = 0; i < num_offices; i++) {
        key[i] = INT_MAX;
        mst_set[i] = 0; // 0 for false
    }

    key[0] = 0;      // Start with the first office
    parent[0] = -1;  // First node is root of MST

    for (int count = 0; count < num_offices - 1; count++) {
        int u = -1; // Office with minimum key value not yet in MST

        // Find the office with the minimum key value among those not yet in MST
        int min_key = INT_MAX;
        for (int v = 0; v < num_offices; v++) {
            if (mst_set[v] == 0 && key[v] < min_key) {
                min_key = key[v];
                u = v;
            }
        }

        mst_set[u] = 1; // Add the selected office to the MST

        // Update key values and parent index of adjacent offices
        for (int v = 0; v < num_offices; v++) {
            if (graph[u][v] && mst_set[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    printf("Edges in Minimum Spanning Tree:\n");
    int total_cost = 0;
    for (int i = 1; i < num_offices; i++) {
        printf("Office %d -- Office %d (Cost: %d)\n", parent[i], i, graph[i][parent[i]]);
        total_cost += graph[i][parent[i]];
    }
    printf("Total minimum cost: %d\n", total_cost);
}

int main() {
    printf("Enter the number of offices: ");
    scanf("%d", &num_offices);

    printf("Enter the cost matrix (INT_MAX for no direct connection):\n");
    for (int i = 0; i < num_offices; i++) {
        for (int j = 0; j < num_offices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    prim_mst();

    return 0;
}
