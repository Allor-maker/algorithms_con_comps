#include <gtest.h>
#include "calc/calc.h"
#include <map>
#include <vector>

class GraphTest : public ::testing::Test {
protected:

    std::vector<int> normalize_components(const std::vector<int>& comps) {
        if (comps.empty()) return {};
        std::vector<int> result = comps;
        std::map<int, int> dict;
        int next_id = 0;

        for (int& id : result) {
            if (dict.find(id) == dict.end()) {
                dict[id] = next_id++;
            }
            id = dict[id];
        }
        return result;
    }

    Graph create_graph(int num, const std::vector<std::vector<int>>& adj_list) {
        return Graph(num, adj_list);
    }
};


TEST_F(GraphTest, isolated_vertex)
{
    Graph g = create_graph(1, { {} });

    ASSERT_EQ(g.component_naive(), (std::vector<int>{0}));
    ASSERT_EQ(g.component_ram(), (std::vector<int>{0}));
}

TEST_F(GraphTest, simple_single_edge)
{
    Graph g = create_graph(2, { {1}, {0} });

    ASSERT_EQ(g.component_naive(), (std::vector<int>{0, 0}));
    ASSERT_EQ(g.component_ram(), (std::vector<int>{0, 0}));
}

TEST_F(GraphTest, two_simple_components)
{
    Graph g = create_graph(4, { {1}, {0}, {3}, {2} });

    ASSERT_EQ(normalize_components(g.component_naive()), (std::vector<int>{0, 0, 1, 1}));
    ASSERT_EQ(normalize_components(g.component_ram()), (std::vector<int>{0, 0, 1, 1}));
}

TEST_F(GraphTest, simple_chain_graph)
{
    Graph g = create_graph(5, { {1}, {0, 2}, {1, 3}, {2, 4}, {3} });

    ASSERT_EQ(normalize_components(g.component_naive()), (std::vector<int>{0, 0, 0, 0, 0}));
    ASSERT_EQ(normalize_components(g.component_ram()), (std::vector<int>{0, 0, 0, 0, 0}));
}

TEST_F(GraphTest, simple_cycle)
{
    Graph g = create_graph(3, { {1, 2}, {0, 2}, {0, 1} });

    ASSERT_EQ(normalize_components(g.component_naive()), (std::vector<int>{0, 0, 0}));
    ASSERT_EQ(normalize_components(g.component_ram()), (std::vector<int>{0, 0, 0}));
}

TEST_F(GraphTest, star_graph)
{
    Graph g = create_graph(4, { {1, 2, 3}, {0}, {0}, {0} });

    ASSERT_EQ(normalize_components(g.component_naive()), (std::vector<int>{0, 0, 0, 0}));
    ASSERT_EQ(normalize_components(g.component_ram()), (std::vector<int>{0, 0, 0, 0}));
}

TEST_F(GraphTest, isolated_graph)
{
    Graph g = create_graph(5, { {}, {}, {}, {}, {} });

    ASSERT_EQ(normalize_components(g.component_naive()), (std::vector<int>{0, 1, 2, 3, 4}));
    ASSERT_EQ(normalize_components(g.component_ram()), (std::vector<int>{0, 1, 2, 3, 4}));
}

TEST_F(GraphTest, graph_with_bridge)
{
    Graph g = create_graph(5, { {1}, {0, 2}, {1, 3, 4}, {2}, {2} });
 
    ASSERT_EQ(normalize_components(g.component_naive()), (std::vector<int>{0, 0, 0, 0, 0}));
    ASSERT_EQ(normalize_components(g.component_ram()), (std::vector<int>{0, 0, 0, 0, 0}));
}

TEST_F(GraphTest, four_compotents_graph)
{
    Graph g = create_graph(5, { {1}, {0},{},{},{} });

    ASSERT_EQ(normalize_components(g.component_naive()), (std::vector<int>{0, 0, 1, 2, 3}));
    ASSERT_EQ(normalize_components(g.component_ram()), (std::vector<int>{0, 0, 1, 2, 3}));
}

TEST_F(GraphTest, big_connected_graph)
{
    Graph g = create_graph(8, { {1, 2}, {0, 3}, {0, 4}, {1, 5}, {2, 6}, {3, 7}, {4, 7}, {5, 6} });

    ASSERT_EQ(normalize_components(g.component_naive()), (std::vector<int>{0, 0, 0, 0, 0, 0, 0, 0}));
    ASSERT_EQ(normalize_components(g.component_ram()), (std::vector<int>{0, 0, 0, 0, 0, 0, 0, 0}));
}

TEST_F(GraphTest, expect_throw_with_incorrect_num_vert)
{
    ASSERT_ANY_THROW(create_graph(3, { {1,2},{} }));
}

TEST_F(GraphTest, expect_throw_adding_edge_with_not_exist_vert)
{
    Graph g(3);

    ASSERT_ANY_THROW(g.add_edge({ 0,3 }));
}

TEST_F(GraphTest, expect_correct_adding_edge)
{
    Graph g(3);
    g.add_edge({ 0,1 });

    ASSERT_EQ(g.get_edges(), (std::vector<std::pair<int, int>>{{0,1}}));
}

TEST_F(GraphTest, expect_correct_adding_vertex)
{
    Graph g(3);
    g.add_vertice();

    ASSERT_EQ(g.get_num_vert(), 4);
}




TEST(DSUTest, initialization_and_find) {
    DSU dsu(5);

    ASSERT_EQ(dsu.find(0), 0);
    ASSERT_EQ(dsu.find(4), 4);
    ASSERT_EQ(dsu.get_comps(), (std::vector<int>{0, 1, 2, 3, 4}));
}

TEST(DSUTest, simple_union_two_sets) {
    DSU dsu(4);

    dsu.union_sets(dsu.find(0), dsu.find(1));

    ASSERT_EQ(dsu.get_comps(), (std::vector<int>{0, 0, 2, 3}));
    ASSERT_EQ(dsu.find(0), dsu.find(1));
}

TEST(DSUTest, union_three_sets_via_center) {
    DSU dsu(5);

    dsu.union_sets(dsu.find(0), dsu.find(4));
    dsu.union_sets(dsu.find(1), dsu.find(4));
    dsu.union_sets(dsu.find(2), dsu.find(4));

    ASSERT_EQ(dsu.get_comps(), (std::vector<int>{2, 2, 2, 3, 2}));
}

TEST(DSUTest, union_already_connected) {
    DSU dsu(3);

    dsu.union_sets(dsu.find(0), dsu.find(1));

    ASSERT_NO_THROW(dsu.union_sets(dsu.find(0), dsu.find(1)));
}

TEST(DSUTest, sequential_union) {
    DSU dsu(4);

    dsu.union_sets(dsu.find(0), dsu.find(1));
    dsu.union_sets(dsu.find(1), dsu.find(2));
    dsu.union_sets(dsu.find(2), dsu.find(3));

    ASSERT_EQ(dsu.get_comps(), (std::vector<int>{0, 0, 0, 0}));
}