const int MAXN = 1 << 7 | 1;
int n;
int64_t aib[MAXN][MAXN][MAXN];

void update(int x, int y, int z, int val) {
  for (int i = x + 1; i <= n; i += i & -i) {
    for (int j = y + 1; j <= n; j += j & -j) {
      for (int k = z + 1; k <= n; k += k & -k) {
        aib[i][j][k] += val;
      }
    }
  }
}

int64_t query(int x, int y, int z) {
  int64_t ans = 0;
  for (int i = x + 1; i >= 1; i -= i & -i) {
    for (int j = y + 1; j >= 1; j -= j & -j) {
      for (int k = z + 1; k >= 1; k -= k & -k) {
        ans += aib[i][j][k];
      }
    }
  }
  return ans;
}

void test_case() {
  cin >> n;
  int op;
  cin >> op;
  while (op != 3) {
    if (op == 1) {
      int x, y, z, val;
      cin >> x >> y >> z >> val;
      update(x, y, z, val);
    } else {
      int x1, y1, z1, x2, y2, z2;
      cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
      int64_t s1 = query(x2, y2, z2) - query(x2, y1 - 1, z2) - query(x1 - 1, y2, z2) + query(x1 - 1, y1 - 1, z2);
      int64_t s2 = query(x2, y2, z1 - 1) - query(x2, y1 - 1, z1 - 1) - query(x1 - 1, y2, z1 - 1) + query(x1 - 1, y1 - 1, z1 - 1);
      cout << s1 - s2 << '\n';
    }
    cin >> op;
  }
}
