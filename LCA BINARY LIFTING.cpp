void dfs(int u, int p) {
  anc[u][0] = parent;
  for (int i = 1; i <= lg; ++i)
    anc[u][i] = anc[anc[u][i - 1]][i - 1];
  for (int v : G[u])
    if (v != p) {
      level[v] = level[u] + 1;
      dfs(v, u);
    }
}

int lca(int u, int v) {
  if (level[u] < level[v])
    swap(u, v);
  for (int i = lg; i >= 0; --i)
    if (level[u] - (1 << i) >= level[v])
      u = anc[u][i];
  if (u == v)
    return u;
  for (int i = lg; i >= 0; --i)
    if (anc[u][i] != anc[v][i]) {
      u = anc[u][i];
      v = anc[v][i];
    }
  return anc[u][0];
}