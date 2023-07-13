struct FenwickTree2D {
  int n;
  vector<vector<int>> vals, aib;

  void init(int N) {
    n = N;
    vals.resize(n + 1);
    aib.resize(n + 1);
  }

  void allocate(int x, int y) {
    for (int i = x; i <= n; i += i & -i) {
      vals[i].emplace_back(y);
    }
  }

  void build() {
    for (int i = 1; i <= n; ++i) {
      sort(vals[i].begin(), vals[i].end());
      vals[i].erase(unique(vals[i].begin(), vals[i].end()), vals[i].end());
      aib[i].resize(vals[i].size() + 1);
    }
  }

  void updateAib(int x, int y, int v) {
    int pos = upper_bound(vals[x].begin(), vals[x].end(), y) - vals[x].begin();
    for (int i = pos; i < (int)aib[x].size(); i += i & -i) {
      aib[x][i] += v;
    }
  }

  void update(int x, int y, int v) {
    for (int i = x; i <= n; i += i & -i) {
      updateAib(i, y, v);
    }
  }

  int queryAib(int x, int y) {
    int pos = upper_bound(vals[x].begin(), vals[x].end(), y) - vals[x].begin();
    int ans = 0;
    for (int i = pos; i > 0; i = i & (i - 1)) {
      ans += aib[x][i];
    }
    return ans;
  }

  int queryIntervalAib(int x, int l, int r) {
    if (r < l) {
      return 0;
    }
    return queryAib(x, r) - queryAib(x, l - 1);
  }

  int query(int x, int y) {
    int ans = 0;
    for (int i = x; i > 0; i = i & (i - 1)) {
      ans += queryAib(i, y);
    }
    return ans;
  }

  int queryInterval(int l, int r, int v) {
    if (r < l) {
      return 0;
    }
    return query(r, v) - query(l - 1, v);
  }
};
