#include <bits/stdc++.h>
 
using namespace std;
 
void fastIO() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
}
 
const int MAXN = 1e5 + 1;
const int MAXM = 2e5 + 1;
vector<int> G[MAXN], GT[MAXN], D[MAXN], DT[MAXN];
pair<int,int> edges[MAXM];
bitset<MAXN> viz, is_source, is_sink;
int vf, S[MAXN], ctc_cnt, node[MAXN], ctc_index[MAXN], sink;
bool rev;
 
void dfs1(int u) {
  viz[u] = true;
  for (int v : G[u])
    if (!viz[v])
      dfs1(v);
  S[++vf] = u;
}
 
void dfs2(int u) {
  ctc_index[u] = ctc_cnt;
  for (int v : GT[u])
    if (!ctc_index[v])
      dfs2(v);
}
 
void dfs(int u) {
  viz[u] = true;
  if (is_sink[u])
    sink = u;
  for (int v : D[u]) {
    if (sink)
      return;
    if (!viz[v])
      dfs(v);
  }
}
 
void print(int x, int y) {
  if (rev)
    cout << node[y] << ' ' << node[x] << '\n';
  else cout << node[x] << ' ' << node[y] << '\n';
}
 
void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    if (u == v)
      continue;
    G[u].emplace_back(v);
    GT[v].emplace_back(u);
    edges[i] = make_pair(u, v);
  }
  for (int u = 1; u <= N; ++u)
    if (!viz[u])
      dfs1(u);
  while (vf) {
    int u = S[vf--];
    if (!ctc_index[u]) {
      node[++ctc_cnt] = u;
      dfs2(u);
    }
  }
  if (ctc_cnt == 1) {
    cout << "0\n";
    return;
  }
  for (int i = 0; i < M; ++i) {
    int u, v;
    tie(u, v) = edges[i];
    u = ctc_index[u], v = ctc_index[v];
    edges[i] = make_pair(u, v);
    if (u != v) {
      D[u].emplace_back(v);
      DT[v].emplace_back(u);
    }
  }
  vector<int> sources, sinks, isolated;
  for (int u = 1; u <= ctc_cnt; ++u) {
    if (D[u].empty() && DT[u].empty()) {
      isolated.emplace_back(u);
      continue;
    }
    if (D[u].empty())
      sinks.emplace_back(u);
    if (DT[u].empty())
      sources.emplace_back(u);
  }
  if ((int)isolated.size() == ctc_cnt) {
    cout << ctc_cnt << '\n';
    for (int u = 1; u <= ctc_cnt; ++u) {
      int v = u + 1;
      if (v > ctc_cnt)
        v = 1;
      cout << node[u] << ' ' << node[v] << '\n';
    }
    return;
  }
  if (sinks.size() < sources.size()) {
    rev = true;
    swap(D, DT);
    swap(sources, sinks);
  }
  for (int u : sources)
    is_source[u] = true;
  for (int u : sinks)
    is_sink[u] = true;
  vector<int> v{0}, w{0};
  for (int u = 1; u <= ctc_cnt; ++u)
    viz[u] = false;
  for (int u : sources) {
    sink = 0;
    dfs(u);
    if (sink) {
      v.emplace_back(u);
      w.emplace_back(sink);
      is_source[u] = is_sink[sink] = false;
    }
  }
  int s = sources.size(), t = sinks.size(), q = isolated.size(), p = v.size() - 1;
  for (int u : sources)
    if (is_source[u])
      v.emplace_back(u);
  for (int u : sinks)
    if (is_sink[u])
      w.emplace_back(u);
  sources.insert(sources.begin(), 0);
  sinks.insert(sinks.begin(), 0);
  isolated.insert(isolated.begin(), 0);
  cout << max(s, t) + q << '\n';
  for (int i = 1; i < p; ++i)
    print(w[i], v[i + 1]);
  for (int i = p + 1; i <= s; ++i)
    print(w[i], v[i]);
  if (q == 0 && s == t) {
    print(w[p], v[1]);
  } else {
    if (s < t) {
      print(w[p], w[s + 1]);
      for (int i = s + 1; i < t; ++i)
        print(w[i], w[i + 1]);
    }
    if (q == 0 && s < t) {
      print(w[t], v[1]);
    } else {
      print(w[t], isolated[1]);
      for (int i = 1; i < q; ++i)
        print(isolated[i], isolated[i + 1]);
      print(isolated[q], v[1]);
    }
  }
}
 
int main() {
  fastIO();
  solve();
  return 0;
}
