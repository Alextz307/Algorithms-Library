#include <bits/stdc++.h>

using namespace std;

ifstream fin("componentebiconexe.in");
ofstream fout("componentebiconexe.out");

const int kN = 1e5;
vector<int> g[1 + kN];
int timer, tin[1 + kN], low[1 + kN];
vector<pair<int, int>> bridges;
bitset<1 + kN> isAp;
stack<pair<int, int>> st;
vector<vector<int>> bc;

void minSelf(int &x, const int &y) {
  if (y < x) {
    x = y;
  }
}

void dfs(int u, int par) {
  g[u].erase(find(g[u].begin(), g[u].end(), par));
  tin[u] = low[u] = ++timer;
  int children = 0;
  for (int v : g[u]) {
    if (tin[v]) {
      minSelf(low[u], tin[v]);
    } else {
      ++children;
      st.emplace(u, v);
      dfs(v, u);
      minSelf(low[u], low[v]);
      if (tin[u] <= low[v]) {
        if (tin[u] < low[v]) {
          bridges.emplace_back(u, v);
        }
        if (par) {
          isAp[u] = true;
        }
        bc.push_back({});
        int p, q;
        do {
          tie(p, q) = st.top();
          st.pop();
          bc.back().emplace_back(p);
          bc.back().emplace_back(q);
        } while (p != u || q != v);
      }
    }
  }
  if (!par && children > 1) {
    isAp[u] = true;
  }
}

void TestCase() {
  int task, n, m;
  fin >> task >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int u, v;
    fin >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  for (int v = 1; v <= n; ++v) {
    if (!tin[v]) {
      g[v].emplace_back(0);
      dfs(v, 0);
    }
  }
  if (task == 1) {
    fout << bc.size() << '\n';
    for (auto it : bc) {
      sort(it.begin(), it.end());
      it.erase(unique(it.begin(), it.end()), it.end());
      fout << it.size() << ' ';
      for (int v : it) {
        fout << v << ' ';
      }
      fout << '\n';
    }
  } else if (task == 2) {
    fout << isAp.count() << '\n';
    for (int v = 1; v <= n; ++v) {
      if (isAp[v]) {
        fout << v << ' ';
      }
    }
    fout << '\n';
  } else {
    fout << bridges.size() << '\n';
    for (auto it : bridges) {
      fout << it.first << ' ' << it.second << '\n';
    }
  }
}

int main() {
  int tests = 1;
  for (int tc = 1; tc <= tests; ++tc) {
    TestCase();
  }
  fin.close();
  fout.close();
  return 0;
}
