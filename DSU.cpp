struct edge {
  int u, v, w;

  void read() {
    cin >> u >> v >> w;
  }

  bool operator < (const edge &A) const {
    return w < A.w;
  }
};

struct DSU {
  vector<int> p, r;

  DSU(int n) {
    p.resize(n + 1);
    iota(p.begin(), p.end(), 0);
    r.assign(n + 1, 1);
  }

  int get(int x) {
    if (x == p[x])
      return x;
    return p[x] = get(p[x]);
  }

  int get_size(int u) {
    return r[get(u)];
  }

  bool connected(int u, int v) {
    return get(u) == get(v);
  }

  bool unite(int u, int v) {
    int x = get(u), y = get(v);
    if (x == y)
      return false;
    if (r[x] > r[y])
      swap(x, y);
    p[x] = y;
    r[y] += r[x];
    return true;
  }
};