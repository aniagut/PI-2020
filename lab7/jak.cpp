#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <algorithm>

using namespace std;

const int INF = INT_MAX / 2;

typedef struct Segment {
	int town, travel_time;
} Segment;

typedef struct Line {
	Segment* segments;
	int number, length, start_town;
} Line;

Line* newLine(int number, int length, int start_town) {
	Line* l = new Line;
	l->number = number;
	l->length = length;
	l->start_town = start_town;
	l->segments = new Segment[length];
	return l;
}

typedef struct Node {
	int town, id;
	vector< pair<Node*, int> > neighbours;
} Node;

int** calculateTimesMatrix(Line** lines, int lines_no, int towns) {
	int** times = new int* [towns];

	for (int i = 0; i < towns; i++)
	{
		times[i] = new int[towns];
		for (int j = 0; j < towns; j++)
			if (i == j)
				times[i][j] = 0;
			else
				times[i][j] = INF;
	}                                   //wypelnienie wartosciami 0 lub INF

	for (int i = 0; i < lines_no; i++)
	{
		Line* line = lines[i];
		int first = line->start_town;

		for (int j = 0; j < line->length; j++)
		{
			Segment next = line->segments[j];
			times[first][next.town] = min(next.travel_time, times[first][next.town]);
			times[next.town][first] = min(next.travel_time, times[next.town][first]);

			first = next.town;
		}
	}

	for (int m = 0; m < towns; m++)
		for (int i = 0; i < towns; i++)
			for (int j = 0; j < towns; j++)
				if (times[i][j] > times[i][m] + times[m][j])
					times[i][j] = times[i][m] + times[m][j];

	return times;
}

int main() {
	int towns, lines_no, queries;
	cin >> towns >> lines_no >> queries;

	Line** lines = new Line * [lines_no];

	for (int i = 0; i < lines_no; i++) {
		int len, start;
		cin >> len >> start;
		lines[i] = newLine(i, len - 1, start);
		for (int j = 0; j < len - 1; j++) {
			int next, time;
			cin >> time >> next;
			lines[i]->segments[j].town = next;
			lines[i]->segments[j].travel_time = time;
		}
	}

	int** times = calculateTimesMatrix(lines, lines_no, towns);

	for (int i = 0; i < queries; i++) {
		int u, v;
		cin >> u >> v;
		cout << times[u][v] << endl;
	}

	for (int i = 0; i < towns; i++) delete[] times[i];
	delete[] times;
	for (int i = 0; i < lines_no; i++) {
		delete[] lines[i]->segments;
		delete lines[i];
	}
	delete[] lines;
}

