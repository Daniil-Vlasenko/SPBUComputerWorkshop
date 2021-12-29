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


enum color { NotVisited, First, Second};    /*Создаем перечисляемый тип*/

int DFScolor (struct Graph *g, int Current, int *color, int prevNode)   /*Обход в глубину, отдельно создаем массив color, где красим вершины*/
{                                                                       /*Предварительно массив color идентифицуруем весь NotVisited*/
    if (prevNode==-1) color[Current] = First;
    else if (color[prevNode]==First) color[Current]=Second;
    else color[Current]=First;
	for (struct AdjListNode* pCrawl = g->array[Current].head; pCrawl; pCrawl=pCrawl->next)
		if (color[pCrawl->dest] == NotVisited)
			DFScolor (g, pCrawl->dest, color, Current);
        else if (color[pCrawl->dest] == color[Current]) return 0;
	return 1;
}

void is_bipartite (struct Graph *g) {    /*Ответ на вопрос о двудольности графа*/
	int color[g->V];
	for (int i=0; i<g->V; i++) {
        color[i]=0;
	}
	int Yes_or_not = DFScolor (g, 0, color, -1);
    printf("%i\n",Yes_or_not);
    if (Yes_or_not)
    {
        for (int i = 0; i < g->V; i++)
        {
            printf("Vertex %i is in the %i part of the Graph\n", i, color[i]);
        }
    }
	return;
}

int main()
{
    int V;
    struct Graph* Graf;
    printf("How many vertices are in the graph:");
    scanf("%i",&V);
    Graf = createGraph(V);
    for (int i = 0; i < V; i++)
    {
        int count=0;
        printf("How many arcs goes from the vertex:");
        scanf("%i",&count);
        for (int j = 0; j < count; j++)
        {
            int dest;
            printf("Link to a vertex number ");
            scanf("%i",&dest);
            addEdge(Graf,i,dest);
        }
    }
    is_bipartite(Graf);
    return 0;
}















