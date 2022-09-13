#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

ifstream fin("fmcm.in");
ofstream fout("fmcm.out");

void minSelf(int &x, int y) {
  if (y < x) {
    x = y;
  }
}

struct MCMF {
  int n, s, t, maxFlow = 0;
  int64_t minCost = 0;
  vector<vector<int>> g, C, W;
  vector<int> d, dp, par, D;
  vector<bool> inQ;
 
  MCMF(int _n, int _s, int _t) : n(_n), s(_s), t(_t) {
    g.resize(n + 1);
    C.resize(n + 1, vector<int>(n + 1));
    W.resize(n + 1, vector<int>(n + 1));
    d.resize(n + 1, INF);
    dp.resize(n + 1);
    par.resize(n + 1);
    D.resize(n + 1);
    inQ.resize(n + 1);
  }
 
  void addEdge(int u, int v, int c, int w) {
    g[u].emplace_back(v);
    g[v].emplace_back(u);
    C[u][v] += c;
    W[u][v] += w;
    W[v][u] -= w;
  }
 
  void BellmanFord() {
    d[s] = 0;
    queue<int> q;
    q.emplace(s);
    inQ[s] = true;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      inQ[u] = false;
      for (int v : g[u]) {
        if (C[u][v] && d[v] > d[u] + W[u][v]) {
          d[v] = d[u] + W[u][v];
          if (!inQ[v]) {
            q.emplace(v);
            inQ[v] = true;
          }
        }
      }
    }
  }
 
  bool Dijkstra() {
    for (int i = 1; i <= n; ++i) {
      dp[i] = INF;
    }
    dp[s] = 0;
    D[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, s);
    while (!pq.empty()) {
      int cost, u;
      tie(cost, u) = pq.top();
      pq.pop();
      if (cost != dp[u]) {
        continue;
      }
      for (int v : g[u]) {
        if (C[u][v] == 0) {
          continue;
        }
        int newCost = cost + W[u][v] + d[u] - d[v];
        if (newCost < dp[v]) {
          dp[v] = newCost;
          D[v] = D[u] + W[u][v];
          par[v] = u;
          if (v != t) {
            pq.emplace(newCost, v);
          }
        }
      }
    }
    if (dp[t] == INF) {
      return false;
    }
    d = D;
    int minFlow = INF;
    for (int v = t; v != s; v = par[v]) {
      minSelf(minFlow, C[par[v]][v]);
      if (minFlow == 0) {
        return false;
      }
    }
    maxFlow += minFlow;
    minCost += (int64_t)minFlow * D[t];
    for (int v = t; v != s; v = par[v]) {
      C[par[v]][v] -= minFlow;
      C[v][par[v]] += minFlow;
    }
    return true;
  }
 
  pair<int, int64_t> solve() {
    BellmanFord();
    while (Dijkstra());
    return {maxFlow, minCost};
  }
};

void testCase() {
  int n, m, s, t;
  fin >> n >> m >> s >> t;
  MCMF g(n, s, t);
  for (int i = 0; i < m; ++i) {
    int u, v, c, w;
    fin >> u >> v >> c >> w;
    g.addEdge(u, v, c, w);
  }
  fout << g.solve().second << '\n';
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
