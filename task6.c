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

void ReadFromFile (struct Graph *g, char *s)   /*Чтение из файла графа*/
{
    FILE *fp;
    fp=fopen(s, "r");
    for (int i=0; i<g->V; i++) {
        for (int j=0; j<g->V; j++) {
            int val=0;
            char sym;
            fscanf(fp, " %c", &sym);
            val = sym-'0';                      /*Не понял этот момент*/
            if (val!=0) addArc(g, i, j);
        }
    }
    fclose(fp);
    return;
}

void WriteToFile (struct Graph *g, char *s)     /*Вывод в вайл графа*/
{
    FILE *fp;
    fp=fopen(s, "w");
    struct AdjListNode* pCrawl = g->array[0].head;
    for (int i=0; i<g->V; i++) {
        if (i) fprintf(fp, "\n");
        for (int j=0; j<g->V; j++) {
            pCrawl = g->array[i].head;
            while (pCrawl)
            {
                if (pCrawl->dest==j)
                {
                    fprintf(fp, "%d", 1);
                    break;
                }
                pCrawl = pCrawl->next;
            }
            if (!pCrawl) fprintf(fp, "%d", 0);
        }
    }
    fclose(fp);
    return;
}

int main() /*создадим вручную граф Graf1, запишем его в файл text, считаем файл text в граф Graf2 и выведем его*/
{
    int V,i=0;;
    struct Graph* Graf1;
    struct Graph* Graf2;
    printf("How many vertices are in the graph:");
    scanf("%i",&V);
    Graf1=createGraph(V);
    Graf2=createGraph(V);
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
            addArc(Graf1,i,dest);
        }
    }
    WriteToFile(Graf1,"text.txt");
    ReadFromFile(Graf2,"text.txt");
    printGraph(Graf2);
    return 0;
}










