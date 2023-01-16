#include <bits/stdc++.h>
// Sample problem: https://oj.uz/problem/view/COCI21_index?locale=en

using namespace std;

const int N = 2e5;
const int INF = 1e9;
vector<pair<int, int>> aib[1 + N];

void build() {
  for (int i = 1; i <= N; ++i) {
    aib[i].emplace_back(0, 0);
  }
}

void update(int version, int p, int v) {
  for (int i = p; i <= N; i += i & -i) {
    aib[i].emplace_back(version, aib[i].back().second + v);
  }
}

int query(int version, int p) {
  int res = 0;

  for (int i = p; i > 0; i = i & (i - 1)) {
    auto it = upper_bound(aib[i].begin(), aib[i].end(), make_pair(version, INF)) - 1;
    res += it->second;
  }

  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  build();

  for (int i = 1; i <= n; ++i) {
    int x;
    cin >> x;

    update(i, x, 1);
  }

  for (int i = 0; i < q; ++i) {
    int l, r;
    cin >> l >> r;

    int len = r - l + 1;

    int st = 2, dr = len, res = 1;

    while (st <= dr) {
      int mid = (st + dr) / 2;

      if (len - (query(r, mid - 1) - query(l - 1, mid - 1)) >= mid) {
        res = mid;
        st = mid + 1;
      } else {
        dr = mid - 1;
      }
    }

    cout << res << '\n';
  }

  return 0;
}
