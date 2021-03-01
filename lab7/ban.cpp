#include <iostream>
#include <climits>
#include <vector>
#include <utility>

using namespace std;

const int INF = INT_MAX/2;

typedef struct Node {
	Node* parent;
	vector <pair<Node*, int>> neighbours;
	int val, dist;
} Node;

Node* newNode(int val) {
	Node* n = new Node;
	n->val = val;
	n->dist = INF;
	n->parent = NULL;
	return n;
}

void addEdge(Node* u, Node* v, int w) {
	pair <Node*, int> edge(v, w);
	u->neighbours.push_back(edge);
}

void relax(Node* u, Node* v, int weight) {
	if (u->dist + weight < v->dist) {
		v->parent = u;
		v->dist = u->dist + weight;
	}
}

bool bellmann_ford(Node** nodes, int N, Node* start) {
	start->dist = 0;

	for (int i = 1; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (auto edge : nodes[j]->neighbours) {
				relax(nodes[j], edge.first, edge.second);
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (auto edge : nodes[i]->neighbours) {
			if (nodes[i]->dist + edge.second < edge.first->dist) {
				return false;
			}
		}
	}

	return true;
}

int main() {
	int N, k, start, end;
	cin >> N >> k;
	Node** nodes = new Node * [N];
	for (int i = 0; i < N; i++) nodes[i] = newNode(i);
	cin >> start >> end;
	for (int i = 0; i < k; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		addEdge(nodes[u], nodes[v], w);
	}

	if (!bellmann_ford(nodes, N, nodes[start])) cout << "CYCLE" << endl;
	else if (nodes[end]->dist < INF) cout << nodes[end]->dist << endl;
	else cout << "NO" << endl;

	for (int i = 0; i < N; i++) delete nodes[i];
}