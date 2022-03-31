#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

ifstream fin("maxflow.in");
ofstream fout("maxflow.out");

const int kN = 1e3;
int n, m, s, t, q[1 + kN], par[1 + kN], C[1 + kN][1 + kN];
vector<int> g[1 + kN];

void minSelf(int &x, int y) {
  if (y < x) {
    x = y;
  }
}

bool bfs() {
  for (int i = 1; i <= n; ++i) {
    par[i] = 0;
  }
  int l = 0, r = -1;
  par[s] = -1;
  q[++r] = s;
  while (l <= r) {
    int u = q[l++];
    for (int v : g[u]) {
      if (par[v] == 0 && C[u][v]) {
        par[v] = u;
        if (v != t) {
          q[++r] = v;
        }
      }
    }
  }
  par[s] = 0;
  return par[t] != 0;
}

int maxFlow() {
  int flow = 0;
  while (bfs()) {
    for (int u : g[t]) {
      if (par[u] != 0) {
        par[t] = u;
        int minFlow = INF;
        for (int v = t; v != s; v = par[v]) {
          minSelf(minFlow, C[par[v]][v]);
          if (minFlow == 0) {
            break;
          }
        }
        if (minFlow == 0) {
          continue;
        }
        flow += minFlow;
        for (int v = t; v != s; v = par[v]) {
          C[par[v]][v] -= minFlow;
          C[v][par[v]] += minFlow;
        }
      }
    }
  }
  return flow;
}

void testCase() {
  fin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    fin >> u >> v >> w;
    C[u][v] += w;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  s = 1, t = n;
  fout << maxFlow() << '\n';
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
