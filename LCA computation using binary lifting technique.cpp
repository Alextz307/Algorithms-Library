const int kN = 5e5;
const int kLog = 18;
int timer, tin[1 + kN], tout[1 + kN], depth[1 + kN], lg2[1 + kN], anc[1 + kN][1 + kLog];
vector<pair<int, int>> g[1 + kN];
int64_t dp[1 + kN];

void precalc() { /// !!!
  for (int i = 2; i <= kN; ++i) {
    lg2[i] = lg2[i / 2] + 1;
  }
}

void dfs(int u) {
  tin[u] = ++timer;
  for (int i = 1; i <= kLog; ++i) {
    anc[u][i] = anc[anc[u][i - 1]][i - 1];
    if (anc[u][i] == 0) {
      break;
    }
  }
  for (auto it : g[u]) {
    int v, w;
    tie(v, w) = it;
    if (v != anc[u][0]) {
      anc[v][0] = u;
      depth[v] = depth[u] + 1;
      dp[v] = dp[u] + w;
      dfs(v);
    }
  }
  tout[u] = timer;
}

bool isAncestor(int u, int v) {
  return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int getLca(int u, int v) {
  if (depth[u] < depth[v]) {
    swap(u, v);
  }
  if (isAncestor(v, u)) {
    return v;
  }
  for (int i = lg2[depth[v]]; i >= 0; --i) {
    if (anc[v][i] && !isAncestor(anc[v][i], u)) {
      v = anc[v][i];
    }
  }
  return anc[v][0];
}

int64_t getDist(int u, int v, int lca) {
  return dp[u] + dp[v] - 2 * dp[lca];
}
