#include <bits/stdc++.h>

using namespace std;

struct qry {
  int l, r, u, v;
};

struct DSU {
  int n, cnt;
  vector<int> p, sz, stk;

  void init(int _n) {
    n = _n;
    p.resize(n + 1);
    iota(p.begin(), p.end(), 0);
    sz.resize(n + 1, 1);
    cnt = n;
  }

  int root(int x) {
    if (x == p[x]) {
      return x;
    }
    return root(p[x]);
  }

  void unite(int u, int v) {
    int x = root(u), y = root(v);
    if (x == y) {
      return;
    }
    if (sz[y] < sz[x]) {
      swap(x, y);
    }
    p[x] = y;
    sz[y] += sz[x];
    stk.emplace_back(x);
    cnt -= 1;
  }

  void rollback(int checkpoint) {
    while ((int)stk.size() > checkpoint) {
      int x = stk.back();
      stk.pop_back();
      sz[p[x]] -= sz[x];
      p[x] = x;
      cnt += 1;
    }
  }
} dsu;

int n, m, q;

bool segIntersect(int l1, int r1, int l2, int r2) {
  return max(l1, l2) <= min(r1, r2);
}

void solve(int l, int r, const vector <qry> &queries) {
  if (l > r) {
    return;
  }
  int checkpoint = dsu.stk.size();
  vector<qry> left, right;
  int mid = (l + r) / 2;
  for (const auto &it : queries) {
    if (it.l <= l && r <= it.r) {
      dsu.unite(it.u, it.v);
    } else {
      if (segIntersect(l, mid, it.l, it.r)) {
        left.emplace_back(it);
      }
      if (segIntersect(mid + 1, r, it.l, it.r)) {
        right.emplace_back(it);
      }
    }
  }
  if (l == r) {
    if (m <= l) {
      cout << dsu.cnt << ' ';
    }
    dsu.rollback(checkpoint);
    return;
  }
  solve(l, mid, left);
  solve(mid + 1, r, right);
  dsu.rollback(checkpoint);
}

void testCase() {
  cin >> n >> m >> q;
  map<pair<int, int>, int> index;
  vector<qry> queries;
  for (int t = 1; t <= m + q; ++t) {
    char op;
    if (t <= m) {
      op = '1';
    } else {
      cin >> op;
    }
    int u, v;
    cin >> u >> v;
    if (u > v) {
      swap(u, v);
    }
    if (op == '1') {
      index[make_pair(u, v)] = queries.size();
      queries.push_back({t, m + q, u, v});
    } else {
      queries[index[make_pair(u, v)]].r = t - 1;
    }
  }
  dsu.init(n);
  solve(1, m + q, queries);
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int tests = 1;
  for (int tc = 0; tc < tests; ++tc) {
    testCase();
  }
  return 0;
}
