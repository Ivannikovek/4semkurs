#include <iostream>
#include "FFA.h"

int main() {
	FFA test("test.txt");
	std::cout << "Max flow = " << test.max_flow() << std::endl << std::endl;
	std::cout << "Input graph:" << std::endl;
	test.print_graph();
	std::cout << std::endl;
	std::cout << "Flow graph:" << std::endl;
	test.print_flow_edge();
}