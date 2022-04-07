#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

const int kN = 2e5;
vector<int> g[1 + kN];
int n, m, timer, vf, N, tin[1 + kN], low[1 + kN], stk[1 + kN], ctcIndex[1 + kN];

void minSelf(int &x, int y) {
  if (y < x) {
    x = y;
  }
}

int neg(int i) {
  if (i <= n) {
    return i + n;
  }
  return i - n;
}

void addEdge(int i, int j) {
  g[i].emplace_back(j);
}

void addOr(int i, int j) {
  addEdge(neg(i), j);
  addEdge(neg(j), i);
}

int getNode(char c, int x) {
  if (c == '+') {
    return x;
  }
  return x + n;
}

void dfs(int u) {
  tin[u] = ++timer;
  low[u] = timer;
  stk[++vf] = u;
  for (int v : g[u]) {
    if (tin[v]) {
      minSelf(low[u], tin[v]);
    } else {
      dfs(v);
      minSelf(low[u], low[v]);
    }
  }
  if (tin[u] == low[u]) {
    int node;
    do {
      node = stk[vf];
      tin[node] = INF;
      ctcIndex[node] = N;
      vf -= 1;
    } while (node != u);
    N += 1;
  }
}

void testCase() {
  cin >> m >> n;
  for (int i = 0; i < m; ++i) {
    char c1, c2;
    int i1, i2;
    cin >> c1 >> i1 >> c2 >> i2;
    addOr(getNode(c1, i1), getNode(c2, i2));
  }
  for (int i = 1; i <= 2 * n; ++i) {
    if (!tin[i]) {
      dfs(i);
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (ctcIndex[i] == ctcIndex[i + n]) {
      cout << "IMPOSSIBLE\n";
      return;
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (ctcIndex[i] < ctcIndex[i + n]) {
      cout << '+';
    } else {
      cout << '-';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int tests = 1;
  for (int tc = 0; tc < tests; ++tc) {
    testCase();
  }
  return 0;
}
