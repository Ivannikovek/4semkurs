#include "NodeMap.h"

NodeMap::Edge::Edge(char key)
	: key(key), is_visited(false), weight(0), node(nullptr), next(nullptr), previous(nullptr) {};

NodeMap::Node::Node(char key)
	: key(key), is_visited(false), next(nullptr), previous(nullptr), head(nullptr), tail(nullptr) {};

NodeMap::NodeMap()
	: cur_min(10000), size(0), head(nullptr), tail(nullptr) {};

NodeMap::~NodeMap() {
	while (head != nullptr) {
		Node* removing = head;
		head = head->next;
		delete removing;
	}
	head = tail = nullptr; //for case of dangling reference
}

NodeMap::Node* NodeMap::add(char key) {
	if (head == nullptr) {
		head = new Node(key);
		tail = head;
		++size;
		return head;
	}

	Node* new_node = new Node(key);
	tail->next = new_node;
	new_node->previous = tail;
	tail = new_node;
	++size;
	return new_node;
}

NodeMap::Node* NodeMap::get_node(char key) const {
	Node* node = head;

	while (node != nullptr) {
		if (node->key == key)
			return node;

		node = node->next;
	}

	return nullptr;
}

NodeMap::Edge* NodeMap::get_edge(char key1, char key2) const {
	Node* node1 = get_node(key1);

	if (node1 == nullptr)
		return nullptr;

	//searching for edge beetwen key1 and key2
	Edge* edge = node1->head;
	while (edge != nullptr) {
		if (edge->key == key2)
			return edge;

		edge = edge->next;
	}

	return nullptr;
}

NodeMap::Edge* NodeMap::addEdge(char key1, char key2, int weight) {
	Node* node1 = get_node(key1);
	Node* node2 = get_node(key2);

	if (node1 == nullptr)
		node1 = add(key1);

	if (node2 == nullptr)
		node2 = add(key2);

	if (node1->head == nullptr) {
		node1->head = new Edge(key2);
		node1->tail = node1->head;
		node1->head->node = node2;
		node1->head->weight = weight;
		return node1->head;
	}

	Edge* edge = new Edge(key2);
	node1->tail->next = edge;
	edge->previous = node1->tail;
	node1->tail = edge;
	edge->node = node2;
	edge->weight = weight;
	return edge;
}

std::string NodeMap::find_path() {
	cur_min = 10000;
	std::string path = find_path(get_node('S'));
	clear();

	return path;
}

std::string NodeMap::find_path(Node* node) {
	if (node == nullptr)
		return "";

	node->is_visited = true;
	if (node->key == 'T')
		return "T";

	Edge* edge = node->head;
	std::string str;

	while (edge != nullptr) {
		if ((edge->is_visited == false) && (edge->weight != 0)) {
			edge->is_visited = true;
			str = find_path(edge->node);
			if (str.size() != 0) {
				if (edge->weight < cur_min)
					cur_min = edge->weight;

				return node->key + str;
			}
		}
		edge = edge->next;
	}

	return "";
}

void NodeMap::clear() {
	Node* node = head;

	while (node != nullptr) {
		node->is_visited = false;
		Edge* edge = node->head;
		while (edge != nullptr) {
			edge->is_visited = false;
			edge = edge->next;
		}
		node = node->next;
	}
}

NodeMap::Node* NodeMap::get_head() const {
	return head;
};

int NodeMap::sum(const NodeMap& other) const {
	if (head == nullptr)
		return 0;

	Edge* edge = this->get_node('S')->head;

	int sum = 0;
	while (edge != nullptr) {
		sum += edge->weight - other.get_edge('S', edge->key)->weight;
		edge = edge->next;
	}

	return sum;
}

int NodeMap::min() const {
	return cur_min;
};