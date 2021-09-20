struct DSU {
  int n, cnt;
  vector<int> p, sz;
  stack<pair<int, int>> st;

  DSU(int _n) : n(_n) {
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
    st.emplace(x, y);
    --cnt;
  }

  void rollback() {
    while (st.top().first) {
      int x, y;
      tie(x, y) = st.top();
      st.pop();
      p[x] = x;
      sz[y] -= sz[x];
      ++cnt;
    }
    st.pop();
  }

  void reset() {
    iota(p.begin(), p.end(), 0);
    sz = vector<int>(n + 1, 1);
    while (!st.empty()) {
      st.pop();
    }
    cnt = n;
  }
};
