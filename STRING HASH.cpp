#include <bits/stdc++.h>

using namespace std;

const int mod[] = {(int)1e9 + 7, (int)1e9 + 9};
const int base[] = {29, 31};
const int kN = 1e6;
int p[2][1 + kN], h[2][1 + kN];

void addSelf(int &x, int y, int mod) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int add(int x, int y, int mod) {
  addSelf(x, y, mod);
  return x;
}

void multSelf(int &x, int y, int mod) {
  x = (int64_t)x * y % mod;
}

int mult(int x, int y, int mod) {
  multSelf(x, y, mod);
  return x;
}

void precalc() {
  for (int j = 0; j < 2; ++j) {
    p[j][0] = 1;
    for (int i = 1; i <= kN; ++i) {
      p[j][i] = mult(p[j][i - 1], base[j], mod[j]);
    }
  }
}

pair<int, int> getHash(int l, int r) {
  int res[2];
  for (int i = 0; i < 2; ++i) {
    res[i] = add(h[i][r], mod[i] - mult(h[i][l - 1], p[i][r - l + 1], mod[i]), mod[i]);
  }
  return {res[0], res[1]};
}

void testCase() {
  string s;
  cin >> s;
  int n = s.size();
  s = '$' + s;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < 2; ++j) {
      h[j][i] = add(mult(h[j][i - 1], base[j], mod[j]), s[i] - 'a' + 1, mod[j]);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  precalc();
  int tests = 1;
  for (int tc = 0; tc < tests; ++tc) {
    testCase();
  }
  return 0;
}
