#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;
};

struct CompareEdges {
    bool operator()(const Edge& a, const Edge& b) const {
        if (a.weight != b.weight) {
            return a.weight < b.weight;
        }
        return (a.u + a.v + a.weight) < (b.u + b.v + b.weight);
    }
};

class DisjointSet {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
            return true;
        }
        return false;
    }
};

int kruskals(int g_nodes, vector<int> g_from, vector<int> g_to, vector<int> g_weight) {
    int m = g_weight.size();
    vector<Edge> edges(m);

    for (int i = 0; i < m; ++i) {
        edges[i] = {g_from[i], g_to[i], g_weight[i]};
    }

    sort(edges.begin(), edges.end(), CompareEdges());

    DisjointSet dsu(g_nodes);
    int total_weight = 0;
    int edges_count = 0;

    for (const auto& edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            total_weight += edge.weight;
            edges_count++;

            if (edges_count == g_nodes - 1) {
                break;
            }
        }
    }

    return total_weight;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int g_nodes, g_edges;
    if (cin >> g_nodes >> g_edges) {
        vector<int> g_from(g_edges);
        vector<int> g_to(g_edges);
        vector<int> g_weight(g_edges);

        for (int i = 0; i < g_edges; ++i) {
            cin >> g_from[i] >> g_to[i] >> g_weight[i];
        }

        int result = kruskals(g_nodes, g_from, g_to, g_weight);
        cout << result << "\n";
    }

    return 0;
}