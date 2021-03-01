#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct node {
    int value;
    struct node* next[];
} node;

int randomize_height(int max_height) {
    int result = 0;
    do {
        ++result;
    }
    while (result < max_height && rand() % 2 == 0);
    return result;
}

void add(node* list, int max_height, int value) {
    int height = randomize_height(max_height);
    node* to_add = malloc(sizeof(*to_add) + height * sizeof(node*));
    to_add->value = value;
    int lane = max_height;
    while (lane--) {
        while (list->next[lane] && list->next[lane]->value < value) {
            list = list->next[lane];
        }
        if (lane < height) {
            to_add->next[lane] = list->next[lane];
            list->next[lane] = to_add;
        }
    }
}

bool find(node* list, int max_height, int value) {
    int lane = max_height;
    while (lane--) {
        while (list->next[lane] && list->next[lane]->value <= value) {
            list = list->next[lane];
            if (list->value == value) {
                return true;
            }
        }
    }
    return false;
}

void rmv(node* list, int max_height, int value) {
    int lane = max_height;
    node* to_free = NULL;

    outer:
    while (lane--) {
        while (list->next[lane] && list->next[lane]->value <= value) {
            if (list->next[lane]->value == value) {
                to_free = list->next[lane];
                list->next[lane] = list->next[lane]->next[lane];
                goto outer;
            }
            list = list->next[lane];
        }
    }
    if (to_free) {
        free(to_free);
    }
}


int main() {
    srand(time(NULL));

    int Z;
    scanf("%d", &Z);

    while (Z--) {
        int h, a, r, f, curr;
        scanf("%d %d %d %d", &h, &a, &r, &f);

        node* list = malloc(sizeof(*list) + h * sizeof(node*));
        for (int i = 0; i < h; ++i) {
            list->next[i] = NULL;
        }

        while (a--) {
            scanf("%d", &curr);
            add(list, h, curr);

        }

        while (r--) {
            scanf("%d", &curr);
            rmv(list, h, curr);
        }

        while (f--) {
            scanf("%d", &curr);
            if (find(list, h, curr)) {
                printf("Y\n");
            }
            else {
                printf("N\n");
            }

        }

        while (list) {
            node* to_free = list;
            list = list->next[0];
            free(to_free);
        }
    }
}
