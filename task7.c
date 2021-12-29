#include <stdio.h>
#include <stdlib.h>

struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};

struct AdjList
{
    struct AdjListNode *head;
};

struct Graph
{
    int V;
    struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array =  (struct AdjList*) malloc(V * sizeof(struct AdjList));
    for (int i = 0; i < V; ++i) graph->array[i].head = NULL;
    return graph;
}

void addNode (struct Graph* graph) {
    graph->V=graph->V+1;
    graph->array=(struct AdjList*) realloc(graph->array, graph->V*sizeof(struct AdjList));
    graph->array[graph->V-1].head=NULL;
}

void addArc (struct Graph* graph, int src, int dest) {
    struct AdjListNode* pCrawl = graph->array[src].head;
    while (pCrawl)
    {
        if (pCrawl->dest==dest)
        {
            return;
        }
        pCrawl = pCrawl->next;
    }
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

void addEdge(struct Graph* graph, int src, int dest)
{
    addArc (graph, src, dest);
    addArc (graph, dest, src);
}

void delArc (struct Graph* graph, int src, int dest)
{
    struct AdjListNode* pCrawl = graph->array[src].head;
    while (pCrawl)
    {
        if (pCrawl->dest==dest)
        {
            graph->array[src].head = pCrawl->next;
            break;
        }
        if (pCrawl->next->dest==dest)
        {
            pCrawl->next=pCrawl->next->next;
            break;
        }
        pCrawl = pCrawl->next;
    }
}

void delEdge(struct Graph* graph, int src, int dest)
{
    delArc (graph, src, dest);
    delArc (graph, dest, src);
}

struct Graph* CopyGraph (struct Graph* g, struct Graph* c) {
    c=createGraph(g->V);
    for (int i=0; i<g->V; i++) {
        for (struct AdjListNode* pCrawl = g->array[i].head; pCrawl; pCrawl=pCrawl->next) {
            addArc(c, i, pCrawl->dest);
        }
    }
    return c;
}

void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}
/*-------------------------------------------------------------------*/
/*DEFComp окрашивает компоненту связности, в которой есть Current одним цветом.
 Функция вызывается для непосященных (count[Current]==0) вершин, если это первая вершина новой компоненты
 связности (predNode==-1), то счетчик компонент (count) увеличивается на 1. Попадая в компоненту
 функция вызывается рекурсивно для всех вершин компоненты.*/
void DFSComp(struct Graph* g, int Current, int* color, int prevNode, int*  count)
{
    if (color[Current]==0)
    {
        if (prevNode==-1) /*Для каждой новой вершины в цикле будем задавать значение -1*/
        {
            (*count)++;
            color[Current]=*count;
            prevNode=0;
        }
        else {color[Current]=*count;}
/*        printf("/////////////// %i",Current);
        for (int k=0;k<g->V;k++)
            printf("%i",color[k]);
        printf("\n");                           для проверки    */
        for (struct AdjListNode* pCrawl = g->array[Current].head; pCrawl; pCrawl=pCrawl->next)
        {
            if (color[pCrawl->dest] == 0)
                DFSComp (g, pCrawl->dest, color, Current, count);
            else if (color[pCrawl->dest] == color[Current]) continue;
        }
        return;
    }
}

int countComp(struct Graph* g)        /*Счетчик копонент связности*/
{
    int counT=0;
    int* count=&counT;
    int color[g->V];
    for (int j=0; j<g->V; j++)
        { color[j]=0; }
    for (int i=0; i<g->V; i++)
    {
        int prevNode=-1;
        DFSComp(g, i, color, prevNode,count);

    }
    return *count;
}

int main()
{
    int V;
    struct Graph* Graf;
    printf("How many vertices are in the graph:");
    scanf("%i",&V);
    Graf = createGraph(V);
    for (int i=0; i<V; i++)
    {
        int count=0;
        printf("How many arcs goes from the vertex:");
        scanf("%i",&count);
        for (int j=0;j<count;j++)
        {
            int dest;
            printf("Link to a vertex number ");
            scanf("%i",&dest);
            addEdge(Graf,i,dest);
        }
    }
    printGraph(Graf);
    int count =countComp(Graf);
    printf("There is(are) %i connectivity component(s) in the graph",count);
    return 0;
}




