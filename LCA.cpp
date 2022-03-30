const int MAXN = 1 << 15;
const int MAXM = 1 << 16;
int m, tour[MAXM], depth[MAXM], first[MAXN], lg2[MAXM], rmq[17][MAXM];
vector<int> G[MAXN];

void dfs(int u, int level) {
  tour[++m] = u;
  depth[m] = level;
  first[u] = m;
  for (int v : G[u]) {
    dfs(v, level + 1);
    tour[++m] = u;
    depth[m] = level;
  }
}

void compute_rmq() {
  for (int i = 2; i <= m; ++i) {
    lg2[i] = lg2[i >> 1] + 1;
  }
  for (int i = 1; i <= m; ++i) {
    rmq[0][i] = i;
  }
  for (int i = 1; (1 << i) < m; ++i) {
    for (int j = 1; j <= m - (1 << i) + 1; ++j) {
      int l = 1 << (i - 1);
      rmq[i][j] = rmq[i - 1][j];
      if (depth[rmq[i - 1][j + l]] < depth[rmq[i][j]]) {
        rmq[i][j] = rmq[i - 1][j + l];
      }
    }
  }
}

int getLca(int u, int v) {
  int x = first[u], y = first[v];
  if (y < x) {
    swap(x, y);
  }
  int diff = y - x + 1;
  int l = lg2[diff];
  int sol = rmq[l][x];
  int shift = diff - (1 << l);
  if (depth[sol] > depth[rmq[l][x + shift]]) {
    sol = rmq[l][x + shift];
  }
  return tour[sol];
}
