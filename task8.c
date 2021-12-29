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
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
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
/*-------------------------------------------------------------*/
/*создадим очередь для обхода в ширину*/
typedef struct queue
{
  struct AdjListNode* head;
  struct AdjListNode* tail;
}queue;

int queue_init (queue* q)
{
    q->head=q->tail=NULL;
    return 1;
}
int queue_is_empty (queue* q)
{
    return !q->head;
}
/*int queue_free (queue* q)
{
    int* j=NULL;
    while (!queue_pop(q, j));
    return 0;
}*/
int queue_push (queue *q, int e)
{
    struct AdjListNode* n = malloc(sizeof(struct AdjListNode));
    if (!n) return -1;
    n->next = NULL;
    n->dest = e;
    if (!q->head)
        q->tail = q->head = n;
    else
    {
        q->tail->next=n;
        q->tail=n;
    }
    return 0;
}
int queue_pop (queue* q, int *e)
{
    struct AdjListNode* t = q->head;
    if(!t) return -1;
    if (e) *e = q->head->dest;
    if (q->head == q->tail)
        q->head = q->tail = NULL;
    else
        q->head = q->head->next;
   /* free(t); */
    return 0;
}

int diametrCOMP(struct Graph* g,int Current) /*обход в ширину в компоненте связности от вершины Current - https://e-maxx.ru/algo/bfs*/
{
    int color[g->V], diam[g->V];
    for (int i = 0; i < g->V; i++)
    {
        color[i] = -1; diam[i] = -1;
    }
    queue Q;
    queue* q = &Q;
    queue_init(q);
    queue_push(q, Current);
    color[Current]=1; diam[Current]=0;
    while (!(queue_is_empty(q)))
    {
/*      int vertex = 1; vertex = queue_pop(q, &vertex);       */
        int vertex = q->head->dest; queue_pop(q, NULL);
        for (struct AdjListNode* pCrawl = g->array[vertex].head; pCrawl; pCrawl=pCrawl->next)
        {;
            if (color[pCrawl->dest] == -1)
            {
                color[pCrawl->dest] = 1;
                queue_push(q, pCrawl->dest);
                diam[pCrawl->dest] = diam[vertex]+1;
            }
        }
    }
int MAXdiametr = -1;
    for (int j = 0; j < g->V; j++)
        if (MAXdiametr < diam[j])
            MAXdiametr = diam[j];
    return MAXdiametr;
}

int diametrGRAPH(struct Graph* g)        /*обход в ширину во всем графе*/
{
    int MAXdiametr = -1;
    for (int j = 0; j < g->V; j++)
    {
        int diametr = diametrCOMP(g, j);
        if (MAXdiametr < diametr)
            MAXdiametr = diametr;
    }
    return MAXdiametr;
}


int main()
{
    int V;
    struct Graph* Graf;
    printf("How many vertices are in the graph:");
    scanf("%i",&V);
    Graf = createGraph(V);
    for (int i = 0; i<V; i++)
    {
        int count=0;
        printf("How many arcs goes from the vertex:");
        scanf("%i",&count);
        for (int j = 0;j<count;j++)
        {
            int dest;
            printf("Link to a vertex number ");
            scanf("%i",&dest);
            addEdge(Graf,i,dest);
        }
    }
    printGraph(Graf);
    int diametr = diametrGRAPH(Graf);
    printf("The diameter of the graph is: %i", diametr);
    return 0;
}











