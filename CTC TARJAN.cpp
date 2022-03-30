#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
 
using namespace std;
 
ifstream fin("ctc.in");
ofstream fout("ctc.out");
 
const int kN = 1e5;
vector<int> g[1 + kN], C[1 + kN];
int timer, vf, N, tin[1 + kN], low[1 + kN], stk[1 + kN];
 
void minSelf(int &x, int y) {
  if (y < x) {
    x = y;
  }
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
    while (stk[vf] != u) {
      int node = stk[vf];
      tin[node] = INF;
      C[N].emplace_back(node);
      vf -= 1;
    }
    tin[u] = INF;
    C[N].emplace_back(u);
    vf -= 1;
    N += 1;
  }
}
 
void testCase() {
  int n, m;
  fin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v;
    fin >> u >> v;
    g[u].emplace_back(v);
  }
  for (int i = 1; i <= n; ++i) {
    if (!tin[i]) {
      dfs(i);
    }
  }
  fout << N << '\n';
  for (int i = 0; i < N; ++i) {
    for (int x : C[i]) {
      fout << x << ' ';
    }
    fout << '\n';
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
