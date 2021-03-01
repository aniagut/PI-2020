#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define N 101	//	100 chars + nullbyte

void encrypt(char* message) {
    int s = 0;
	int w = 0;
	int dlugosc=strlen(message)-2;
	while(message[w]==' '){
        w+=1;
	}
	while (w!=dlugosc+1 && message[w] != ' ') {
		s += 1;
		w += 1;
	}
	char alphabet[] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
	for(int i=0;i<=dlugosc;i++){
        if(message[i]!=' '){
        int j=0;
        while(alphabet[j]!=message[i]){
            j+=1;
        }
        message[i]=alphabet[(j+s*2)%(strlen(alphabet))];
	}
	}

}

int main() {
	char message[N];
	fgets(message, N, stdin);
	encrypt(message);
	printf("%s\n", message);
}

