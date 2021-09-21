#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 1;
int cnt[MAXN];

struct qry {
  int l, r, u, v;
};

struct DSU {
  int n, cnt;
  vector<int> p, sz;
  stack<int> st;

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
    if (sz[x] > sz[y]) {
      swap(x, y);
    }
    p[x] = y;
    sz[y] += sz[x];
    st.emplace(x);
    --cnt;
  }

  void rollback(int checkpoint) {
    while ((int)st.size() > checkpoint) {
      int x = st.top();
      st.pop();
      sz[p[x]] -= sz[x];
      p[x] = x;
      ++cnt;
    }
  }
} tree;

bool seg_intersect(int l1, int r1, int l2, int r2) {
  return l1 <= r2 && l2 <= r1;
}

void solve(int l, int r, const vector <qry> &queries) {
  if (l > r) {
    return;
  }
  if (cnt[l - 1] == cnt[r]) {
    return;
  }
  int checkpoint = tree.st.size();
  vector<qry> new_queries;
  for (const auto &it : queries) {
    if (it.l <= l && r <= it.r) {
      tree.unite(it.u, it.v);
    } else {
      if (seg_intersect(l, r, it.l, it.r)) {
        new_queries.emplace_back(it);
      }
    }
  }
  if (l == r) {
    if (cnt[l] - cnt[l - 1]) {
      cout << tree.cnt << '\n';
    }
    tree.rollback(checkpoint);
    return;
  }
  int mid = (l + r) >> 1;
  solve(l, mid, new_queries);
  solve(mid + 1, r, new_queries);
  tree.rollback(checkpoint);
}

void test_case() {
  int n, m;
  cin >> n >> m;
  map<pair<int, int>, int> index;
  vector<qry> queries;
  for (int t = 1; t <= m; ++t) {
    char op;
    cin >> op;
    cnt[t] = cnt[t - 1];
    if (op == '?') {
      ++cnt[t];
      continue;
    }
    int u, v;
    cin >> u >> v;
    if (u > v) {
      swap(u, v);
    }
    if (op == '+') {
      index[make_pair(u, v)] = queries.size();
      queries.push_back({t, m, u, v});
    } else {
      queries[index[make_pair(u, v)]].r = t - 1;
    }
  }
  tree.init(n);
  solve(1, m, queries);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T = 1;
  for (int tc = 1; tc <= T; ++tc) {
    test_case();
  }
  return 0;
}
