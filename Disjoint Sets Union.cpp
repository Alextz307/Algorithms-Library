struct DSU {
  vector<int> p, sz;

  DSU(int n) {
    p.resize(n + 1);
    iota(p.begin(), p.end(), 0);
    sz.assign(n + 1, 1);
  }

  int root(int x) {
    if (x == p[x]) {
      return x;
    }
    return p[x] = root(p[x]);
  }

  bool unite(int u, int v) {
    int x = root(u), y = root(v);
    if (x == y) {
      return false;
    }
    if (sz[y] < sz[x]) {
      swap(x, y);
    }
    p[x] = y;
    sz[y] += sz[x];
    return true;
  }
};
