#include<iostream>
#include<fstream>
#include<vector>
#include<list>

using namespace std;

//Macierz Sasiedztwa
vector<vector<int>> AdjacencyMatrix(int rows, int columns) {
	ifstream adjacency_matrix_data("data.txt");
	if (adjacency_matrix_data) {
		cout << "Plik otwarty\n";
		vector<vector<int>> adjacency_matrix(rows, vector<int>(columns, 0));

		//Insert Values
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				adjacency_matrix_data >> adjacency_matrix[i][j];
			}
		}

		return adjacency_matrix;

	}
	else {
		cout << "Nie udalo sie otworzyc pliku\n";
		return {};
	}

}

struct Edge {
	int from, to, weight;
};

list<Edge> EdgeListBasedOnAM(vector<vector<int>>& adjacency_matrix, int rows, int columns) {
	list<Edge> edge_list;
	//Insert Values
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (adjacency_matrix[i][j] != 0) {
				edge_list.push_back({ i + 1, j + 1, adjacency_matrix[i][j] });
			}
		}
	}
	//Show Values
	for (auto& edge : edge_list) {
		cout << "from: " << edge.from << " to: " << edge.to << " weight: " << edge.weight << endl;
	}
	return edge_list;
}


void AdjacencyListBasedOnEL(list<Edge> edge_list, int rows, int columns) {
	vector<vector<pair<int, int>>> adjacency_list(rows + 1);
	//Get Values From Edge List
	for (auto& edge : edge_list) {
		int from = edge.from;
		int to = edge.to;
		int weight = edge.weight;

		adjacency_list[from].emplace_back(to, weight);

	}

	//Show Values
	cout << "Lista sasiedztwa:\n";
	for (int i = 1; i <= rows; i++) {
		cout << i << ": ";
		for (auto& neighbor : adjacency_list[i]) {
			cout << "to: " << neighbor.first << " weight: " << neighbor.second << ", ";
		}
		cout << endl;
	}
}

void PrimAlgorithm(list<Edge>& edge_list, int vertices, int columns, int start) {
	vector<int> color(vertices, 0);
	list<Edge> result; 
	color[start - 1] = 1;
	while (result.size() < vertices - 1) {
		Edge min_edge = { 0, 0, INT_MAX };

		//szukamy minimalnej krawedzi dla wierzcholkow z ciagu
		for (auto& edge : edge_list) {
			if (color[edge.from - 1] == 1 && color[edge.to - 1] == 0 && edge.weight < min_edge.weight) {
				min_edge = edge;
			}
		}


		//dodajemy cala krawedz do listy koncowej
		result.emplace_back(min_edge);
		color[min_edge.to - 1] = 1;

		cout << "dodano: " << min_edge.from << " do " << min_edge.to << " waga: " << min_edge.weight << endl;
	}

	cout << "\nminimalne drzewo rozpinajace:\n";
	for (auto& edge : result) {
		cout << "od: " << edge.from << " do: " << edge.to << " waga: " << edge.weight << endl;
	}
}

int main() {
	int rows = 8;
	int vertices = 8;
	int columns = 8;

	int start;
	cout << "start with the number from range 1 to 8: ";
	cin >> start;


	//Lista krawedzi na podstawie macierzy sasiedztwa
	vector<vector<int>> adjacency_matrix = AdjacencyMatrix(rows, columns);
	list<Edge> edge_list = EdgeListBasedOnAM(adjacency_matrix, rows, columns);

	//Lista sasiedztwa na podstawie listy krawedzi
	AdjacencyListBasedOnEL(edge_list, rows, columns);

	PrimAlgorithm(edge_list, vertices, columns, start);
	return 0;

}