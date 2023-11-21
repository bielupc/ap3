#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;


const int INF = INT_MAX;

struct Edge {
  int from, to, cost;
};

using Graph = vector<vector<Edge>>;

int dijkstra(const Graph& G, const int x, const int y){
  vector<int> dist(G.size(), INF);
  dist[x] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
  q.push({0, x});

  while (not q.empty()) {
    int u = q.top().second;
    int w = q.top().first;
    q.pop();

    for(const Edge& e: G[u]){
      if (dist[e.to] > dist[u] + e.cost) {
        dist[e.to] = dist[u] + e.cost;
        q.push({dist[e.to],e.to});
      }
    }
  }
  return dist[y];
}
  

int main (){
  int n, m;

  while (cin >> n >> m) {

    Graph G(n);

    for (int i = 0; i < m; i++) {
      int u, v, c;
      cin >> u >> v >> c;
      G[u].push_back(Edge{u, v, c});
    }

    int x, y;
    cin >> x >> y;
    
    int result = dijkstra(G, x, y);
    if (result == INF){
      cout << "no path from " << x << " to " << y << endl;
    }
    else{
      cout << result << endl;
    }
    
  }
  
  return 0;
}

