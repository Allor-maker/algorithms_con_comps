#include "calc.h"

DSU::DSU(int num)
{
	n = num;
	comp_id.resize(n);
	for (int i = 0; i < n; i++)
	{
		comp_id[i] = i;
	}
}

int DSU::find(const int vert) const
{
	return comp_id[vert];
}

void DSU::union_sets(const int& comp1, const int& comp2)
{
	if (comp1 == comp2)
	{
		return;
	}
	for (int i = 0; i < n; i++)
	{
		if (comp_id[i] == comp2)
		{
			comp_id[i] = comp1;
		}
	}
}

std::vector<int> DSU::get_comps() const
{
	return comp_id;
}



Graph::Graph() : n(0)
{	}

Graph::Graph(int n) : n(n)
{	}

Graph::Graph(int num_vertices, const std::vector<std::pair<int, int>>& edgs) : n(num_vertices), edges(edgs)
{	}

Graph::Graph(const Graph& g) : n(g.n), edges(g.edges)
{	}

Graph::Graph(const std::vector<std::vector<int>>& adj_matrix)
{
	n = adj_matrix.size();
	if (n == 0) return;

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (adj_matrix[i][j] > 0)
			{
				edges.push_back({ i, j });
			}
		}
	}
}

Graph::Graph(int num_vert, const std::vector<std::vector<int>>& adj_list)
{
	n = num_vert;
	if (n != adj_list.size())
	{
		throw(std::exception("Incorrect size was given"));
	}
	if (n == 0) return;

	for (int i = 0; i < n; i++)
	{
		for (int neighbor : adj_list[i])
		{
			if (i < neighbor)
			{
				edges.push_back({ i, neighbor });
			}
		}
	}
}

void Graph::add_edge(const std::pair<int, int>& p)
{
	if (p.first > n - 1 || p.second > n - 1)
	{
		throw std::exception("incorrect value of vertice");
	}
	edges.push_back(p);
}

void Graph::add_vertice()
{
	n += 1;
}

int Graph::get_num_vert() const
{
	return n;
}

std::vector<std::pair<int, int>> Graph::get_edges()
{
	return edges;
}

std::vector<int> Graph::component_naive() const
{
	std::vector<int> comp(n);
	for (int i = 0; i < n; i++)
	{
		comp[i] = i;
	}
	int m = edges.size();
	int comp_min = -1;

	int idx1, idx2;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < m; j++)
		{
			idx1 = comp[edges[j].first];
			idx2 = comp[edges[j].second];
			comp_min = std::min(idx1, idx2);

			comp[edges[j].first] = comp_min;
			comp[edges[j].second] = comp_min;
		}
	}
	return comp;
}

std::vector<int> Graph::component_ram() const
{
	DSU comp(n);
	int m = edges.size();

	int comp1, comp2;
	for (int i = 0; i < m; i++)
	{
		comp1 = comp.find(edges[i].first);
		comp2 = comp.find(edges[i].second);
		if (comp1 != comp2)
		{
			comp.union_sets(comp1, comp2);
		}
	}
	return comp.get_comps();
}
