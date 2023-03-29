#include <bits/stdc++.h>

using namespace std;

ifstream fin("cuplaj.in");
ofstream fout("cuplaj.out");

const int kN = 1e4;
vector<int> g[1 + kN];
int l[1 + kN], r[1 + kN];
bitset<1 + kN> vis;

bool dfs(int u) {
  if (vis[u]) {
    return false;
  }

  vis[u] = true;

  for (const int &v : g[u]) {
    if (!r[v]) {
      l[u] = v;
      r[v] = u;
      return true;
    }
  }

  for (const int &v : g[u]) {
    if (dfs(r[v])) {
      l[u] = v;
      r[v] = u;
      return true;
    }
  }

  return false;
}

void testCase() {
  int n, m, E;
  fin >> n >> m >> E;

  for (int i = 0; i < E; ++i) {
    int u, v;
    fin >> u >> v;

    g[u].emplace_back(v);
  }

  bool flag;

  do {
    flag = false;
    vis.reset();

    for (int i = 1; i <= n; ++i) {
      if (!l[i]) {
        flag |= dfs(i);
      }
    }
  } while (flag);

  int ans = 0;

  for (int i = 1; i <= n; ++i) {
    if (l[i]) {
      ans += 1;
    }
  }

  fout << ans << '\n';

  for (int i = 1; i <= n; ++i) {
    if (l[i]) {
      fout << i << ' ' << l[i] << '\n';
    }
  }
}

int main() {
  int tests = 1;

  for (int tc = 0; tc < tests; ++tc) {
    testCase();
  }

  fin.close();
  fout.close();

  return 0;
}
