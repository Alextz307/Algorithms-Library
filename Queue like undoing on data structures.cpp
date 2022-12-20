// Sample problem: https://codeforces.com/contest/1386/problem/C
#include <bits/stdc++.h>

using namespace std;

struct DSU { // bipartitness using 2SAT(an edge implies color[u] != color[v])
  vector<int> p, sz;
  vector<int> stk, ptr;

  void init(int n) {
    p.resize(2 * n);
    iota(p.begin(), p.end(), 0);
    sz.resize(2 * n, 1);
  }

  int root(int v) {
    while (v != p[v]) {
      v = p[v];
    }
    return v;
  }

  void unite(int u, int v) {
    int x = root(u), y = root(v);
    if (x == y) {
      return;
    }
    if (sz[y] < sz[x]) {
      swap(x, y);
    }
    stk.emplace_back(x);
    p[x] = y;
    sz[y] += sz[x];
  }

  void addEdge(int u, int v) {
    ptr.emplace_back(stk.size());
    unite(2 * u, 2 * v + 1);
    unite(2 * u + 1, 2 * v);
  }

  bool checkEdge(int u, int v) {
    if (root(2 * u) == root(2 * v)) {
      return false;
    }
    return true;
  }

  void undo() { // undo the last operation which is an addition of 2 edges!
    int n = ptr.back();
    ptr.pop_back();
    while ((int)stk.size() > n) {
      int x = stk.back();
      stk.pop_back();
      sz[p[x]] -= sz[x];
      p[x] = x;
    }
  }
} dsu;

struct update_t {
  int type, u, v; // 0 means not yet reversed(blue) and 1 means reversed and ready to be popped(red)
};

struct queue_t {
  int ready = 0; // counter of red updates
  vector<update_t> stk; // simulate queue using only this stack
  vector<update_t> tmp[2]; // for swap

  // The sequence of push and pop updates is supposed to be a correct one and not have any flaws(like popping an empty queue)

  void pushBack(int u, int v) {
    dsu.addEdge(u, v);
    stk.push_back({0, u, v});
  }

  void popFront() {
    if (ready == 0) { // all the updates are a whole blue block, which needs to be reversed in order to pop the right one
      for (size_t rep = 0; rep < stk.size(); ++rep) {
        dsu.undo();
      }
      reverse(stk.begin(), stk.end());
      for (auto &update : stk) {
        update.type = 1; // this update is now reversed
        dsu.addEdge(update.u, update.v);
      }
      ready = stk.size();
    }
    tmp[0].clear();
    tmp[1].clear();
    while (stk.back().type == 0) { // not ready to be popped, so swap the blue block with previous red block
      tmp[0].push_back(stk.back());
      dsu.undo();
      stk.pop_back();
    }
    int redBlock = (ready & (-ready)); // length of last red block, which is the smallest, as they come in decreasing order
    for (int rep = 0; rep < redBlock; ++rep) {
      tmp[1].push_back(stk.back());
      dsu.undo();
      stk.pop_back();
    }
    for (int t : {0, 1}) { // swap the red and blue blocks
      while (!tmp[t].empty()) {
        auto update = tmp[t].back();
        tmp[t].pop_back();
        dsu.addEdge(update.u, update.v);
        stk.push_back(update);
      }
    }
    // now the last update is for sure red and it can be popped
    dsu.undo();
    stk.pop_back();
    ready -= 1;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, q;
  cin >> n >> m >> q;
  vector<pair<int, int>> edges(m);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    u -= 1, v -= 1;
    edges[i] = make_pair(u, v);
  }
  dsu.init(2 * n);
  queue_t Q;
  int l = 0;
  vector<int> left(2 * m);
  for (int r = 0; r < 2 * m; ++r) {
    int u, v;
    tie(u, v) = edges[r % m];
    while (!dsu.checkEdge(u, v)) {
      Q.popFront();
      l += 1;
    }
    left[r] = l;
    Q.pushBack(u, v);
  }
  for (int i = 0; i < q; ++i) {
    int l, r;
    cin >> l >> r;
    l -= 1, r -= 1;
    if (left[l + m - 1] <= r + 1) {
      cout << "NO\n";
    } else {
      cout << "YES\n";
    }
  }
  return 0;
}
