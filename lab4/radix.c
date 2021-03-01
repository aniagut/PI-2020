#include<stdio.h>
#include<stdlib.h>

int digit(char* number, int position) {
    return (int)(number[position]-'0');
}

void sortByPosition(char** tab, int n, int pos) {
    int k = 10;
    int *counters = malloc(k*sizeof(int));
    char** result = malloc(n*sizeof(char*));

    for(int i = 0; i < k; i++) {
      counters[i] = 0;
    }
    for(int i = 0; i < n; i++) {
      counters[digit(tab[i], pos)]++;
    }
    for(int i = 1; i < k; i++) {
      counters[i] += counters[i - 1];
    }
    for(int i = n - 1; i >= 0; i--) {
      counters[digit(tab[i], pos)]--;
      result[counters[digit(tab[i],pos)]]=tab[i];
    }
    for(int i = 0; i < n; i++) {
      tab[i] = result[i];
    }
}

void radixSort(char** tab, int n, int length) {
    for(int i = length - 1; i >= 0; i--) {
      sortByPosition(tab, n, i);
    }
}

int main() {
    int Z;
    scanf("%d", &Z);

	while (Z--) {

		int n, length;
		scanf("%d %d", &n, &length);
		char **tab = malloc(n*sizeof(char*));
		for(int i=0; i<n; i++) {
			tab[i] = malloc((length)*sizeof(char));
            int read_len = scanf("%s", tab[i]);
		}
        radixSort(tab, n, length);
        for(int i=0; i<n; i++) {
            printf("%s\n", tab[i]);
            free(tab[i]);
        }
        free(tab);
    }
}
