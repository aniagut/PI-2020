
#include <stdio.h>
#include <stdlib.h>
#define N 100

struct operacja {
    char typ;
     char number[30];
};

struct Queue{
    //rear-koniec kolejki
    //front-poczatek
    int rear, front, size;
    struct operacja arr[N];
};

struct Queue* creat_queue(){
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->rear=N-1;
    queue->front = queue->size = 0;
    return queue;
};

void add_to_queue(struct Queue* queue, struct operacja item){
    queue->rear=(queue->rear+1)%N;
    queue->arr[queue->rear]=item;
    queue->size=queue->size+1;
}

struct operacja remove_from_queue(struct Queue* queue){
            struct operacja item = queue->arr[queue->front];
            queue->front=(queue->front+1)%N;
            queue->size=queue->size-1;
            return item;
}

int isEmpty(struct Queue* queue) {
     return (queue->size == 0);
 }

void object(struct Queue* queue)
{
    struct operacja operation;

    if(scanf(" %c", &operation.typ) == 1) {
        switch (operation.typ)
        {
        case 'a':
            scanf("%d %s", &operation.secs, operation.number);
            add_to_queue(queue, operation);
            break;

        case 'r':
            scanf("%d", &operation.secs);
            struct operacja tmp = remove_from_queue(queue);
            tmp.secs = operation.secs - tmp.secs;
            printf("%s %d\n", tmp.number, tmp.secs);
        };
    }
}

int main()
{
    int k;
    scanf("%d", &k);
    struct Queue* queue = creat_queue();
    while(k--){
    object(queue);
    }
    return 0;
}
