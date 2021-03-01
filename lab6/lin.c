#include<iostream>
#include<list>

using namespace std;

int n;
list<int>* graph;
int nlines;
list<int>* lines;
bool flag;


void euler(int u)
{
	while (!graph[u].empty())
	{
		int v = graph[u].front();
		graph[v].remove(u);
		graph[u].pop_front();
		euler(v);
	}

	if (!flag && u == 0)
		nlines++;
	else
		lines[nlines].push_back(u);
}

int main() {
	int Z;

	cin >> Z;

	while (Z--) {
		int n, m;
		cin >> n >> m;

		graph = new list<int>[n + 2];
		lines = new list<int>[n + 2];
		int u, v;
		for (int i = 0; i < m; i++)
		{
			cin >> u >> v;
			graph[u].push_back(v);
			graph[v].push_back(u);
		}

		flag = true;
		for (int i = 1; i <= n; i++)
			if (graph[i].size() % 2 != 0)
			{
				graph[i].push_back(0);
				graph[0].push_back(i);
				flag = false;
			}

		nlines = 0;

		if (flag)
			euler(1);
		else
			euler(0);

		int lines_number = 0;

		for (int i = 0; i <= nlines; i++)
			if (lines[i].size() > 1)
				lines_number++;

		printf("%d\n", lines_number);

		for (int i = 0; i <= lines_number; i++)
		{
			if (lines[i].size() > 1)
			{
				printf("%lu ", lines[i].size());
				for (list<int>::iterator it = lines[i].begin(); it != lines[i].end(); it++)
				{
					printf("%d ", *it);
				}
				printf("\n");
			}
		}

		delete[] graph;
		delete[] lines;
	}
}
