#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

// Структура для представления ребра графа
struct Edge {
	int to;
	int weight;
};

// Структура для представления вершины графа
struct Vertex {
	int id;
	int distance;
	bool visited;
	vector<Edge> edges;
};

// Функция для поиска кратчайшего пути методом Дейкстры
void dijkstra(vector<Vertex> &graph, int source) {
	// Инициализируем расстояния до всех вершин как бесконечность
	for (auto &vertex: graph) {
		vertex.distance = INF;
		vertex.visited = false;
	}

	// Расстояние до исходной вершины равно 0
	graph[source].distance = 0;

	// Очередь с приоритетом для хранения вершин, которые нужно обработать
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	// Добавляем исходную вершину в очередь
	pq.push(make_pair(0, source));

	while (!pq.empty()) {
		// Извлекаем вершину с наименьшим расстоянием
		auto current = pq.top().second;
		pq.pop();

		// Если вершина уже была посещена, пропускаем ее
		if (graph[current].visited) {
			continue;
		}

		// Помечаем вершину как посещенную
		graph[current].visited = true;

		// Обновляем расстояния до смежных вершин
		for (auto &edge: graph[current].edges) {
			auto next = edge.to;
			auto weight = edge.weight;

			if (!graph[next].visited && graph[current].distance != INF &&
				graph[current].distance + weight < graph[next].distance) {
				graph[next].distance = graph[current].distance + weight;
				pq.push(make_pair(graph[next].distance, next));
			}
		}
	}
}

int main() {
	// Создаем граф из варианта №13
	int n;
	cout << "Введите кол-во вершин в графе: ";
	cin >> n;
	vector<Vertex> graph(n);
	for (int i = 0; i < n; i++) {
		graph[i].id = i;
		cout << "Текущая вершина: " << i + 1 << "\n";
		while (true) {

			cout
					<< "Введите номер вершины, с котрой должна быть соединена текущая вершина, а так же расстояние до нее (для остановки введите -1): ";
			int to, weight;
			cin >> to;
			if (to == -1)
				break;
			cin >> weight;
			graph[i].edges.push_back({to - 1, weight});
		}
	}
	// Запускаем алгоритм Дейкстры
	dijkstra(graph, 0);

	cout << "\n";

	// Выводим кратчайшие расстояния до всех вершин
	for (auto &vertex: graph) {
		cout << "Кратчайший путь до вершины " << vertex.id + 1 << " - " << vertex.distance << endl;
	}

	return 0;
}
