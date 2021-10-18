const int MAXN = 1e5;
int n, aib[1 + MAXN];

void update(int x, int t) {
  for (int i = x; i <= n; i += i & -i) {
    aib[i] += t;
  }
}

int query(int x) {
  int ans = 0;
  for (int i = x; i >= 1; i -= i & -i) {
    ans += aib[i];
  }
  return ans;
}

int query_interval(int l, int r) {
  return query(r) - query(l - 1);
}
