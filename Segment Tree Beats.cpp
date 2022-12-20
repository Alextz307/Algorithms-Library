#include <bits/stdc++.h>
#define ABS(x) ((x) >= 0 ? (x) : -(x))

using namespace std;

void max_self(int64_t &x, int64_t y) {
  if (x < y)
    x = y;
}

void min_self(int64_t &x, int64_t y) {
  if (x > y)
    x = y;
}

int64_t gcd(int64_t x, int64_t y) {
  x = ABS(x), y = ABS(y);
  while (y) {
    int64_t r = x % y;
    x = y;
    y = r;
  }
  return x;
}

const int64_t INF = 1e18L;

struct node {
  int64_t max1, max2, min1, min2, sum, diff_gcd, lazy_set, lazy_add;
  int cnt_max, cnt_min;
};

struct SegTree {
  int Size;
  vector<node> tree;

  SegTree(int n) {
    Size = 1;
    while (Size < n)
      Size <<= 1;
    tree.resize(Size << 1);
  }

  node join(const node &a, const node &b) {
    node x;
    x.sum = a.sum + b.sum;
    x.lazy_add = 0;
    x.lazy_set = INF;
    if (a.max1 > b.max1) {
      x.max1 = a.max1;
      x.cnt_max = a.cnt_max;
      x.max2 = max(a.max2, b.max1);
    } else {
      if (a.max1 < b.max1) {
        x.max1 = b.max1;
        x.cnt_max = b.cnt_max;
        x.max2 = max(a.max1, b.max2);
      } else {
        x.max1 = a.max1;
        x.cnt_max = a.cnt_max + b.cnt_max;
        x.max2 = max(a.max2, b.max2);
      }
    }
    if (a.min1 < b.min1) {
      x.min1 = a.min1;
      x.cnt_min = a.cnt_min;
      x.min2 = min(a.min2, b.min1);
    } else {
      if (a.min1 > b.min1) {
        x.min1 = b.min1;
        x.cnt_min = b.cnt_min;
        x.min2 = min(a.min1, b.min2);
      } else {
        x.min1 = a.min1;
        x.cnt_min = a.cnt_min + b.cnt_min;
        x.min2 = min(a.min2, b.min2);
      }
    }
    x.diff_gcd = gcd(a.diff_gcd, b.diff_gcd);
    int64_t any = -1;
    for (int64_t any_left : {a.min2, a.max2}) {
      if (ABS(any_left) == INF || any_left == x.min1 || any_left == x.max1)
        continue;
      any = any_left;
      for (int64_t any_right : {b.min2, b.max2}) {
        if (ABS(any_right) == INF || any_right == x.min1 || any_right == x.max1)
          continue;
        x.diff_gcd = gcd(x.diff_gcd, any_left - any_right);
      }
    }
    for (int64_t any_right : {b.min2, b.max2}) {
      if (ABS(any_right) == INF || any_right == x.min1 || any_right == x.max1)
        continue;
      any = any_right;
    }
    for (int64_t val : {a.min1, a.max1, b.min1, b.max1}) {
      if (val == x.min1 || val == x.max1)
        continue;
      if (any != -1)
        x.diff_gcd = gcd(x.diff_gcd, any - val);
      else any = val;
    }
    return x;
  }

  void build(int x, int lx, int rx) {
    if (lx == rx) {
      int64_t val;
      cin >> val;
      tree[x].max1 = tree[x].min1 = tree[x].sum = val;
      tree[x].max2 = -INF;
      tree[x].min2 = INF;
      tree[x].cnt_max = tree[x].cnt_min = 1;
      tree[x].diff_gcd = tree[x].lazy_add = 0;
      tree[x].lazy_set = INF;
      return;
    }
    int mid = (lx + rx) >> 1;
    build(x << 1, lx, mid);
    build(x << 1 | 1, mid + 1, rx);
    tree[x] = join(tree[x << 1], tree[x << 1 | 1]);
  }

