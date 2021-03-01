#include <stdio.h>
#include <stdlib.h>

void sort(int *t, int n){
int wart, idx;
for(int i=1; i<n;i++){
    wart=t[i];
    idx=i-1;
    while(idx>=0 && wart<t[idx]){
        t[idx+1]=t[idx];
        idx--;
    }
    t[idx+1]=wart;
}
}

int merge(int *t1, int *t2, int *t3, int m, int n){
    int idx1=0;
    int idx2=0;
    int idx3=0;
    while(idx1<m && idx2<n){
        if (t1[idx1]<t2[idx2]){
            if(idx1>0 && t1[idx1]==t1[idx1-1]){
                idx1++;
            }
            else{
                t3[idx3]=t1[idx1];
                idx1++;
                idx3++;
            }
        }
        else if(t1[idx1]==t2[idx2]){
            if((idx1>0 && t1[idx1]==t1[idx1-1]) || (idx2>0 && t2[idx2]==t2[idx2-1])){
                idx1++;
                idx2++;
            }
            else{
                t3[idx3]=t1[idx1];
                idx1++;
                idx2++;
                idx3++;
            }
        }
        else{
            if(idx2>0 && t2[idx2]==t2[idx2-1]){
                idx2++;
            }
            else{
                t3[idx3]=t2[idx2];
                idx2++;
                idx3++;
            }
        }
    }
    while(idx1<m){
        if(idx1>0 && t1[idx1]==t1[idx1-1]){
            idx1++;
        }
        else{
            t3[idx3]=t1[idx1];
            idx1++;
            idx3++;
        }
    }
    while(idx2<n){
        if(idx2>0 && t2[idx2]==t2[idx2-1]){
            idx2++;
        }
        else{
            t3[idx3]=t2[idx2];
            idx2++;
            idx3++;
        }
    }
    return idx3;
}
void print(int* t, int n){
    for(int i=0;i<n;i++){
        printf("%d\n", t[i]);
    }
}

int main(void){
    int m,n;
    scanf("%d %d",&m, &n);

    int *t1=malloc(m*sizeof(int));
    int *t2=malloc(n*sizeof(int));
    int *t3=malloc((m+n)*sizeof(int));

    for(int i=0;i<m;i++){
        scanf("%d", &t1[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%d", &t2[i]);
    }
    sort(t1,m);
    sort(t2,n);

    int l=merge(t1,t2,t3,m,n);
    print(t3,l);
    free(t1);
    free(t2);
    free(t3);
}