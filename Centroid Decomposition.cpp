#include <bits/stdc++.h>

using namespace std;

const int kN = 1e5;
const int kLog = 17;
const int INF = 1e9;
int m, tour[2 * kN], dep[2 * kN], first[1 + kN], lg2[2 * kN], rmq[1 + kLog][2 * kN];
int sub[1 + kN], p[1 + kN], d[1 + kN];
vector<int> g[1 + kN];
bitset<1 + kN> vis;

void dfsLca(int u, int par, int level) {
  tour[++m] = u;
  dep[m] = level;
  first[u] = m;

  for (const int &v : g[u]) {
    if (v != par) {
      dfsLca(v, u, level + 1);

      tour[++m] = u;
      dep[m] = level;
    }
  }
}

void precompute() {
  for (int i = 2; i <= m; ++i) {
    lg2[i] = lg2[i >> 1] + 1;
  }

  for (int i = 1; i <= m; ++i) {
    rmq[0][i] = i;
  }

  for (int l = 1; l <= lg2[m]; ++l) {
    for (int i = 1; i <= m - (1 << l) + 1; ++i) {
      rmq[l][i] = rmq[l - 1][i + (1 << (l - 1))];

      if (dep[rmq[l - 1][i]] < dep[rmq[l][i]]) {
        rmq[l][i] = rmq[l - 1][i];
      }
    }
  }
}

int lcaQuery(int u, int v) {
  int l = first[u], r = first[v];

  if (r < l) {
    swap(l, r);
  }

  int k = lg2[r - l + 1];

  int index = rmq[k][r - (1 << k) + 1];

  if (dep[rmq[k][l]] < dep[index]) {
    index = rmq[k][l];
  }

  return tour[index];
}

int getDistance(int u, int v) {
  return dep[first[u]] + dep[first[v]] - 2 * dep[first[lcaQuery(u, v)]];
}

void findSize(int u, int par) {
  sub[u] = 1;

  for (const int &v : g[u]) {
    if (!vis[v] && v != par) {
      findSize(v, u);
      sub[u] += sub[v];
    }
  }
}

int findCentroid(int u, int par, int n) {
  for (const int &v : g[u]) {
    if (!vis[v] && v != par && sub[v] > n / 2) {
      return findCentroid(v, u, n);
    }
  }

  return u;
}

void buildCentroid(int u, int par) {
  findSize(u, 0);

  int c = findCentroid(u, 0, sub[u]);
  vis[c] = true;
  p[c] = par;

  for (const int &v : g[c]) {
    if (!vis[v]) {
      buildCentroid(v, c);
    }
  }
}

void minSelf(int &x, int y) {
  if (y < x) {
    x = y;
  }
}

void update(int u) {
  int v = u;

  while (v) {
    minSelf(d[v], getDistance(u, v));
    v = p[v];
  }
}

int query(int u) {
  int best = INF;
  int v = u;

  while (v) {
    minSelf(best, getDistance(u, v) + d[v]);
    v = p[v];
  }

  return best;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;

    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  dfsLca(1, 0, 0);
  precompute();

  buildCentroid(1, 0);

  for (int i = 1; i <= n; ++i) {
    d[i] = INF;
  }

  update(1);

  for (int i = 1; i <= m; ++i) {
    int t, v;
    cin >> t >> v;

    if (t == 1) {
      update(v);
    } else {
      cout << query(v) << '\n';
    }
  }

  return 0;
}
