#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node {
    int n;
    struct node* next;
} node;

void dfs(node** graph, int* components, int n, int i, int component_no) {
    components[i] = component_no;
    node* neighbor = graph[i];

    while(neighbor != NULL)
    {
        if(components[neighbor->n] == -1)
            dfs(graph, components, n, neighbor->n, component_no);

        neighbor = neighbor->next;
    }
}

int* count_components(node** graph, int n)
{
    int* components = malloc(sizeof(int)*n);

    for(int i=0; i<n; i++) components[i] = -1;

    int counter = 0;

    for(int i=0; i<n; i++)
        if(components[i] == -1)
            dfs(graph, components, n, i, counter++);

    return components;
}

int main() {
    int n, k, p;
    scanf("%d", &n);
    node **graph = malloc(sizeof(node*)*n);

    for(int i=0;i<n;i++) graph[i] = NULL;

    scanf("%d", &k);
    scanf("%d", &p);

    for (int i=0; i<k; i++)
    {
        node *tmp1 = malloc(sizeof(node)), *tmp2 = malloc(sizeof(node));
        int x, y;
        scanf("%d", &x);
        scanf("%d", &y);
        tmp1->n = y;
        tmp1->next = graph[x];
        graph[x] = tmp1;

        tmp2->n = x;
        tmp2->next = graph[y];
        graph[y] = tmp2;
    }
    int* components = count_components(graph, n);

    for (int i=0; i<p; i++)
    {
        int x, y;
        scanf("%d", &x);
        scanf("%d", &y);
        if(components[x] == components[y])
            printf("%s\n", "YES");
        else
            printf("%s\n", "NO");
    }
    free(graph);
    free(components);
}

