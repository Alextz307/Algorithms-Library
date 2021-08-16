struct FenwickTree2D {
  int n;
  vector<vector<int>> vals, tree;

  FenwickTree2D(int N) {
    n = N;
    vals.resize(n + 1);
    tree.resize(n + 1);
  }

  void allocate(int x, int y) {
    while (x <= n) {
      vals[x].emplace_back(y);
      x += x & -x;
    }
  }

  void init() {
    for (int i = 1; i <= n; ++i) {
      sort(vals[i].begin(), vals[i].end());
      vals[i].erase(unique(vals[i].begin(), vals[i].end()), vals[i].end());
      tree[i].resize(vals[i].size() + 1);
    }
  }

  void update(int x, int y, int val) {
    while (x <= n) {
      int pos = lower_bound(vals[x].begin(), vals[x].end(), y) - vals[x].begin();
      for (++pos; pos < (int)tree[x].size(); pos += pos & -pos)
        tree[x][pos] += val;
      x += x & -x;
    }
  }

  int calc(int x, int val) {
    int pos = upper_bound(vals[x].begin(), vals[x].end(), val) - vals[x].begin() - 1;
    int ans = 0;
    for (++pos; pos > 0; pos = pos & (pos - 1))
      ans += tree[x][pos];
    return ans;
  }

  int query(int x, int val) {
    int ans = 0;
    while (x > 0) {
      ans += calc(x, val);
      x = x & (x - 1);
    }
    return ans;
  }

  /* int query_interval(int st, int dr, int val) {
    int ans = 0;
    while (dr > 0) {
      ans += calc(dr, val);
      dr = dr & (dr - 1);
    }
    for (--st; st > 0; st = st & (st - 1))
      ans -= calc(st, val);
    return ans;
  } */

  int query_interval(int st, int dr, int val) {
    return query(dr, val) - query(st - 1, val);
  }
};