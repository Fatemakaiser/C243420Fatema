#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int prims(int n, vector<vector<int>> edges, int start) {
    vector<vector<pair<int, int>>> adj(n + 1);
    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int w = edge[2];
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<bool> visited(n + 1, false);
    int total_weight = 0;

    pq.push({0, start});

    while (!pq.empty()) {
        auto [weight, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;
        total_weight += weight;

        for (const auto& neighbor : adj[u]) {
            int v = neighbor.first;
            int w = neighbor.second;
            if (!visited[v]) {
                pq.push({w, v});
            }
        }
    }

    return total_weight;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (cin >> n >> m) {
        vector<vector<int>> edges(m, vector<int>(3));
        for (int i = 0; i < m; ++i) {
            cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
        }
        int start;
        cin >> start;

        cout << prims(n, edges, start) << "\n";
    }
    return 0;
}