  void push_set(int x, int n, int64_t val) {
    tree[x].max1 = tree[x].min1 = tree[x].lazy_set = val;
    tree[x].cnt_max = tree[x].cnt_min = n;
    tree[x].max2 = -INF;
    tree[x].min2 = INF;
    tree[x].sum = val * n;
    tree[x].diff_gcd = tree[x].lazy_add = 0;
  }

  void push_min_equal(int x, int n, int64_t val) {
    if (val <= tree[x].min1)
      push_set(x, n, val);
    else if (val < tree[x].max1) {
      if (tree[x].min2 == tree[x].max1)
        tree[x].min2 = val;
      tree[x].sum -= (tree[x].max1 - val) * tree[x].cnt_max;
      tree[x].max1 = val;
    }
  }

  void push_max_equal(int x, int n, int64_t val) {
    if (tree[x].max1 <= val)
      push_set(x, n, val);
    else if (val > tree[x].min1) {
      if (tree[x].max2 == tree[x].min1)
        tree[x].max2 = val;
      tree[x].sum += (val - tree[x].min1) * tree[x].cnt_min;
      tree[x].min1 = val;
    }
  }

  void push_add(int x, int n, int64_t val) {
    tree[x].max1 += val;
    if (tree[x].max2 != -INF)
      tree[x].max2 += val;
    tree[x].min1 += val;
    if (tree[x].min2 != INF)
      tree[x].min2 += val;
    tree[x].sum += val * n;
    if (tree[x].lazy_set != INF)
      tree[x].lazy_set += val;
    else tree[x].lazy_add += val;
  }

  void push(int x, int lx, int rx) {
    if (lx == rx)
      return;
    int mid = (lx + rx) >> 1, lSon = x << 1, rSon = x << 1 | 1;
    int l1 = mid - lx + 1, l2 = rx - mid;
    if (tree[x].lazy_set != INF) {
      push_set(lSon, l1, tree[x].lazy_set);
      push_set(rSon, l2, tree[x].lazy_set);
      tree[x].lazy_set = INF;
      return;
    }
    if (tree[x].lazy_add != 0) {
      push_add(lSon, l1, tree[x].lazy_add);
      push_add(rSon, l2, tree[x].lazy_add);
      tree[x].lazy_add = 0;
    }
    push_min_equal(lSon, l1, tree[x].max1);
    push_min_equal(rSon, l2, tree[x].max1);
    push_max_equal(lSon, l1, tree[x].min1);
    push_max_equal(rSon, l2, tree[x].min1);
  }

  void update_min(int x, int lx, int rx, int st, int dr, int val) {
    if (tree[x].max1 <= val)
      return;
    if (st <= lx && rx <= dr && tree[x].max2 < val) {
      push_min_equal(x, rx - lx + 1, val);
      return;
    }
    push(x, lx, rx);
    int mid = (lx + rx) >> 1;
    if (st <= mid)
      update_min(x << 1, lx, mid, st, dr, val);
    if (mid < dr)
      update_min(x << 1 | 1, mid + 1, rx, st, dr, val);
    tree[x] = join(tree[x << 1], tree[x << 1 | 1]);
  }

  void update_max(int x, int lx, int rx, int st, int dr, int val) {
    if (val <= tree[x].min1)
      return;
    if (st <= lx && rx <= dr && val < tree[x].min2) {
      push_max_equal(x, rx - lx + 1, val);
      return;
    }
    push(x, lx, rx);
    int mid = (lx + rx) >> 1;
    if (st <= mid)
      update_max(x << 1, lx, mid, st, dr, val);
    if (mid < dr)
      update_max(x << 1 | 1, mid + 1, rx, st, dr, val);
    tree[x] = join(tree[x << 1], tree[x << 1 | 1]);
  }

  void update_set(int x, int lx, int rx, int st, int dr, int val) {
    if (st <= lx && rx <= dr) {
      push_set(x, rx - lx + 1, val);
      return;
    }
    push(x, lx, rx);
    int mid = (lx + rx) >> 1;
    if (st <= mid)
      update_set(x << 1, lx, mid, st, dr, val);
    if (mid < dr)
      update_set(x << 1 | 1, mid + 1, rx, st, dr, val);
    tree[x] = join(tree[x << 1], tree[x << 1 | 1]);
  }

