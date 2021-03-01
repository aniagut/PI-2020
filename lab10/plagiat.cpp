
#include <iostream>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;

void EditDistDP(string str1, string str2,int len1,int len2, int** DP)
{

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < len1 + 1; j++) {
			DP[i][j] = 0;
		}
	}

	for (int i = 0; i <= len1; i++)
		DP[0][i] = i;

	for (int i = 1; i <= len2; i++) {

		for (int j = 0; j <= len1; j++) {

			if (j == 0)
				DP[i % 2][j] = i;

			else if (str1[j - 1] == str2[i - 1]) {
				DP[i % 2][j] = DP[(i - 1) % 2][j - 1];
			}

			else {
				DP[i % 2][j] = 1 + min(DP[(i - 1) % 2][j],
					min(DP[i % 2][j - 1],
						DP[(i - 1) % 2][j - 1]));
			}
		}
	}


	cout << DP[len2 % 2][len1] << endl;
}

int main()
{

	string str1;
	string str2;
	int n = 200;
	getline(cin, str1);
	getline(cin, str2);
    int len1 = str1.length();
	int len2 = str2.length();
	int** DP = new int* [2];
	for (int i = 0; i < 2; i++) {
		DP[i] = new int[len1+1];
	}
	EditDistDP(str1, str2, str1.length(), str2.length(), DP);
}