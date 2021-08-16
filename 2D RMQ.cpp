#include <bits/stdc++.h>

using namespace std;

const int MAXN = 212;
const int LGMAX = 8;
int n, lg2[MAXN], rmq[LGMAX][LGMAX][MAXN][MAXN];

int query(int x1, int y1, int x2, int y2) {
  int h1 = lg2[x2 - x1], h2 = lg2[y2 - y1];
  return min({rmq[h1][h2][x1][y1], rmq[h1][h2][x2 - (1 << h1) + 1][y1],
              rmq[h1][h2][x1][y2 - (1 << h2) + 1], rmq[h1][h2][x2 - (1 << h1) + 1][y2 - (1 << h2) + 1]});
}

void test_case() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
        cin >> rmq[0][0][i][j];
  for (int i = 2; i < MAXN; ++i)
    lg2[i] = lg2[i >> 1] + 1;
  for (int h1 = 0; h1 < LGMAX; ++h1)
    for (int h2 = 0; h2 < LGMAX; ++h2)
      if (h1 > 0 || h2 > 0)
        for (int i = 1; i <= n; ++i)
          for (int j = 1; j <= n; ++j)
            if (i + (1 << h1) - 1 <= n && j + (1 << h2) - 1 <= n)
              rmq[h1][h2][i][j] = query(i, j, i + (1 << h1) - 1, j + (1 << h2) - 1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  for (int tc = 0; tc < T; ++tc)
    test_case();
  return 0;
}
