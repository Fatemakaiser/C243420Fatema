#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>

using namespace std;

struct Edge {
    int u, v, exp;
};

class DisjointSet {
private:
    vector<int> parent;
public:
    DisjointSet(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

int n, m;
vector<vector<pair<int, int>>> adj;
vector<long long> subtree_size;
vector<long long> binary_sum;

void dfs(int u, int p) {
    subtree_size[u] = 1;
    for (auto& edge : adj[u]) {
        int v = edge.first;
        int exp = edge.second;
        if (v != p) {
            dfs(v, u);
            subtree_size[u] += subtree_size[v];

            long long paths = subtree_size[v] * (n - subtree_size[v]);
            binary_sum[exp] += paths;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (cin >> n >> m) {
        vector<Edge> edges(m);
        for (int i = 0; i < m; ++i) {
            cin >> edges[i].u >> edges[i].v >> edges[i].exp;
        }

        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.exp < b.exp;
        });

        DisjointSet dsu(n);
        adj.resize(n + 1);
        int edges_count = 0;

        for (const auto& edge : edges) {
            if (dsu.unite(edge.u, edge.v)) {
                adj[edge.u].push_back({edge.v, edge.exp});
                adj[edge.v].push_back({edge.u, edge.exp});
                edges_count++;
                if (edges_count == n - 1) break;
            }
        }

        // Maximum possible exponent is M, but carrying over can expand it up to M + 2 * log2(N)
        binary_sum.resize(m + 64, 0);
        subtree_size.resize(n + 1, 0);

        dfs(1, 0);

        long long carry = 0;
        string result = "";
        for (size_t i = 0; i < binary_sum.size(); ++i) {
            long long current = binary_sum[i] + carry;
            binary_sum[i] = current % 2;
            carry = current / 2;
        }

        int last_one = binary_sum.size() - 1;
        while (last_one >= 0 && binary_sum[last_one] == 0) {
            last_one--;
        }

        if (last_one < 0) {
            cout << "0\n";
        } else {
            for (int i = last_one; i >= 0; --i) {
                result += to_string(binary_sum[i]);
            }
            cout << result << "\n";
        }
    }

    return 0;
}
