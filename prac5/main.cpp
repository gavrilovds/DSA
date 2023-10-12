#include <iostream>
#include <queue>

using namespace std;

struct Node {
	int data;
	Node *left;
	Node *right;
};

//Бинарное дерево поиска
class BST {
private:
	Node *root;
public:
	BST() {
		root = NULL;
	}

	Node *getRoot() {
		return root;
	}

	Node *createNode(int value) {
		Node *newNode = new Node();
		newNode->data = value;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}

	void insert(int value) {
		root = insertHelper(root, value);
	}

	Node *insertHelper(Node *currentNode, int value) {
		if (currentNode == NULL) {
			currentNode = createNode(value);
		} else if (value <= currentNode->data) {
			currentNode->left = insertHelper(currentNode->left, value);
		} else {
			currentNode->right = insertHelper(currentNode->right, value);
		}
		return currentNode;
	}

	void display() {
		displayHelper(root);
	}

	void displayHelper(Node *currentNode) {
		if (currentNode != NULL) {
			displayHelper(currentNode->left);
			cout << currentNode->data << " ";
			displayHelper(currentNode->right);
		}
	}

	bool search(int value) {
		return searchHelper(root, value);
	}

	bool searchHelper(Node *currentNode, int value) {
		if (currentNode == NULL) {
			return false;
		} else if (currentNode->data == value) {
			return true;
		} else if (value <= currentNode->data) {
			return searchHelper(currentNode->left, value);
		} else {
			return searchHelper(currentNode->right, value);
		}
	}
	//Обход в ширину
	void breadthFirstTraversal() {
		if (root == NULL) {
			return;
		}

		queue<Node *> q;
		q.push(root);

		while (!q.empty()) {
			Node *currentNode = q.front();
			cout << currentNode->data << " ";

			if (currentNode->left != NULL) {
				q.push(currentNode->left);
			}
			if (currentNode->right != NULL) {
				q.push(currentNode->right);
			}

			q.pop();
		}
	}
	//Симметричный обход
	void inOrderTraversal(Node *currentNode) {
		if (currentNode == NULL) {
			return;
		}

		inOrderTraversal(currentNode->left);
		cout << currentNode->data << " ";
		inOrderTraversal(currentNode->right);
	}
	//Поиск длины пути до заданного значения от корня
	int findPathLength(Node *currentNode, int value, int length) {
		if (currentNode == NULL) {
			return 0;
		}

		if (currentNode->data == value) {
			return length;
		}

		int leftPath = findPathLength(currentNode->left, value, length + 1);
		if (leftPath != 0) {
			return leftPath;
		}

		int rightPath = findPathLength(currentNode->right, value, length + 1);
		if (rightPath != 0) {
			return rightPath;
		}

		return 0;
	}
	//Среднее значение всех узлов
	double findAverage(Node *currentNode, double &sum, double &count) {
		if (currentNode == NULL) {
			return 0;
		}

		sum += currentNode->data;
		count++;

		double leftAverage = findAverage(currentNode->left, sum, count);
		double rightAverage = findAverage(currentNode->right, sum, count);

		return (sum / count);
	}
};

int main() {
	BST tree;

	tree.insert(50);
	tree.insert(30);
	tree.insert(20);
	tree.insert(40);
	tree.insert(70);
	tree.insert(60);
	tree.insert(80);
	tree.insert(10);
	tree.insert(5);
	tree.insert(13);

	cout << "Бинарное дерево поиска:" << endl;
	tree.display();
	cout << "\n";
	int n;
	while (true) {
		cout
				<< "Введите действие(1 - BFS, 2 - симметричный обход, 3 - поиск длины пути от корня до заданного значения,"
				   "4 - поиск среднего значения всех узлов дерева):";
		cin >> n;
		int res;
		switch (n) {
			case 1:
				tree.breadthFirstTraversal();
				break;
			case 2:
				tree.inOrderTraversal(tree.getRoot());
				break;
			case 3:
				int k;
				cout << "Введите искомое значение: ";
				cin >> k;
				res = tree.findPathLength(tree.getRoot(), k, 0);
				if (res == 0 && res != tree.getRoot()->data) {
					cout << "Такого значения нет в дереве";
				} else {
					cout << "Длина до искомого значения от вершины: ";
					cout << res;
				}
				break;
			case 4:
				double summ = 0;
				double cnt = 0;
				cout << tree.findAverage(tree.getRoot(), summ, cnt);
		}
		cout << "\n";
	}

}