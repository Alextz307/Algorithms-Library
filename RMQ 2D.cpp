#include <bits/stdc++.h>

using namespace std;

ifstream fin("euclid.in");
ofstream fout("euclid.out");

const int kN = 400;
const int kLog = 8;
int lg2[1 + kN], rmq[1 + kLog][1 + kLog][1 + kN][1 + kN];

void maxSelf(int &x, int y) {
  if (x < y) {
    x = y;
  }
}

void precalc() {
  for (int i = 2; i <= kN; ++i) {
    lg2[i] = lg2[i / 2] + 1;
  }
}

int query(int x1, int y1, int x2, int y2) {
  int h1 = lg2[x2 - x1], h2 = lg2[y2 - y1];
  return __gcd(__gcd(rmq[h1][h2][x1][y1], rmq[h1][h2][x2 - (1 << h1) + 1][y1]), __gcd(rmq[h1][h2][x1][y2 - (1 << h2) + 1], rmq[h1][h2][x2 - (1 << h1) + 1][y2 - (1 << h2) + 1]));
}

void testCase(int tc) {
  int n, m, h, w;
  fin >> n >> m >> h >> w;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      fin >> rmq[0][0][i][j];
    }
  }
  for (int h1 = 0; h1 <= kLog; ++h1) {
    for (int h2 = 0; h2 <= kLog; ++h2) {
      if (h1 > 0 || h2 > 0) {
        for (int i = 1; i <= n - (1 << h1) + 1; ++i) {
          for (int j = 1; j <= m - (1 << h2) + 1; ++j) {
            rmq[h1][h2][i][j] = query(i, j, i + (1 << h1) - 1, j + (1 << h2) - 1);
          }
        }
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= n - h + 1; ++i) {
    for (int j = 1; j <= m - w + 1; ++j) {
      maxSelf(ans, query(i, j, i + h - 1, j + w - 1));
    }
  }
  fout << "Case #" << tc << ": " << ans << '\n';
}

int main() {
  precalc();
  int tests;
  fin >> tests;
  for (int tc = 1; tc <= tests; ++tc) {
    testCase(tc);
  }
  fin.close();
  fout.close();
  return 0;
}
