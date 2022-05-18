#include "FFA.h"

FFA::FFA(const std::string& path) {
	create_graph(path);
};

void FFA::create_graph(const std::string& path) {
	std::ifstream file("test.txt");
	if (!file.is_open())
		throw std::runtime_error("File 'test.txt' didn't open.\n");

	FFA::path = path;

	std::string in;
	int count = 0;
	while (std::getline(file, in))
		count++;

	file.close();

	file.open("test.txt");
	char v1, v2;
	int weight;

	for (int i = 0; i < count; i++)
		if (file >> v1 >> v2 >> weight)
			graph.addEdge(v1, v2, weight);
		else
			throw std::runtime_error("Eror input from 'test.txt'.\n");

	file.close();

	file.open("test.txt");

	for (int i = 0; i < count; i++) {
		file >> v1 >> v2 >> weight;
		flow_graph.addEdge(v1, v2, weight);
	}

	file.close();
}

int FFA::max_flow() {
	std::string path;
	int min_weight;
	path = flow_graph.find_path();
	min_weight = flow_graph.min();

	while (path.size()) {
		for (int u = 0; u < path.size() - 1; u++) {
			int v = u + 1;
			flow_graph.get_edge(path[u], path[v])->weight -= min_weight;
			if (flow_graph.get_edge(path[v], path[u]))
				flow_graph.get_edge(path[v], path[u])->weight += min_weight;
			else
				flow_graph.addEdge(path[v], path[u], min_weight);
		}
		path = flow_graph.find_path();
		min_weight = flow_graph.min();
	}
	return graph.sum(flow_graph);
}

void FFA::print_graph() const {
	NodeMap::Node* node = graph.get_head();

	while (node) {
		NodeMap::Edge* edge = node->head;
		while (edge) {
			std::cout << node->key << " " << edge->key << " " << edge->weight << std::endl;
			edge = edge->next;
		}
		node = node->next;
	}
}

void FFA::print_flow_edge() const {
	NodeMap::Node* node = graph.get_head();

	while (node) {
		NodeMap::Edge* edge = node->head;
		while (edge) {
			NodeMap::Edge* flow = flow_graph.get_edge(node->key, edge->key);
			std::cout << node->key << " " << edge->key << " " << edge->weight - flow->weight << std::endl;
			edge = edge->next;
		}
		node = node->next;
	}
}

const NodeMap& FFA::get_graph() const {
	return graph;
};

const NodeMap& FFA::get_flow() const {
	return flow_graph;
};