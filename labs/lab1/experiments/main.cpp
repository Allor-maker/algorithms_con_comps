#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>
#include <fstream>
#include "calc.h"
#include <set>

Graph generate_random_graph(int n, int m)
{
    if (n <= 1)
    {
        return Graph(n);
    }

    long long max_edges = (long long)n * (n - 1) / 2;
    if (m > max_edges) {
        throw(std::exception("incorrect number of edges"));
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, n - 1);

    std::set<std::pair<int, int>> edges_set;

    while (edges_set.size() < m) {
        int u = distrib(gen);
        int v = distrib(gen);

        if (u != v) {
            if (u > v) {
                std::swap(u, v);
            }
            edges_set.insert({ u, v });
        }
    }

    std::vector<std::pair<int, int>> edges_vec(edges_set.begin(), edges_set.end());

    return Graph(n, edges_vec);
}

void run_performance_experiments()
{
    std::cout << "Experiments 1-3." << std::endl;

    std::ofstream file1("exp_3_1_dense.csv");
    std::ofstream file2("exp_3_2_tree.csv");
    std::ofstream file3("exp_3_3_sparse.csv");

    file1 << "n,T_naive_ms,T_ram_ms\n";
    file2 << "n,T_naive_ms,T_ram_ms\n";
    file3 << "n,T_naive_ms,T_ram_ms\n";

   
    for (int n = 1; n <= 1001; n += 10)
    {

        int m1 = (long long)n * n / 10;
        int m2 = n - 1;
        int m3 = 0;
        if (n > 1)
        {
            m3 = static_cast<int>(log2(n));
        }
        
        Graph g1 = generate_random_graph(n, m1);
        auto start1_naive = std::chrono::steady_clock::now();
        g1.component_naive();
        auto end1_naive = std::chrono::steady_clock::now();
        auto t1_naive = std::chrono::duration<double>(end1_naive - start1_naive);

        auto start1_ram = std::chrono::steady_clock::now();
        g1.component_ram();
        auto end1_ram = std::chrono::steady_clock::now();
        auto t1_ram = std::chrono::duration<double>(end1_ram - start1_ram);
        file1 << n << "," << t1_naive.count() << "," << t1_ram.count() << "\n";

        Graph g2 = generate_random_graph(n, m2);
        auto start2_naive = std::chrono::steady_clock::now();
        g2.component_naive();
        auto end2_naive = std::chrono::steady_clock::now();
        auto t2_naive = std::chrono::duration<double>(end2_naive - start2_naive);

        auto start2_ram = std::chrono::steady_clock::now();
        g2.component_ram();
        auto end2_ram = std::chrono::steady_clock::now();
        auto t2_ram = std::chrono::duration<double>(end2_ram - start2_ram);
        file2 << n << "," << t2_naive.count() << "," << t2_ram.count() << "\n";

        Graph g3 = generate_random_graph(n, m3);
        auto start3_naive = std::chrono::steady_clock::now();
        g3.component_naive();
        auto end3_naive = std::chrono::steady_clock::now();
        auto t3_naive = std::chrono::duration<double>(end3_naive - start3_naive);

        auto start3_ram = std::chrono::steady_clock::now();
        g3.component_ram();
        auto end3_ram = std::chrono::steady_clock::now();
        auto t3_ram = std::chrono::duration<double>(end3_ram - start3_ram);
        file3 << n << "," << t3_naive.count() << "," << t3_ram.count() << "\n";
    }

    file1.close();
    file2.close();
    file3.close();
    std::cout << "Success. Relults in files 1-3." << std::endl;
}

bool is_connected(int n, const std::vector<int>& components) 
{
    if (n <= 1)
    {
        return true;
    }
    int first_comp = components[0];
    for (int i = 1; i < components.size(); i++) {
        if (components[i] != first_comp) {
            return false;
        }
    }
    return true;
}

void run_connectivity_experiment()
{
    std::cout << "\nExperiment 4." << std::endl;

    std::ofstream file4("exp_3_4_connectivity.csv");
    file4 << "n,m_required\n";

    for (int n = 1; n <= 1001; n += 10)
    {
        if (n == 1) 
        {
            file4 << n << ",0\n";
            continue;
        }

        std::vector<std::pair<int, int>> all_possible_edges;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                all_possible_edges.push_back({ i, j });
            }
        }
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(all_possible_edges.begin(), all_possible_edges.end(), g);

        Graph cur_graph(n);
        int edges_added = 0;
        for (const auto& edge : all_possible_edges) {
            cur_graph.add_edge(edge);
            edges_added++;

            std::vector<int> components = cur_graph.component_ram();
            if (is_connected(n, components))
            {
                break;
            }
        }
        file4 << n << "," << edges_added << "\n";
    }

    file4.close();
    std::cout << "Success. Results in file 4." << std::endl;
}


int main()
{
    run_performance_experiments();
    run_connectivity_experiment();

    std::cout << "\nAll experiments successfully finished." << std::endl;
    return 0;
}