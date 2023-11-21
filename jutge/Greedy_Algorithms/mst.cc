#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int INF = INT_MAX;

struct Edge {
  int from, to, cost;
};

using Graph = vector<vector<Edge>>;

int main() {
  int n, m;

  while (cin >> n >> m) {
    int weight = 0;
    vector<bool> visited(n, false);
    Graph G(n);
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        q;

    for (int i = 0; i < m; ++i) {
      int u, v, w;
      cin >> u >> v >> w;
      G[u - 1].push_back(Edge{u - 1, v - 1, w});
      G[v - 1].push_back(Edge{v - 1, u - 1, w});
    }

    int idx = 0;
    int nodes_count = 0;
    while (nodes_count < n-1) {
      visited[idx] = true;
      for (Edge e : G[idx]) {
        if (not visited[e.to]) {
          q.push({e.cost, e.to});
        }
      }
      while(not q.empty() and visited[q.top().second]) {
        q.pop();
      }
      if (not q.empty()){
        idx = q.top().second;
        weight += q.top().first;
        q.pop();
        ++nodes_count;
      }
    }
    cout << weight << endl;
  }

  return 0;
}
