#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<math.h>
void liczby_najpierwsze(int n){
if (n>2){
    printf("%d\n",2);
for(int i=3;i<n;i=i+2){
    bool flag=true;
    int liczba=i;
    int ost=liczba%10;
    liczba/=10;
    int przed=liczba%10;
    while(liczba>0 && przed<=ost){
        liczba/=10;
        ost=przed;
        przed=liczba%10;
    }
    if(przed>ost) flag=false;
    if(i%2==0) flag=false;
    for(int k=3;k<=sqrt(i) && flag;k+=2){
        if(i%k==0) flag=false;
    }
    if(flag){
        printf("%d\n",i);
    }
}
}
}
int main(){
int n;
scanf("%d",&n);
liczby_najpierwsze(n);
}
