#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 1;
int pw2[18], lg2[MAXN], rmq[MAXN][17];

void compute_rmq(int n) {
  pw2[0] = 1;
  for (int i = 1; i <= n; ++i) {
    if (i < 18)
      pw2[i] = pw2[i - 1] << 1;
    if (i > 1)
      lg2[i] = lg2[i >> 1] + 1;
  }
  for (int j = 1; pw2[j] <= n; ++j)
    for (int i = 1; i + pw2[j] - 1 <= n; ++i)
      rmq[i][j] = min(rmq[i][j - 1], rmq[i + pw2[j - 1]][j - 1]);
}

int query(int st, int dr) {
  int diff = dr - st + 1;
  int k = lg2[diff];
  int shift = diff - pw2[k];
  return min(rmq[st][k], rmq[st + shift][k]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> rmq[i][0];
  compute_rmq(n);
  return 0;
}
