#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Maximum number of vertices
#define INF 9999 // Representation of no edge in adjacency matrix

typedef struct
{
    int u, v, weight;
} Edge;

int parent[MAX];

// Function prototypes
void readGraph(int n, int adjMatrix[MAX][MAX]);
int find(int i);
void unionSets(int u, int v);
void kruskal(int n, int adjMatrix[MAX][MAX]);

int main()
{
    int n, adjMatrix[MAX][MAX];

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    readGraph(n, adjMatrix);
    kruskal(n, adjMatrix);

    return 0;
}

// Function to read graph from file
void readGraph(int n, int adjMatrix[MAX][MAX])
{
    FILE *file = fopen("inUnAdjMat.dat", "r");
    if (!file)
    {
        printf("Error: Cannot open file.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fscanf(file, "%d", &adjMatrix[i][j]);
            if (i != j && adjMatrix[i][j] == 0)
                adjMatrix[i][j] = INF; // No edge
        }
    }
    fclose(file);
}

// Find root of the set containing i
int find(int i)
{
    if (parent[i] == i)
        return i;
    return find(parent[i]);
}

// Union two sets containing u and v
void unionSets(int u, int v)
{
    int root_u = find(u);
    int root_v = find(v);
    parent[root_u] = root_v;
}

// Kruskal's algorithm
void kruskal(int n, int adjMatrix[MAX][MAX])
{
    Edge edges[MAX * MAX];
    int edgeCount = 0;

    // Convert adjacency matrix to edge list
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (adjMatrix[i][j] != INF)
            {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].weight = adjMatrix[i][j];
                edgeCount++;
            }
        }
    }

    // Sort edges by weight (Bubble sort)
    for (int i = 0; i < edgeCount - 1; i++)
    {
        for (int j = 0; j < edgeCount - i - 1; j++)
        {
            if (edges[j].weight > edges[j + 1].weight)
            {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    // Initialize parent array for Union-Find
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
    }

    int mstCost = 0;
    int mstEdges = 0;
    printf("Edges in the Minimum Spanning Tree:\n");
    printf("Edge \tWeight\n");

    for (int i = 0; i < edgeCount && mstEdges < n - 1; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;

        // Check if adding this edge creates a cycle
        if (find(u) != find(v))
        {
            printf("%d - %d \t%d\n", u + 1, v + 1, weight);
            mstCost += weight;
            unionSets(u, v);
            mstEdges++;
        }
    }

    printf("Total cost of Minimum Spanning Tree: %d\n", mstCost);
}
