#include <bits/stdc++.h>

using namespace std;

ifstream fin("lca.in");
ofstream fout("lca.out");

const int NMAX = 2e5 + 5;
int N, Q, M, tour[NMAX], depth[NMAX], first[NMAX], lg2[NMAX], rmq[18][NMAX];
vector<int> G[NMAX];

void dfs(int u, int level) {
  tour[++M] = u;
  depth[M] = level;
  first[u] = M;
  for (int v : G[u]) {
    dfs(v, level + 1);
    tour[++M] = u;
    depth[M] = level;
  }
}

void compute_rmq() {
  for (int i = 2; i <= M; ++i)
    lg2[i] = lg2[i >> 1] + 1;
  for (int i = 1; i <= M; ++i)
    rmq[0][i] = i;
  for (int i = 1; (1 << i) < M; ++i)
    for (int j = 1; j <= M - (1 << i); ++j) {
      int l = 1 << (i - 1);
      rmq[i][j] = rmq[i - 1][j];
      if (depth[rmq[i - 1][j + l]] < depth[rmq[i][j]])
        rmq[i][j] = rmq[i - 1][j + l];
    }
}

int lca(int u, int v) {
  int x = first[u], y = first[v];
  if (x > y)
    swap(x, y);
  int diff = y - x + 1;
  int l = lg2[diff];
  int sol = rmq[l][x];
  int shift = diff - (1 << l);
  if (depth[sol] > depth[rmq[l][x + shift]])
    sol = rmq[l][x + shift];
  return tour[sol];
}

void solve() {
  fin >> N >> Q;
  for (int u = 2; u <= N; ++u) {
    int t;
    fin >> t;
    G[t].emplace_back(u);
  }
  dfs(1, 0);
  compute_rmq();
  for (int q = 0; q < Q; ++q) {
    int u, v;
    fin >> u >> v;
    fout << lca(u, v) << '\n';
  }
}

void close_files() {
  fin.close();
  fout.close();
}

int main() {
  solve();
  close_files();
  return 0;
}
