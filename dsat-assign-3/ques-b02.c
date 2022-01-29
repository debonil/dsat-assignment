/*
Q. Implement the following graph algorithms from scratch. Use adjacency matrix to
represent your graph:
2) Depth First Search Algorithm on an undirected graph

 Submitted by Debonil Ghosh (M21AIE225)
*/

#include <stdio.h>
#include <stdlib.h>

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
void dfs(struct Graph *graph, int vertex)
{
    int *adjList = graph->adjMtx[vertex];

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    for (int i = 0; i < graph->numVertices; i++)
        if (adjList[i] && !graph->visited[i])
            dfs(graph, i);
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
    dfs(graph, s);

    printf("\n");
    return 0;
}
