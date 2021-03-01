#include<stdio.h>
#include<stdbool.h>
#include <ctype.h>

void funkcja(int**W,int**T,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
          if(i==0 && j==0){
            W[i][j]+=(T[i][j+1]+T[i+1][j]+T[i+1][j+1]);
          }
          else if(i==0 && j==n-1){
            W[i][j]+=(T[i][j-1]+T[i+1][j-1]+T[i+1][j]);
          }
          else if(i==0){
            W[i][j]+=(T[i][j-1]+T[i][j+1]+T[i+1][j-1]+T[i+1][j]+T[i+1][j+1]);
          }
          else if(i==n-1 && j==0){
            W[i][j]+=(T[i-1][j]+T[i-1][j+1]+T[i][j+1]);
          }
          else if(i==n-1 && j==n-1){
            W[i][j]+=(T[i-1][j-1]+T[i-1][j]+T[i][j-1]);
          }
          else if(i==n-1){
            W[i][j]+=(T[i-1][j-1]+T[i-1][j]+T[i-1][j+1]+T[i][j-1]+T[i][j+1]);
          }
          else if(j==0){
            W[i][j]+=(T[i-1][j]+T[i-1][j+1]+T[i][j+1]+T[i+1][j]+T[i+1][j+1]);
          }
          else if(j==n-1){
            W[i][j]+=(T[i-1][j-1]+T[i-1][j]+T[i][j-1]+T[i+1][j-1]+T[i+1][j]);
          }
          else{
            W[i][j]+=(T[i-1][j-1]+T[i-1][j]+T[i-1][j+1]+T[i][j-1]+T[i][j+1]+T[i+1][j-1]+T[i+1][j]+T[i+1][j+1]);
          }
    }
}
}


int main(){
    int n;
    scanf("%d",&n);
    int** T=malloc(n*sizeof(int*));
    for(int i=0;i<n;i++){
        T[i]=malloc(n*sizeof(int));
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&T[i][j]);
        }
    }
    int** W=malloc(n*sizeof(int*));
    for(int i=0;i<n;i++){
        W[i]=malloc(n*sizeof(int));
    }
     for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            W[i][j]=0;
        }
    }
    funkcja(W,T,n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d %s",W[i][j], " ");
        }
        printf("\n");
    }

}

