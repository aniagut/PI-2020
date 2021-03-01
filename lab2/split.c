#include <stdio.h>
#include <stdlib.h>

void sort(int* t, int n) {
	int wart, idx;
	for (int i = 1; i < n; i++) {
		wart = t[i];
		idx = i-1;
		while (idx >= 0 && wart < t[idx]) {
			t[idx+1] = t[idx];
			idx--;
		}
		t[idx+1] = wart;
	}
}

int split(int* t1, int* t2, int* t3, int n) {
	int idx1 = 0;
	int idx2 = 0;
	int idx3 = 0;
	while (idx1 < n) {
		if (t1[idx1] % 2 == 0) {
			t2[idx2] = t1[idx1];
			idx1++;
			idx2++;
		}
		else {
			t3[idx3] = t1[idx1];
			idx1++;
			idx3++;
		}
	}
	return idx2;
}

void print(int* t, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d\n", t[i]);
	}
}

int main() {

	int n;
	scanf("%d", &n);

	int* t1 = malloc(n * sizeof(int));
	int* t2 = malloc(n * sizeof(int));
	int* t3 = malloc(n * sizeof(int));

	for (int i = 0; i < n; i++) {
		scanf("%d", &t1[i]);
	}

	int e = split(t1, t2, t3, n);
	int o = n - e;

	sort(t2, e);
	sort(t3, o);

	printf("%d %d\n", e, o);
	print(t2, e);
	print(t3, o);

	free(t1);
	free(t2);
	free(t3);
}
