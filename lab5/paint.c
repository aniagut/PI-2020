#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct point {
    int x, y;
} point;

typedef struct queue {
    int start, end, size;
    point *elements;
} queue;

queue *new_queue(int size)
{
    queue *q = (queue *) malloc(sizeof(queue));
    q->start=0;
    q->end=0;
    q->size=size;
    q->elements=(point *) malloc(size*sizeof(point));
    return q;
}

void delete_queue(queue *q)
{
    free (q->elements);
    free (q);
}

point *get(queue *q) {
    if (q->start+1 < q->size)
    {
        return &(q->elements[++q->start]);
    }
    else
    {
        q->start=0;
        return &(q->elements[q->start]);
    }
}

bool is_empty(queue *q) {
    if (q->start==q->end) return true;
    return false;
}

void put(int x, int y, queue *q){
    if (q->end+1 < q->size)
    {
        q->end++;
        q->elements[q->end].x=x;
        q->elements[q->end].y=y;
    }
    else
    {
        q->end=0;
        q->elements[q->end].x=x;
        q->elements[q->end].y=y;
    }
}

bool not_painted(int **image, point *p,int n){
    if (p->x >=n || p->y >=n || p->x <0 || p->y <0) return false;

    if(image[p->x][p->y]==0)
        return true;
    else
        return false;
}

void fill(int **image, int n, int x, int y, int color) {
    queue *points = new_queue(n*n);
    put(x,y,points);

    while (!is_empty(points)) {
        point *p=get(points);

        if (not_painted(image,p,n))
        {
            put(p->x+1,p->y,points);
            put(p->x-1,p->y,points);
            put(p->x,p->y-1,points);
            put(p->x,p->y+1,points);

            if (image[p->x][p->y] == 0)
                image[p->x][p->y]=color;
        }
    }
    delete_queue(points);
}

int main() {
    int n, k;
    scanf("%d", &n);
    scanf("%d", &k);

    int **image = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        image[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            scanf("%d", &image[i][j]);
        }
    }

    int x, y, color;
    for (int i = 0; i < k; i++) {
        scanf("%d", &x);
        scanf("%d", &y);
        scanf("%d", &color);
        fill(image, n, x, y, color);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", image[i][j]);
        }
        printf("\n");
        free(image[i]);
    }
    free(image);
}

