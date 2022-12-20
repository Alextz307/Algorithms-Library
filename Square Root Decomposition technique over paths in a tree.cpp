#include <bits/stdc++.h>

using namespace std;

const int MAXN = 4e4 + 1;
const int MAXM = 8e4 + 1;
const int MAXQ = 1e5 + 1;
int n, Q, block, a[MAXN];
vector<int> g[MAXN];
int timer, m, tin[MAXN], tout[MAXN], node[MAXM], tour[MAXM], depth[MAXM], first[MAXN], lg2[MAXM], rmq[17][MAXM];
int ans, freq[MAXN], sol[MAXQ];
bool vis[MAXN];

struct query {
  int l, r, lca, index;

  bool operator < (const query &A) const {
    if (l / block != A.l / block) {
      return l < A.l;
    }
    return ((l / block) & 1) ? (r < A.r) : (r > A.r);
  };
} q[MAXQ];

void dfs(int u, int par, int level) {
  tin[u] = ++timer;
  node[timer] = u;
  tour[++m] = u;
  depth[m] = level;
  first[u] = m;
  for (int v : g[u]) {
    if (v != par) {
      dfs(v, u, level + 1);
      tour[++m] = u;
      depth[m] = level;
    }
  }
  tout[u] = ++timer;
  node[timer] = u;
}

void compute_rmq() {
  for (int i = 2; i <= m; ++i) {
    lg2[i] = lg2[i >> 1] + 1;
  }
  for (int i = 1; i <= m; ++i) {
    rmq[0][i] = i;
  }
  for (int i = 1; (1 << i) < m; ++i) {
    for (int j = 1; j <= m - (1 << i); ++j) {
      int l = 1 << (i - 1);
      rmq[i][j] = rmq[i - 1][j];
      if (depth[rmq[i - 1][j + l]] < depth[rmq[i][j]]) {
        rmq[i][j] = rmq[i - 1][j + l];
      }
    }
  }
}

int find_lca(int u, int v) {
  int x = first[u], y = first[v];
  if (x > y) {
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

void update(int v) {
  vis[v] ^= true;
  if (vis[v] == true) {
    if (++freq[a[v]] == 1) {
      ++ans;
    }
  } else {
    if (--freq[a[v]] == 0) {
      --ans;
    }
  }
}

void test_case() {
  cin >> n >> Q;
  vector<int> vals(n);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    vals[i - 1] = a[i];
  }
  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());
  for (int i = 1; i <= n; ++i) {
    a[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
  }
  for (int i = 1; i <= n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  dfs(1, 0, 0);
  compute_rmq();
  for (int i = 1; i <= Q; ++i) {
    int u, v;
    cin >> u >> v;
    if (tin[v] < tin[u]) {
      swap(u, v);
    }
    q[i].lca = find_lca(u, v);
    if (q[i].lca == u) {
      q[i].l = tin[u];
      q[i].r = tin[v];
    } else {
      q[i].l = tout[u];
      q[i].r = tin[v];
    }
    q[i].index = i;
  }
  block = sqrt(timer) + 1;
  sort(q + 1, q + Q + 1);
  int l = q[1].l, r = q[1].l - 1;
  for (int i = 1; i <= Q; ++i) {
    while (l > q[i].l) {
      --l;
      update(node[l]);
    }
    while (r < q[i].r) {
      ++r;
      update(node[r]);
    }
    while (l < q[i].l) {
      update(node[l]);
      ++l;
    }
    while (r > q[i].r) {
      update(node[r]);
      --r;
    }
    if (q[i].lca != node[q[i].l]) {
      update(q[i].lca);
      sol[q[i].index] = ans;
      update(q[i].lca);
    } else {
      sol[q[i].index] = ans;
    }
  }
  for (int i = 1; i <= Q; ++i) {
    cout << sol[i] << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  for (int tc = 1; tc <= t; ++tc) {
    test_case();
  }
  return 0;
}
