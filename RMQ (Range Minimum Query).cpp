struct RMQ {
  int n;
  vector<int> lg2;
  vector<vector<int>> rmq;

  RMQ(const vector<int> &a) {
    n = a.size() - 1;
    lg2.resize(n + 1);
    for (int i = 2; i <= n; ++i) {
      lg2[i] = lg2[i / 2] + 1;
    }
    rmq.resize(n + 1, vector<int>(lg2[n] + 1));
    for (int i = 1; i <= n; ++i) {
      rmq[i][0] = a[i];
    }
    for (int l = 1; l <= lg2[n]; ++l) {
      for (int i = 1; i <= n - (1 << l) + 1; ++i) {
        rmq[i][l] = min(rmq[i][l - 1], rmq[i + (1 << (l - 1))][l - 1]);
      }
    }
  }

  int query(int l, int r) {
    int k = lg2[r - l + 1];
    return min(rmq[l][k], rmq[r - (1 << k) + 1][k]);
  }
};
