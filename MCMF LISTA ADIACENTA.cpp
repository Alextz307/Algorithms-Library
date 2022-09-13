struct edge {
  int v, c, w;
};

void minSelf(int &x, int y) {
  if (y < x) {
    x = y;
  }
}

struct MCMF {
  int n, s, t, idx = 0, maxFlow = 0, minCost = 0;
  vector<vector<int>> g;
  vector<edge> edges;
  vector<int> d, dp, par, lastId, D;
  vector<bool> inQ;

  MCMF(int _n, int _s, int _t) : n(_n), s(_s), t(_t) {
    g.resize(n + 1);
    d.resize(n + 1, INF);
    dp.resize(n + 1, INF);
    par.resize(n + 1);
    lastId.resize(n + 1);
    D.resize(n + 1);
    inQ.resize(n + 1);
  }

  void addEdge(int u, int v, int c, int w) {
    g[u].emplace_back(idx);
    edges.push_back({v, c, w});
    idx += 1;
    g[v].emplace_back(idx);
    edges.push_back({u, 0, -w});
    idx += 1;
  }

  void BellmanFord() {
    d[s] = 0;
    queue<int> q;
    q.emplace(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      inQ[u] = false;
      for (int id : g[u]) {
        int v = edges[id].v, c = edges[id].c, w = edges[id].w;
        if (c && d[v] > d[u] + w) {
          d[v] = d[u] + w;
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
      for (int id : g[u]) {
        int v = edges[id].v, c = edges[id].c, w = edges[id].w;
        if (c) {
          int newCost = cost + w + d[u] - d[v];
          if (newCost < dp[v]) {
            dp[v] = newCost;
            D[v] = D[u] + w;
            par[v] = u;
            lastId[v] = id;
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
    for (int i = t; i != s; i = par[i]) {
      minSelf(minFlow, edges[lastId[i]].c);
      if (minFlow == 0) {
        return false;
      }
    }
    maxFlow += minFlow;
    minCost += minFlow * D[t];
    for (int i = t; i != s; i = par[i]) {
      edges[lastId[i]].c -= minFlow;
      edges[lastId[i] ^ 1].c += minFlow;
    }
    return true;
  }

  pair<int, int> solve() {
    BellmanFord();
    while (Dijkstra());
    return {maxFlow, minCost};
  }
};