  void update_add(int x, int lx, int rx, int st, int dr, int val) {
    if (st <= lx && rx <= dr) {
      push_add(x, rx - lx + 1, val);
      return;
    }
    push(x, lx, rx);
    int mid = (lx + rx) >> 1;
    if (st <= mid)
      update_add(x << 1, lx, mid, st, dr, val);
    if (mid < dr)
      update_add(x << 1 | 1, mid + 1, rx, st, dr, val);
    tree[x] = join(tree[x << 1], tree[x << 1 | 1]);
  }

  int64_t query_sum(int x, int lx, int rx, int st, int dr) {
    if (st <= lx && rx <= dr)
      return tree[x].sum;
    push(x, lx, rx);
    int mid = (lx + rx) >> 1;
    int64_t ans = 0;
    if (st <= mid)
      ans += query_sum(x << 1, lx, mid, st, dr);
    if (mid < dr)
      ans += query_sum(x << 1 | 1, mid + 1, rx, st, dr);
    return ans;
  }

  int64_t query_min(int x, int lx, int rx, int st, int dr) {
    if (st <= lx && rx <= dr)
      return tree[x].min1;
    push(x, lx, rx);
    int mid = (lx + rx) >> 1;
    int64_t ans = INF;
    if (st <= mid)
      min_self(ans, query_min(x << 1, lx, mid, st, dr));
    if (mid < dr)
      min_self(ans, query_min(x << 1 | 1, mid + 1, rx, st, dr));
    return ans;
  }

  int64_t query_max(int x, int lx, int rx, int st, int dr) {
    if (st <= lx && rx <= dr)
      return tree[x].max1;
    push(x, lx, rx);
    int mid = (lx + rx) >> 1;
    int64_t ans = 0;
    if (st <= mid)
      max_self(ans, query_max(x << 1, lx, mid, st, dr));
    if (mid < dr)
      max_self(ans, query_max(x << 1 | 1, mid + 1, rx, st, dr));
    return ans;
  }

  int64_t query_gcd(int x, int lx, int rx, int st, int dr) {
    if (st <= lx && rx <= dr) {
      int64_t ans = tree[x].diff_gcd;
      ans = gcd(ans, tree[x].max1);
      ans = gcd(ans, tree[x].min1);
      for (int64_t val : {tree[x].min2, tree[x].max2})
        if (ABS(val) != INF) {
          ans = gcd(ans, tree[x].max1 - val);
          ans = gcd(ans, tree[x].min1 - val);
          break;
        }
      return ans;
    }
    push(x, lx, rx);
    int mid = (lx + rx) >> 1;
    int64_t ans = 0;
    if (st <= mid)
      ans = gcd(ans, query_gcd(x << 1, lx, mid, st, dr));
    if (mid < dr)
      ans = gcd(ans, query_gcd(x << 1 | 1, mid + 1, rx, st, dr));
    return ans;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  SegTree tree(n);
  tree.build(1, 1, n);
  int Q;
  cin >> Q;
  for (int q = 0; q < Q; ++q) {
    int t;
    cin >> t;
    if (t < 5) {
      int l, r, x;
      cin >> l >> r >> x;
      if (t == 1)
        tree.update_min(1, 1, n, l, r, x);
      if (t == 2)
        tree.update_max(1, 1, n, l, r, x);
      if (t == 3)
        tree.update_set(1, 1, n, l, r, x);
      if (t == 4)
        tree.update_add(1, 1, n, l, r, x);
    } else {
      int l, r;
      cin >> l >> r;
      if (t == 5)
        cout << tree.query_sum(1, 1, n, l, r);
      if (t == 6)
        cout << tree.query_min(1, 1, n, l, r);
      if (t == 7)
        cout << tree.query_max(1, 1, n, l, r);
      if (t == 8)
        cout << tree.query_gcd(1, 1, n, l, r);
      cout << '\n';
    }
  }
  return 0;
}
