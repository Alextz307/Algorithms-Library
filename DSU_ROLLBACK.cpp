struct DSU {
  int cnt;
  vector<int> p, sz;
  stack<int> st;

  void init(int n) {
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
};
