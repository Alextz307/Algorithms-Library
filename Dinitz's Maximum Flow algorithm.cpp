#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

ifstream fin("maxflow.in");
ofstream fout("maxflow.out");

struct edge {
  int u, v, c;

  edge() {}

  edge(int _u, int _v, int _c) : u(_u), v(_v), c(_c) {}
};

struct Dinic {
  int n, m = 0, s, t;
  vector<edge> edges;
  vector<vector<int>> g;
  vector<int> q, level, ptr;

  Dinic(int _n, int _m, int _s, int _t) : n(_n), s(_s), t(_t) {
    edges.resize(2 * _m);
    g.resize(n + 1);
    q.resize(n + 1);
    level.resize(n + 1);
    ptr.resize(n + 1);
  }

  void addEdge(int u, int v, int c) {
    g[u].emplace_back(m);
    edges[m++] = {u, v, c};
    
    g[v].emplace_back(m);
    edges[m++] = {v, u, 0};
  }

  bool bfs() {
    for (int i = 1; i <= n; ++i) {
      level[i] = -1;
    }
    
    level[s] = 0;
    int l = 0, r = -1;
    q[++r] = s;
    
    while (l <= r) {
      int u = q[l++];
      
      for (int id : g[u]) {
        if (level[edges[id].v] == -1 && edges[id].c) {
          level[edges[id].v] = level[u] + 1;
          q[++r] = edges[id].v;
        }
      }
    }
    
    return level[t] != -1;
  }

  int dfs(int u, int flow) {
    if (flow == 0) {
      return 0;
    }
    
    if (u == t) {
      return flow;
    }
    
    for (int &p = ptr[u]; p < (int)g[u].size(); ++p) {
      int id = g[u][p];
      int v = edges[id].v;
      int c = edges[id].c;
      
      if (level[v] != level[u] + 1 || c == 0) {
        continue;
      }
      
      int minFlow = dfs(v, min(flow, c));
      
      if (minFlow == 0) {
        continue;
      }
      
      edges[id].c -= minFlow;
      edges[id ^ 1].c += minFlow;
      
      return minFlow;
    }
    
    return 0;
  }

  int maxFlow() {
    int flow = 0;
    
    while (bfs()) {
      for (int i = 1; i <= n; ++i) {
        ptr[i] = 0;
      }
      
      while (int newFlow = dfs(s, INF)) {
        flow += newFlow;
      }
    }
    
    return flow;
  }
};

void testCase() {
  int n, m;
  fin >> n >> m;
  
  Dinic g(n, m, 1, n);
  
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    fin >> u >> v >> w;
    g.addEdge(u, v, w);
  }
  
  fout << g.maxFlow() << '\n';
}

int main() {
  int tests = 1;
  
  for (int tc = 0; tc < tests; ++tc) {
    testCase();
  }
  
  fin.close();
  fout.close();
  
  return 0;
}
