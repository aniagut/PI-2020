#include<stdio.h>
#include<stdlib.h>
void heapify(int*a,int n,int i){
    int l=i*2+1;
    int r=i*2+2;
    int max=i;
    if(l<=n-1 && a[l]>a[max]){
        max=l;
    }
    if(r<=n-1 && a[r]>a[max]){
        max=r;
    }
    if(max!=i){
        a[max]+=a[i];
        a[i]=a[max]-a[i];
        a[max]=a[max]-a[i];
        heapify(a,n,max);
    }
}
void build_heap(int *a,int n){
for(int i=n/2;i>=0;i--){
    heapify(a,n,i);
}
}
void heapSort(int *a, int n) {
    build_heap(a,n);
    for(int i=n-1;i>0;i--){
        a[0]+=a[i];
        a[i]=a[0]-a[i];
        a[0]=a[0]-a[i];
        heapify(a,i,0);
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

        heapSort(a, n);
        for(int i = 0; i < n; i++) {
            printf("%d\n", a[i]);
        }
        free(a);
    }
}

