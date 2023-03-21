#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 1;

struct node {
  int64_t sum;
  int lazy;

  node() : sum(0), lazy(INF) {}

  node(int64_t _sum, int _lazy) : sum(_sum), lazy(_lazy) {}

  node operator + (const node &rhs) const {
    return node(sum + rhs.sum, INF);
  }
};

const node NIL = node(0, INF);

class SegTree {
  private:
    int n;
    vector<node> t;

    void updateNode(int x, int len, int v) {
      t[x].sum = (int64_t)v * len;
      t[x].lazy = v;
    }

    void push(int x, int lx, int rx) {
      if (t[x].lazy != INF) {
        int mid = (lx + rx) / 2;

        updateNode(x * 2, mid - lx + 1, t[x].lazy);
        updateNode(x * 2 + 1, rx - mid, t[x].lazy);

        t[x].lazy = INF;
      }
    }

    void update(int x, int lx, int rx, int st, int dr, int v) {
      if (st <= lx && rx <= dr) {
        updateNode(x, rx - lx + 1, v);
        return;
      }

      push(x, lx, rx);

      int mid = (lx + rx) / 2;

      if (st <= mid) {
        update(x * 2, lx, mid, st, dr, v);
      }

      if (mid < dr) {
        update(x * 2 + 1, mid + 1, rx, st, dr, v);
      }

      t[x] = t[x * 2] + t[x * 2 + 1];
    }

    node query(int x, int lx, int rx, int st, int dr) {
      if (st <= lx && rx <= dr) {
        return t[x];
      }

      push(x, lx, rx);

      int mid = (lx + rx) / 2;

      if (st <= mid && mid < dr) {
        return query(x * 2, lx, mid, st, dr) + query(x * 2 + 1, mid + 1, rx, st, dr);
      } else if (st <= mid) {
        return query(x * 2, lx, mid, st, dr);
      } else {
        return query(x * 2 + 1, mid + 1, rx, st, dr);
      }
    }

  public:
    void init(int N) {
      n = N;

      int dim = 1;

      while (dim < n) {
        dim <<= 1;
      }

      t.resize(dim << 1);
    }

    void build(int x, int lx, int rx, const vector<int> &a) {
      if (lx == rx) {
        t[x] = node(a[lx], INF);
        return;
      }

      int mid = (lx + rx) / 2;

      build(x * 2, lx, mid, a);
      build(x * 2 + 1, mid + 1, rx, a);

      t[x] = t[x * 2] + t[x * 2 + 1];
    }

    void update(int l, int r, int v) {
      if (l <= r) {
        update(1, 1, n, l, r, v);
      }
    }

    node query(int l, int r) {
      if (r < l) {
        return NIL;
      }
      return query(1, 1, n, l, r);
    }
} st;

const int kN = 2e5;
int timer, par[1 + kN], dep[1 + kN], sub[1 + kN], chainTop[1 + kN], heavySon[1 + kN], tin[1 + kN], tout[1 + kN];
vector<int> g[1 + kN];

void dfs1(int u) {
  sub[u] = 1;
  chainTop[u] = u;

  for (const int &v : g[u]) {
    if (v != par[u]) {
      par[v] = u;
      dep[v] = dep[u] + 1;

      dfs1(v);

      sub[u] += sub[v];

      if (sub[heavySon[u]] < sub[v]) {
        heavySon[u] = v;
      }
    }
  }
}

void dfs2(int u) {
  tin[u] = ++timer;

  if (heavySon[u]) {
    chainTop[heavySon[u]] = chainTop[u];
    dfs2(heavySon[u]);

    for (const int &v : g[u]) {
      if (v != par[u] && v != heavySon[u]) {
        dfs2(v);
      }
    }
  }

  tout[u] = timer;
}

void heavyUpdate(int u, int v, int x) {
  while (chainTop[u] != chainTop[v]) {
    if (dep[chainTop[u]] < dep[chainTop[v]]) {
      swap(u, v);
    }
    st.update(tin[chainTop[u]], tin[u], x);
    u = par[chainTop[u]];
  }

  int l = tin[u], r = tin[v];

  if (r < l) {
    swap(l, r);
  }

  st.update(l, r, x); /// Pentru muchii ---> st.update(l + 1, r, x)
}

node heavyQuery(int u, int v) {
  node res = NIL;

  while (chainTop[u] != chainTop[v]) {
    if (dep[chainTop[u]] < dep[chainTop[v]]) {
      swap(u, v);
    }
    res = res + st.query(tin[chainTop[u]], tin[u]);
    u = par[chainTop[u]];
  }

  int l = tin[u], r = tin[v];

  if (r < l) {
    swap(l, r);
  }

  res = res + st.query(l, r); /// Pentru muchii ---> st.query(l + 1, r)

  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> a(n + 1);

  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }

  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;

    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  dfs1(1);
  dfs2(1);

  vector<int> linearTree(n + 1);

  for (int i = 1; i <= n; ++i) {
    linearTree[tin[i]] = a[i];
  }

  st.init(n);
  st.build(1, 1, n, linearTree);

  for (int i = 0; i < m; ++i) {
    char op;
    int type, x, y, z;

    cin >> op >> type >> x;

    if (type == 3) {
      cin >> y;
    }

    if (op == 'U') {
      cin >> z;

      if (type == 1) {
        heavyUpdate(x, x, z);
      } else if (type == 2) {
        st.update(tin[x], tout[x], z);
      } else {
        heavyUpdate(x, y, z);
      }
    } else {
      if (type == 1) {
        cout << heavyQuery(x, x).sum << '\n';
      } else if (type == 2) {
        cout << st.query(tin[x], tout[x]).sum << '\n';
      } else {
        cout << heavyQuery(x, y).sum << '\n';
      }
    }
  }

  return 0;
}
