#include "pch.h"

#include "../test/FFA.h"
#include "../test/FFA.cpp"

#include "../test/NodeMap.h"
#include "../test/NodeMap.cpp"

TEST(FFA, createGraph) {
	FFA test("test.txt");
	NodeMap::Node* node = test.get_graph().get_head();

	size_t count = 0;
	while (node != nullptr) {
		++count;
		node = node->next;
	}

	ASSERT_EQ(count, 6u);

	node = test.get_graph().get_head();
	NodeMap::Edge* edge = node->head;

	count = 0;
	while (edge != nullptr) {
		++count;
		edge = edge->next;
	}

	ASSERT_EQ(count, 2u);

	node = node->next;
	edge = node->head;

	count = 0;
	while (edge != nullptr) {
		++count;
		edge = edge->next;
	}

	ASSERT_EQ(count, 1u);

	node = node->next;
	edge = node->head;

	count = 0;
	while (edge != nullptr) {
		++count;
		edge = edge->next;
	}

	ASSERT_EQ(count, 1u);

	node = node->next;
	edge = node->head;

	count = 0;
	while (edge != nullptr) {
		++count;
		edge = edge->next;
	}

	ASSERT_EQ(count, 2u);
}

TEST(FFA, createMaxFlow) {
	FFA test("test.txt");
	ASSERT_EQ(test.max_flow(), 12);
}

TEST(NodeMap, add) {
	NodeMap test;

	test.add('a');
	test.add('b');
	test.add('c');
	test.add('d');
	test.add('e');
	test.add('f');

	NodeMap::Node* node = test.get_head();

	size_t count = 0;
	while (node != nullptr) {
		++count;
		node = node->next;
	}

	ASSERT_EQ(count, 6u);
}

TEST(NodeMap, addEdge) {
	std::ifstream file("test.txt");
	if (!file.is_open()) {
		std::cerr << "File didn't open." << std::endl;
		return;
	}

	char v1, v2;
	int weight;
	NodeMap test;
	size_t count = 7;

	for (size_t i = 0; i < count; ++i) {
		file >> v1 >> v2 >> weight;
		test.addEdge(v1, v2, weight);
	}

	file.close();

	count = 0;

	NodeMap::Node* node = test.get_head();

	while (node != nullptr) {
		++count;
		node = node->next;
	}

	ASSERT_EQ(count, 6u);

	node = test.get_head();
	count = 0;

	NodeMap::Edge* edge = node->head;
	while (edge != nullptr) {
		++count;
		edge = edge->next;
	}

	ASSERT_EQ(count, 2u);

	node = node->next;
	count = 0;

	edge = node->head;
	while (edge != nullptr) {
		++count;
		edge = edge->next;
	}

	ASSERT_EQ(count, 1u);

	node = node->next;
	count = 0;

	edge = node->head;
	while (edge != nullptr) {
		++count;
		edge = edge->next;
	}

	ASSERT_EQ(count, 1u);

	node = node->next;
	count = 0;

	edge = node->head;
	while (edge != nullptr) {
		++count;
		edge = edge->next;
	}

	ASSERT_EQ(count, 2u);
}

TEST(NodeMap, findPath) {
	std::ifstream file("test.txt");
	if (!file.is_open()) {
		std::cerr << "File didn't open." << std::endl;
		return;
	}

	char v1, v2;
	int weight;
	NodeMap test;
	size_t count = 7;

	for (int i = 0; i < count; ++i) {
		file >> v1 >> v2 >> weight;
		test.addEdge(v1, v2, weight);
	}

	file.close();

	ASSERT_STREQ(test.find_path().c_str(), "SbdecT");
}

TEST(NodeMap, sum) {
	std::ifstream file("test.txt");
	if (!file.is_open()) {
		std::cerr << "File didn't open." << std::endl;
		return;
	}

	char v1, v2;
	int weight;
	NodeMap test;
	size_t count = 7;

	for (int i = 0; i < count; ++i) {
		file >> v1 >> v2 >> weight;
		test.addEdge(v1, v2, weight);
	}

	file.close();

	ASSERT_EQ(test.sum(test), 0);
}

TEST(NodeMap, getNode) {
	std::ifstream file("test.txt");
	if (!file.is_open()) {
		std::cerr << "File didn't open." << std::endl;
		return;
	}

	char v1, v2;
	int weight;
	NodeMap test;
	size_t count = 7;

	for (int i = 0; i < count; ++i) {
		file >> v1 >> v2 >> weight;
		test.addEdge(v1, v2, weight);
	}

	file.close();

	NodeMap::Node* node = test.get_node('S');

	ASSERT_EQ(node->key, 'S');

	count = 0;
	NodeMap::Edge* edge = node->head;

	while (edge != nullptr) {
		++count;
		edge = edge->next;
	}

	ASSERT_EQ(count, 2u);
}