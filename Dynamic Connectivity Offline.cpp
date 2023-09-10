#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <stdlib.h>
#include <cassert>
#include <string.h>
#include <chrono>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <bitset>
#include <array>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <functional>
#include <numeric>
#include <complex>

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
    cout << dsu.cnt << '\n';

    dsu.rollback(checkpoint);

    return;
  }

  solve(l, mid, left);
  solve(mid + 1, r, right);

  dsu.rollback(checkpoint);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr); 

  int n, q;
  cin >> n >> q;

  vector<int> p(n + 1);
  vector<qry> queries;
  map<pair<int, int>, int> index;

  auto getEdge = [&](int i) -> pair<int, int> {
    return make_pair(min(i, p[i]), max(i, p[i]));
  };

  auto startEdge = [&](int i, int t) -> void {
    int u, v;
    tie(u, v) = getEdge(i);

    index[make_pair(u, v)] = queries.size();
    queries.push_back({t, q, u, v});
  };

  auto endEdge = [&](int i, int t) -> void {
    int u, v;
    tie(u, v) = getEdge(i);
    
    queries[index[make_pair(u, v)]].r = t - 1;
  };

  for (int i = 1; i <= n; ++i) {
    cin >> p[i];
    startEdge(i, 0);
  }
    
  for (int t = 1; t <= q; ++t) {
    int i, j;
    cin >> i >> j;

    endEdge(i, t);
    endEdge(j, t);

    swap(p[i], p[j]);

    startEdge(i, t);
    startEdge(j, t);
  }

  dsu.init(n);
  solve(0, q, queries);

  return 0;
}
