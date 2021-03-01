#include <iostream>

using namespace std;

struct Node
{
	string nazwisko;
	string number;
	Node* next;
};

struct operacja {
	char typ;
	string nazwisko;
	string number;
};

int hashfunc(string nazwisko) {
	int hash = 0;

	int min = nazwisko.length();
	if (min > 5) min = 5;

	for (int i = 0; i < min; i++) {
		hash = hash * 31 + pow(nazwisko[i],2);
	}
	return hash;
}

void add_to_hashtable(Node** hashtable, int n, string nazwisko, string number) {

	int hash = hashfunc(nazwisko) % n;

	Node* newNode = new Node;
	newNode->nazwisko = nazwisko;
	newNode->number = number;
	newNode->next = NULL;

	Node* node = hashtable[hash];


	if (node == NULL) {
		hashtable[hash] = newNode;
		return;
	}

	while (node->next != NULL) {
		node = node->next;
	}
	node->next = newNode;

}



void remove_from_hashtable(Node** hashtable, int n, string nazwisko) {

	int hash = hashfunc(nazwisko) % n;

	Node* tmp = hashtable[hash];
	if (tmp == NULL) return;
	if (tmp->nazwisko == nazwisko) {
		hashtable[hash] = hashtable[hash]->next;
		return;
	}

	while (tmp->next != NULL && tmp->next->nazwisko != nazwisko) tmp = tmp->next;

	if (tmp->next != NULL) {


		Node* c = tmp->next;


		tmp->next = tmp->next->next;


		delete c;
	}
}

void get_from_hashtable(Node** hashtable, int n, string nazwisko) {
	int hash = hashfunc(nazwisko) % n;
	Node* tmp = new Node;
	tmp->next = hashtable[hash];

	while (tmp->next != NULL && nazwisko != tmp->next->nazwisko) tmp = tmp->next
		;


	if (tmp->next != NULL) cout << tmp->next->number << endl;
	else cout << endl;

}
int main() {

	int Z;
	cin >> Z;

	while (Z--) {
		int n, k;


		cin >> n >> k;



		Node** hashtable = new Node * [n];

		for (int i = 0; i < n; i++)
			hashtable[i] = NULL;




		for (int i = 0; i < k; i++) {

			struct operacja operation;
			cin >> operation.typ;
			switch (operation.typ)
			{
			case 'a':
				cin >> operation.nazwisko >> operation.number;
				add_to_hashtable(hashtable, n, operation.nazwisko, operation.number);
				break;

			case 'r':
				cin >> operation.nazwisko;
				remove_from_hashtable(hashtable, n, operation.nazwisko);
				break;

			case 'g':
				cin >> operation.nazwisko;
				get_from_hashtable(hashtable, n, operation.nazwisko);
				break;

			};


		}

		for (int i = 0; i < n; i++) {
			free(hashtable[i]);
		}

		free(hashtable);

	}

}

