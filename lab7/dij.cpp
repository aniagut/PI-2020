#include <iostream>
#include <climits>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

const int INF = INT_MAX;

typedef struct Node {
	vector <pair<Node*, int>> neighbours;
	int val, dist;
} Node;

Node* newNode(int val) {
	Node* n = new Node;
	n->val = val;
	n->dist = INF;
	return n;
}

void addEdge(Node* u, Node* v, int w) {
	pair <Node*, int> u_edge(v, w);
	pair <Node*, int> v_edge(u, w);
	u->neighbours.push_back(u_edge);
	v->neighbours.push_back(v_edge);
}

auto cmp = [](Node* x, Node* y) { return x->dist > y->dist; };

bool relax(Node* u, Node* v, int weight) {
	if (u->dist + weight < v->dist)
	{
		v->dist = u->dist + weight;
		return true;
	}
	return false;
}

void dijkustra(Node** nodes, int n, Node* start) {
	priority_queue <Node*, vector<Node*>, decltype(cmp)> queue(cmp);

	start->dist = 0;

	for (int i = 0; i < n; i++)
		queue.push(nodes[i]);

	while (!queue.empty())
	{
		Node* x = queue.top();
		queue.pop();

		for (auto neighbour : x->neighbours)
			if (relax(x, neighbour.first, neighbour.second))
				queue.push(x);
	}
}

int main() {
	int N, k, start, end;
	cin >> N >> k;
	Node **nodes=new Node*[N];  

	for (int i = 0; i < N; i++) {
		nodes[i] = newNode(i);
	}

	cin >> start >> end;

	for (int i = 0; i < k; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		addEdge(nodes[u], nodes[v], w);
	}

	dijkustra(nodes, N, nodes[start]);
	cout << nodes[end]->dist << endl;

	for (int i = 0; i < N; i++) delete nodes[i];
}