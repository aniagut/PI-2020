#include <stdio.h>
#include <stdlib.h>

int program (int* arr, int n){
int i=0;
int j=n-1;
int suma1=0;
int suma2=0;
while(i!=j){
    if(suma1<suma2){
        i+=1;
        suma1+=arr[i-1];
    }
    else if (suma2<suma1){
        j-=1;
        suma2+=arr[j+1];
    }
    else{
        if(i+1==j){
            if (arr[i]==0){
                return i;
            }
            else{
                return j;
            }
        }
        i+=1;
        j-=1;
        suma1+=arr[i-1];
        suma2+=arr[j+1];
    }
}
return j;
}

int main(){
int n;

scanf("%d",&n);

int* tablica=malloc(n*sizeof(int));

for(int i=0;i<n;i++){
    scanf("%d", &tablica[i]);
}
int wynik=program(tablica,n);

printf("%d", wynik);

free(tablica);

}
