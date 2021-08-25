struct flow_edge {
    int u, v, cap;

    flow_edge(int _u, int _v, int _cap) : u(_u), v(_v), cap(_cap) {}
};

struct Dinic {
  int n, m = 0, s, t;
  vector<flow_edge> edges;
  vector<vector<int>> adj;
  vector<int> level, ptr;
  queue<int> q;

  Dinic(int N, int source, int sink) : n(N), s(source), t(sink) {
    adj.resize(n + 1);
    level.resize(n + 1);
    ptr.resize(n + 1);
  }

  void add_edge(int u, int v, int cap) {
    edges.emplace_back(u, v, cap);
    adj[u].emplace_back(m++);
    edges.emplace_back(v, u, 0);
    adj[v].emplace_back(m++);
  }

  bool bfs() {
    while (!q.empty()) {
      int curr = q.front();
      q.pop();
      for (int id : adj[curr])
        if (level[edges[id].v] == -1 && edges[id].cap) {
          level[edges[id].v] = level[curr] + 1;
          q.emplace(edges[id].v);
        }
    }
    return level[t] != -1;
  }

  int dfs(int u, int curr_flow) {
    if (curr_flow == 0)
      return 0;
    if (u == t)
      return curr_flow;
    for (int& p = ptr[u]; p < static_cast<int>(adj[u].size()); ++p) {
      int id = adj[u][p];
      int v = edges[id].v;
      if (level[u] + 1 != level[v] || edges[id].cap <= 0)
        continue;
      int new_flow = dfs(v, min(curr_flow, edges[id].cap));
      if (new_flow == 0)
        continue;
      edges[id].cap -= new_flow;
      edges[id ^ 1].cap += new_flow;
      return new_flow;
    }
    return 0;
  }

  int max_flow() {
    int flow = 0;
    while (true) {
      fill(level.begin(), level.end(), -1);
      level[s] = 0;
      q.emplace(s);
      if (!bfs())
        break;
      fill(ptr.begin(), ptr.end(), 0);
      while (int curr_flow = dfs(s, INF))
        flow += curr_flow;
    }
    return flow;
  }
};
