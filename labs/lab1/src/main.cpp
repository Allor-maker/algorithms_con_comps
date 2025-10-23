#include <iostream>
#include "calc.h"

void print_result(const std::vector<int>& comps, const std::string& name) {
    std::cout << name << " result: ";
    for (int id : comps) {
        std::cout << id << " ";
    }
    std::cout << "\n";
}

int main() 
{
    const int N = 5;
    std::vector<std::vector<int>> adj_list = {
        {1, 2},
        {0},
        {0, 3},
        {2},
        {}
    };

    Graph g(N, adj_list);

    std::vector<int> naive_comps = g.component_naive();
    print_result(naive_comps, "Naive Algorithm");

    std::vector<int> ram_comps = g.component_ram();
    print_result(ram_comps, "Ram Algorithm (array)");

    return 0;
}