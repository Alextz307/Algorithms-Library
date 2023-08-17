#include <bits/stdc++.h>
 
using namespace std;
 
void fastIO() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
}
 
typedef vector<int>::iterator itr;
 
struct wavelet {
  wavelet *l, *r;
  vector<int> f;
  int lo, hi;
 
  void build(itr st, itr dr, int x, int y) {
    lo = x, hi = y;
    if (x == y)
      return;
    f.reserve(dr - st + 1);
    int mid = (x + y) >> 1;
    auto check = [&](int v) {
      return v <= mid;
    };
    f.push_back(0);
    for (itr it = st; it != dr; ++it)
      f.push_back(f.back() + check(*it));
    itr pivot = stable_partition(st, dr, check);
    if (st < pivot) {
      l = new wavelet;
      l->build(st, pivot, x, mid);
    }
    if (pivot < dr) {
      r = new wavelet;
      r->build(pivot, dr, mid + 1, y);
    }
  }
 
  int kth(int st, int dr, int k) {
    if (lo == hi)
      return lo;
    int lb = f[st - 1], rb = f[dr];
    int in_left = rb - lb;
    if (k <= in_left)
      return l->kth(lb + 1, rb, k);
    return r->kth(st - lb, dr - rb, k - in_left);
  }
};
 
void solve() {
  int N, Q;
  cin >> N >> Q;
  vector<int> a(N + 1);
  for (int i = 1; i <= N; ++i)
    cin >> a[i];
  wavelet wt;
  wt.build(a.begin() + 1, a.end(), *min_element(a.begin() + 1, a.end()), *max_element(a.begin() + 1, a.end()));
  for (int i = 0; i < Q; ++i) {
    int l, r, k;
    cin >> l >> r >> k;
    ++l, ++k;
    cout << wt.kth(l, r, k) << '\n';
  }
}
 
int main() {
  fastIO();
  solve();
  return 0;
}
 
