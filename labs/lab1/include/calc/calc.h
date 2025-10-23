#pragma once
#include <vector>

class DSU
{
private:
	int n = 0;
	std::vector<int> comp_id;
public:
	DSU(int num);

	int find(const int vert) const;
	void union_sets(const int& comp1, const int& comp2);

	std::vector<int> get_comps() const;
};

class Graph
{
private:
	int n = 0;
	std::vector<std::pair<int, int>> edges;
public:
	Graph();
	Graph(int n);
	Graph(int num_vertices, const std::vector<std::pair<int, int>>& edgs);
	Graph(const Graph& g);
	Graph(const std::vector<std::vector<int>>& adj_matrix);
	Graph(int num_vert, const std::vector<std::vector<int>>& adj_list);

	void add_edge(const std::pair<int, int>& p);
	void add_vertice();

	int get_num_vert() const;
	std::vector<std::pair<int, int>> get_edges();

	std::vector<int> component_naive() const;
	std::vector<int> component_ram() const;
};