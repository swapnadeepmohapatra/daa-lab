#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100  // Maximum number of vertices
#define INF 9999 // Representation of no edge in adjacency matrix

typedef struct
{
    int vertex, key;
} MinHeapNode;

typedef struct
{
    MinHeapNode *array;
    int *position;
    int size;
} MinHeap;

int parent[MAX];
int adjMatrix[MAX][MAX];

// Function prototypes
void readGraph(int n);
MinHeap *createMinHeap(int capacity);
void insertMinHeap(MinHeap *minHeap, int vertex, int key);
MinHeapNode extractMin(MinHeap *minHeap);
void decreaseKey(MinHeap *minHeap, int vertex, int key);
void prims(int n);

int main()
{
    int n;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    readGraph(n);
    prims(n);

    return 0;
}

// Function to read graph from file
void readGraph(int n)
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

// Utility functions for Min-Heap
MinHeap *createMinHeap(int capacity)
{
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->position = (int *)malloc(capacity * sizeof(int));
    minHeap->array = (MinHeapNode *)malloc(capacity * sizeof(MinHeapNode));
    minHeap->size = 0;
    return minHeap;
}

void swapMinHeapNodes(MinHeapNode *a, MinHeapNode *b)
{
    MinHeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left].key < minHeap->array[smallest].key)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right].key < minHeap->array[smallest].key)
        smallest = right;

    if (smallest != idx)
    {
        MinHeapNode smallestNode = minHeap->array[smallest];
        MinHeapNode idxNode = minHeap->array[idx];

        // Swap positions
        minHeap->position[smallestNode.vertex] = idx;
        minHeap->position[idxNode.vertex] = smallest;

        // Swap nodes
        swapMinHeapNodes(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

MinHeapNode extractMin(MinHeap *minHeap)
{
    if (minHeap->size == 0)
        return (MinHeapNode){-1, INF};

    MinHeapNode root = minHeap->array[0];
    MinHeapNode lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->position[root.vertex] = minHeap->size - 1;
    minHeap->position[lastNode.vertex] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(MinHeap *minHeap, int vertex, int key)
{
    int i = minHeap->position[vertex];
    minHeap->array[i].key = key;

    while (i && minHeap->array[i].key < minHeap->array[(i - 1) / 2].key)
    {
        minHeap->position[minHeap->array[i].vertex] = (i - 1) / 2;
        minHeap->position[minHeap->array[(i - 1) / 2].vertex] = i;
        swapMinHeapNodes(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Prim's algorithm using Min-Heap (Min-Priority Queue)
void prims(int n)
{
    int key[MAX];
    MinHeap *minHeap = createMinHeap(n);
    int totalCost = 0;

    for (int v = 0; v < n; v++)
    {
        key[v] = INF;
        parent[v] = -1;
        insertMinHeap(minHeap, v, key[v]);
    }

    key[0] = 0;
    decreaseKey(minHeap, 0, key[0]);

    while (minHeap->size)
    {
        MinHeapNode minNode = extractMin(minHeap);
        int u = minNode.vertex;

        totalCost += key[u];

        for (int v = 0; v < n; v++)
        {
            int weight = adjMatrix[u][v];
            if (weight != INF && minHeap->position[v] < minHeap->size && weight < key[v])
            {
                key[v] = weight;
                parent[v] = u;
                decreaseKey(minHeap, v, key[v]);
            }
        }
    }

    // Display MST
    printf("Edges in the Minimum Spanning Tree:\n");
    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++)
    {
        printf("%d - %d \t%d\n", parent[i] + 1, i + 1, adjMatrix[i][parent[i]]);
    }

    printf("Total cost of Minimum Spanning Tree: %d\n", totalCost);

    free(minHeap->array);
    free(minHeap->position);
    free(minHeap);
}
