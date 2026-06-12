#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        int total_cost = 0;
        int edges_used = 0;

        vector<bool> in_mst(n, false);
        vector<int> min_dist(n, INT_MAX);

        min_dist[0] = 0;

        while (edges_used < n) {
            int curr_node = -1;
            int curr_min_dist = INT_MAX;

            for (int i = 0; i < n; ++i) {
                if (!in_mst[i] && min_dist[i] < curr_min_dist) {
                    curr_min_dist = min_dist[i];
                    curr_node = i;
                }
            }

            in_mst[curr_node] = true;
            total_cost += curr_min_dist;
            edges_used++;

            for (int next_node = 0; next_node < n; ++next_node) {
                if (!in_mst[next_node]) {
                    int weight = abs(points[curr_node][0] - points[next_node][0]) +
                                 abs(points[curr_node][1] - points[next_node][1]);

                    if (weight < min_dist[next_node]) {
                        min_dist[next_node] = weight;
                    }
                }
            }
        }

        return total_cost;
    }
};
