#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int partition(int *a, int p, int k){
    int x = a[p];
    int i = p, j = k;
    while (true){
        while (a[j] > x) j--;
        while (a[i] < x) i++;
        if (i < j) {
            a[i]+=a[j];
            a[j]=a[i]-a[j];
            a[i]-=a[j];
            i++;
            j--;
        }
        else return j;
        }
}
void quicksort(int* a, int p, int k){
if(p<k){
int q=partition(a,p,k);
if (p < q){
quicksort(a, p, q);
}
if(q<k){
quicksort(a, q+1, k);
}
}
}
int main() {
    int Z;
    scanf("%d", &Z);

	while (Z--) {
		int n;
		scanf("%d", &n);
		int *a = malloc(n * sizeof(int));
		for(int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
		}
		int p=0;
		int k=n-1;
        quicksort(a,p,k);
        for(int i = 0; i < n; i++) {
            printf("%d\n", a[i]);
        }
        free(a);
    }
}


