#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF INT_MAX

void floydWarshall(int n, int dist[MAX][MAX], int next[MAX][MAX])
{
    int i, j, k;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (dist[i][j] != INF && i != j)
            {
                next[i][j] = j;
            }
            else
            {
                next[i][j] = -1;
            }
        }
    }

    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

void printMatrix(int n, int dist[MAX][MAX])
{
    printf("Shortest path distance matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] == INF)
            {
                printf("INF ");
            }
            else
            {
                printf("%d ", dist[i][j]);
            }
        }
        printf("\n");
    }
}

void printPath(int u, int v, int next[MAX][MAX])
{
    if (next[u][v] == -1)
    {
        printf("No path\n");
        return;
    }
    printf("Shortest Path from vertex %d to vertex %d: %d", u + 1, v + 1, u + 1);
    while (u != v)
    {
        u = next[u][v];
        printf(" --> %d", u + 1);
    }
    printf("\n");
}

int main()
{
    int n;
    int dist[MAX][MAX], next[MAX][MAX];
    int source, destination;

    FILE *file = fopen("inDiAdjMat2.dat", "r");
    if (!file)
    {
        printf("Error: Unable to open file\n");
        return 1;
    }

    fscanf(file, "%d", &n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fscanf(file, "%d", &dist[i][j]);
            if (i != j && dist[i][j] == 0)
            {
                dist[i][j] = INF;
            }
            next[i][j] = -1;
        }
    }
    fclose(file);

    floydWarshall(n, dist, next);

    printMatrix(n, dist);

    printf("Enter the source and destination vertex: ");
    scanf("%d %d", &source, &destination);
    source--;
    destination--;

    if (dist[source][destination] == INF)
    {
        printf("No path exists from vertex %d to vertex %d\n", source + 1, destination + 1);
    }
    else
    {
        printf("Path weight: %d\n", dist[source][destination]);
        printPath(source, destination, next);
    }

    return 0;
}
