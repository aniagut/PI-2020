#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
bool is_triangular(int** macierz, int n){
    if(n==0 || n==1){
        return false;
    }
    for(int i=0; i<n-1; i++){
        for(int k=i+1;k<n;k++){
            if(macierz[i][k]!=0){
                return false;
            }
        }
    }
    return true;
}

int main(void){
int n;
scanf("%d", &n);
int** macierz=malloc(n*sizeof(int*));
for(int i=0;i<n;i++){
    macierz[i]=malloc(n*sizeof(int));
}
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        scanf("%d", &macierz[i][j]);
    }
}
if(is_triangular(macierz,n)){
    printf("YES\n");
}
else{
    printf("NO\n");
}
for(int i=0;i<n;i++){
    free(macierz[i]);
}
free(macierz);
}
