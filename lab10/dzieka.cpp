#include<iostream>
using namespace std;

class BST {

	struct node {
		int num;
		string name;
		node* left;
		node* right;
	};

	node* root;

	node* makeEmpty(node* t) {
		if (t == NULL)
			return NULL;
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		return NULL;
	}

	node* insert(int x,string name, node* t)
	{
		if (t == NULL)
		{
			t = new node;
			t->num = x;
			t->name = name;
			t->left = t->right = NULL;
		}
		else if (x < t->num)
			t->left = insert(x,name, t->left);
		else if (x > t->num)
			t->right = insert(x,name, t->right);
		return t;
	}

	node* findMin(node* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->left == NULL)
			return t;
		else
			return findMin(t->left);
	}

	node* findMax(node* t) {
		if (t == NULL)
			return NULL;
		else if (t->right == NULL)
			return t;
		else
			return findMax(t->right);
	}

	node* remove(int x, node* t) {
		node* temp;
		if (t == NULL)
			return NULL;
		else if (x < t->num)
			t->left = remove(x, t->left);
		else if (x > t->num)
			t->right = remove(x, t->right);
		else if (t->left && t->right)
		{
			temp = findMin(t->right);
			t->num = temp->num;
			t->right = remove(t->num, t->right);
		}
		else
		{
			temp = t;
			if (t->left == NULL)
				t = t->right;
			else if (t->right == NULL)
				t = t->left;
			delete temp;
		}

		return t;
	}

	void inorder(node* t) {
		if (t == NULL)
			return;
		inorder(t->left);
		cout << t->num << " ";
		inorder(t->right);
	}

	node* find(node* t, int x) {
		if (t == NULL)
			return NULL;
		else if (x < t->num)
			return find(t->left, x);
		else if (x > t->num)
			return find(t->right, x);
		else
			return t;
	}

public:
	BST() {
		root = NULL;
	}

	~BST() {
		root = makeEmpty(root);
	}

	void insert(int x,string name) {
		root = insert(x,name, root);
	}

	void remove(int x) {
		root = remove(x, root);
	}

	void display() {
		inorder(root);
		cout << endl;
	}

	void search(int x) {
		root = find(root, x);
		if (root == NULL) cout << "NO" << endl;
		else cout << root->name << endl;
	}
};

int main() {
	BST t;
	int a, r, f;
	cin >> a >> r >> f;
	while (a--) {
		int num;
		string name;
		cin >> num >> name;
		t.insert(num, name);
	}
	while (r--) {
		int num;
		cin >> num;
		t.remove(num);
	}
	while (f--) {
		int num;
		cin >> num;
		t.search(num);
	}
	
}