#ifndef FFA_H__

#define FFA_H__

#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>

#include "NodeMap.h"

//Ford–Fulkerson algorithm
class FFA {
public:
	FFA(const std::string& path);
	
	int max_flow();
	void print_graph() const;
	void print_flow_edge() const;

	const NodeMap& get_graph() const;
	const NodeMap& get_flow() const;
private:
	void create_graph(const std::string& path);

	NodeMap graph;
	NodeMap flow_graph;
	std::string path;
};

#endif //!FFA_H__