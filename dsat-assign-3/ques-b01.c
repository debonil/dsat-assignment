/*
Q. Implement the following graph algorithms from scratch. Use adjacency matrix to
represent your graph:
1) Breadth-First Search Algorithm on an undirected graph

 Submitted by Debonil Ghosh (M21AIE225)
*/

#include <stdio.h>
#include <stdlib.h>
// Used queue data structure created in assignment 1
#include "queue.h"

struct Graph
{
    int numVertices;
    int *visited;
    int **adjMtx;
};
struct Graph *createGraph(int **adjMtx, int numVertices)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjMtx = adjMtx;
    graph->visited = (int *)calloc(numVertices, sizeof(int));
    return graph;
}
void bfs(struct Graph *graph, int start)
{
    struct Queue *queue = createQueue();
    queueAdd(queue, start);

    while (queue->front != NULL)
    {
        int vertex = queueRemove(queue);
        if (!graph->visited[vertex])
        {
            graph->visited[vertex] = 1;
            printf("%d ", vertex);
            int *adjList = graph->adjMtx[vertex];
            for (int i = 0; i < graph->numVertices; i++)
                if (adjList[i] && !graph->visited[i])
                    queueAdd(queue, i);
        }
    }
}

int main()
{
    int n, **arr, s;
    scanf("%d", &n);
    arr = (int **)calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++)
        arr[i] = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &arr[i][j]);

    struct Graph *graph = createGraph(arr, n);

    scanf("%d", &s);
    bfs(graph, s);

    printf("\n");
    return 0;
}
