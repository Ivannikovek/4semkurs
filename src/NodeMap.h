#ifndef NODE_MAP_H__

#define NODE_MAP_H__

#include <string>

class NodeMap {
public:
	struct Node;

	struct Edge {
		Edge(char key);

		char key;
		int weight;
		bool is_visited;

		Node* node;

		Edge* next;
		Edge* previous;
	};

	struct Node {
		Node(char key);

		char key;
		bool is_visited;

		Edge* head;
		Edge* tail;

		Node* next;
		Node* previous;
	};

public:
	NodeMap();
	NodeMap(const NodeMap& other) = delete;
	NodeMap& operator=(const NodeMap& other) = delete;
	~NodeMap();

	Node* add(char key);
	Edge* addEdge(char key1, char key2, int weight);
	std::string find_path();
	Node* get_node(char key) const;
	Edge* get_edge(char key1, char key2) const;
	Node* get_head() const;

	int sum(const NodeMap& other) const;
	int min() const;

private:
	void clear();
	std::string find_path(Node* cur);

	int cur_min;
	int size;
	Node* head;
	Node* tail;
};

#endif //!NODE_MAP_H__ 