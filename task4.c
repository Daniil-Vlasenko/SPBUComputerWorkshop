#include <stdio.h>
#include <stdlib.h>

struct AdjListNode      /* узел связного списка (вершины) - дуга, dest - вершина*/
{
    int dest;
    struct AdjListNode* next;
};

struct AdjList          /*вершина-это связный список, то есть массив*/
{
    struct AdjListNode *head;
};

struct Graph            /*граф - массив связных списков(вершин)*/
{
    int V;
    struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest)         /*создание узла связного списка*/
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V)        /*создание графа*/
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array =  (struct AdjList*) malloc(V * sizeof(struct AdjList));
    int i = 0;
    for (i; i < V; ++i) graph->array[i].head = NULL;
    return graph;
}

void addNode (struct Graph* graph)      /*добавление вершины*/
{
    graph->V=graph->V+1;
    graph->array=(struct AdjList*) realloc(graph->array, graph->V*sizeof(struct AdjList));
    graph->array[graph->V-1].head=NULL;
}

void addArc (struct Graph* graph, int src, int dest)    /*добавление дуги*/
{
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

void addEdge(struct Graph* graph, int src, int dest)        /*добавление симметричной дуги*/
{
    addArc (graph, src, dest);
    addArc (graph, dest, src);
}

void delArc (struct Graph* graph, int src, int dest)        /*удаление дуги (черный ящик)*/
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

/* не верный
void delArc (struct Graph* graph, int src, int dest)
{
    struct AdjListNode* pCrawl = graph->array[src].head;
    struct AdjListNode* predpCrawl = graph->array[src].head;
    while (pCrawl)
    {
        if (pCrawl->dest==dest)
        {
            predpCrawl->next=pCrawl->next;
            break;
        }
        pCrawl = pCrawl->next;
    }
}
*/


void delEdge(struct Graph* graph, int src, int dest)        /*удаление симметричной дуги*/
{
    delArc (graph, src, dest);
    delArc (graph, dest, src);
}

struct Graph* CopyGraph (struct Graph* g, struct Graph* c)      /*копирование графа*/
{
    c=createGraph(g->V);
    int i=0;
    for (i; i<g->V; i++) {
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

int main()
{
    int V,i=0;;
    struct Graph* Graf;
    printf("How many vertices are in the graph:");
    scanf("%i",&V);
    Graf = createGraph(V);
    for (i; i<V; i++)
    {
        int count=0;
        printf("How many arcs goes from the vertex:");
        scanf("%i",&count);
        int j=0;
        for (j;j<count;j++)
        {
            int dest;
            printf("Link to a vertex number ");
            scanf("%i",&dest);
            addArc(Graf,i,dest);
        }
    }
    printGraph(Graf);
    return 0;
}
  /*проверка создание и вывода графа*/
