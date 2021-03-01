#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define REPETITIONS 5

_Static_assert(CLOCKS_PER_SEC == 1000000, "CLOCKS_PER_SEC != 1000000");

typedef struct node {
    int value;
    //height parameter is not required
    struct node** next;
} node;

typedef struct node_fam {
    int value;
    //height parameter is not required
    struct node_fam* next[];
} node_fam;

int integer_log2(int n) {
    int result = 0;
    --n;
    while (n > 0) {
        n /= 2;
        ++result;
    }
    return result;
}

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

    node* to_add = malloc(sizeof(*to_add));
    to_add->next = malloc(height * sizeof(node*));

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

void add_fam(node_fam* list, int max_height, int value) {
    int height = randomize_height(max_height);

    node_fam* to_add = malloc(sizeof(*to_add) + height * sizeof(node_fam*));

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

//identical for default struct and version with flexible array member
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

//identical for default struct and version with flexible array member
bool find_fam(node_fam* list, int max_height, int value) {
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

    //to_free != NULL <=> we've found the object to remove
    node* to_free = NULL;

    outer:
    while (lane--) {
        while (list->next[lane] && list->next[lane]->value <= value) {
            if (list->next[lane]->value == value) {
                to_free = list->next[lane];
                list->next[lane] = list->next[lane]->next[lane];

                //this is NOT a pure goto, it's a labelled break - C doesn't have this
                goto outer;
            }
            list = list->next[lane];
        }
    }
    if (to_free) {
        free(to_free->next);
        free(to_free);
    }
}

void rmv_fam(node_fam* list, int max_height, int value) {
    int lane = max_height;

    //to_free != NULL <=> we've found the object to remove
    node_fam* to_free = NULL;

    outer:
    while (lane--) {
        while (list->next[lane] && list->next[lane]->value <= value) {
            if (list->next[lane]->value == value) {
                to_free = list->next[lane];
                list->next[lane] = list->next[lane]->next[lane];

                //this is NOT a pure goto, it's a labelled break - C doesn't have this
                goto outer;
            }
            list = list->next[lane];
        }
    }
    if (to_free) {
        free(to_free);
    }
}

void bench(int height, int* data, int data_size) {
    volatile bool variable_to_prevent_compiler_from_optimising_find_call_away = false;

    node* list = malloc(sizeof(*list));
    list->next = malloc(height * sizeof(node*));

    for (int i = 0; i < height; i++) {
        list->next[i] = NULL;
    }

    for (int i = data_size - 1; i >= 0; --i) {
        add(list, height, data[i]);
    }

    for (int i = 0; i < data_size / 2; ++i) {
        rmv(list, height, data[i]);
    }

    for (int i = data_size / 2; i < data_size; ++i) {
        //retval is always true, because we've removed the first half of the set
        variable_to_prevent_compiler_from_optimising_find_call_away = find(list, height, data[i]);

        if (!variable_to_prevent_compiler_from_optimising_find_call_away) {
            printf("this is a dead statement to prevent compiler from optimising find call away");
            printf("this statement will not be executed");
        }
    }

    while (list) {
        node* to_free = list;
        list = list->next[0];
        free(to_free->next);
        free(to_free);
    }
}

void bench_fam(int height, int* data, int data_size) {
    volatile bool variable_to_prevent_compiler_from_optimising_find_call_away = false;

    node_fam* list = malloc(sizeof(*list) + height * sizeof(node*));

    for (int i = 0; i < height; i++) {
        list->next[i] = NULL;
    }

    for (int i = data_size - 1; i >= 0; --i) {
        add_fam(list, height, data[i]);
    }

    for (int i = 0; i < data_size / 2; ++i) {
        rmv_fam(list, height, data[i]);
    }

    for (int i = data_size / 2; i < data_size; ++i) {
        //retval is always true, because we've removed the first half of the set
        variable_to_prevent_compiler_from_optimising_find_call_away = find_fam(list, height, data[i]);

        if (!variable_to_prevent_compiler_from_optimising_find_call_away) {
            printf("this is a dead side effect to prevent compiler from optimising find call away");
            printf("this statement will not be executed");
        }
    }

    while (list) {
        node_fam* to_free = list;
        list = list->next[0];
        free(to_free);
    }
}

//argv[1..argc-1] - test dataset size
int main(){
    int argc;
    scanf("%d",&argc);
    int* argv=malloc(argc*sizeof(int));
    for(int i=0;i<argc;i++){
        scanf("%d",&argv[i]);
    }

    srand(0x5EEDDA7A);

    int* sizes = malloc((argc - 1) * sizeof(*sizes));

    for (int i = 1; i < argc; ++i) {
        sizes[i - 1] = atoi(argv[i]);
    }

    for (int i = 0; i < argc - 1; ++i) {
        int* data_set = malloc(sizes[i] * sizeof(*data_set));
        printf("%d,", sizes[i]);
        int max_height = integer_log2(sizes[i]);
        clock_t timeA, timeB, timeC;

        //adding and removing from the front of the list/////////////////////
        for (int j = 0; j < sizes[i]; ++j) {
            data_set[j] = j;
        }
        timeA = clock();
        for (int j = 0; j < REPETITIONS; ++j) {
            bench(max_height, data_set, sizes[i]);
        }
        timeB = clock();
        for (int j = 0; j < REPETITIONS; ++j) {
            bench_fam(max_height, data_set, sizes[i]);
        }
        timeC = clock();
        printf("%ld,%ld,", (timeB - timeA) / REPETITIONS, (timeC - timeB) / REPETITIONS);


        //adding and removing to the back of the list////////////////////////
        for (int j = 0; j < sizes[i]; ++j) {
            data_set[j] = sizes[i] - j - 1;
        }
        timeA = clock();
        for (int j = 0; j < REPETITIONS; ++j) {
            bench(max_height, data_set, sizes[i]);
        }
        timeB = clock();
        for (int j = 0; j < REPETITIONS; ++j) {
            bench_fam(max_height, data_set, sizes[i]);
        }
        timeC = clock();
        printf("%ld,%ld,", (timeB - timeA) / REPETITIONS, (timeC - timeB) / REPETITIONS);


        //random data////////////////////////////////////////////////////////
        for (int j = 0; j < sizes[i]; ++j) {
            data_set[j] = rand();
        }
        timeA = clock();
        for (int j = 0; j < REPETITIONS; ++j) {
            bench(max_height, data_set, sizes[i]);
        }
        timeB = clock();
        for (int j = 0; j < REPETITIONS; ++j) {
            bench_fam(max_height, data_set, sizes[i]);
        }
        timeC = clock();
        printf("%ld,%ld\n", (timeB - timeA) / REPETITIONS, (timeC - timeB) / REPETITIONS);


        free(data_set);
    }

    free(sizes);
}
