#include <bits/stdc++.h>
/// #define int long long
#define INF 0x3f3f3f3f

using namespace std;

/* ifstream fin(".in");
ofstream fout(".out"); */

/*
- TIPURI DE DATE!!!

- DE SCHIMBAT:
  * node -> operator
  * update_node */

/// const int INF = 1e16L;
const int NO_OPERATION = INF;

void min_self(int &x, int y) {
  if (x > y)
    x = y;
}

void max_self(int &x, int y) {
  if (x < y)
    x = y;
}

struct node {
  int val, lazy_sum, lazy_set;

  friend node operator + (const node &A, const node &B) {
    node ans;
    ans.val = A.val + B.val;
    /// ans.val = min(A.val, B.val); - MIN
    /// ans.val = max(A.val, B.val); - MAX
    ans.lazy_sum = 0;
    ans.lazy_set = NO_OPERATION;
    return ans;
  }
};

const node empty_node = {0, 0, NO_OPERATION};

struct SegTree {
  int Size;
  vector<node> tree;

  SegTree(int n) {
    Size = 1;
    while (Size < n)
      Size <<= 1;
    tree.resize(Size << 1, empty_node);
  }

  void build(int x, int lx, int rx) {
    if (lx == rx) {
      int val;
      cin >> val;
      tree[x].val = val;
      tree[x].lazy_sum = 0;
      tree[x].lazy_set = NO_OPERATION;
      return;
    }
    int mid = (lx + rx) >> 1, lSon = x << 1, rSon = x << 1 | 1;
    build(lSon, lx, mid);
    build(rSon, mid + 1, rx);
    tree[x] = tree[lSon] + tree[rSon];
  }

  void update_node_set(int x, int lx, int rx, int val) {
    tree[x].lazy_sum = 0;
    tree[x].val = (rx - lx + 1) * val;
    /// tree[x].val = val; - MIN / MAX
    tree[x].lazy_set = val;
  }

  void update_node_add(int x, int lx, int rx, int val) {
    tree[x].val += (rx - lx + 1) * val;
    /// tree[x].val += val; - MIN / MAX
    tree[x].lazy_sum += val;
  }

  void push_set(int x, int lx, int rx) {
    int val = tree[x].lazy_set;
    if (val == INF)
      return;
    int mid = (lx + rx) >> 1, lSon = x << 1, rSon = x << 1 | 1;
    update_node_set(lSon, lx, mid, val);
    update_node_set(rSon, mid + 1, rx, val);
    tree[x].lazy_set = NO_OPERATION;
  }

  void push_add(int x, int lx, int rx) {
    int val = tree[x].lazy_sum;
    if (val == 0)
      return;
    int mid = (lx + rx) >> 1, lSon = x << 1, rSon = x << 1 | 1;
    update_node_add(lSon, lx, mid, val);
    update_node_add(rSon, mid + 1, rx, val);
    tree[x].lazy_sum = 0;
  }

  void set_pos(int x, int lx, int rx, int pos, int val) {
    if (lx == rx) {
      tree[x].val = val;
      return;
    }
    push_set(x, lx, rx);
    push_add(x, lx, rx);
    int mid = (lx + rx) >> 1, lSon = x << 1, rSon = x << 1 | 1;
    if (pos <= mid)
      set_pos(lSon, lx, mid, pos, val);
    else set_pos(rSon, mid + 1, rx, pos, val);
    tree[x] = tree[lSon] + tree[rSon];
  }

  void add_pos(int x, int lx, int rx, int pos, int val) {
    if (lx == rx) {
      tree[x].val += val;
      return;
    }
    push_set(x, lx, rx);
    push_add(x, lx, rx);
    int mid = (lx + rx) >> 1, lSon = x << 1, rSon = x << 1 | 1;
    if (pos <= mid)
      add_pos(lSon, lx, mid, pos, val);
    else add_pos(rSon, mid + 1, rx, pos, val);
    tree[x] = tree[lSon] + tree[rSon];
  }

  void set_interval(int x, int lx, int rx, int st, int dr, int val) {
    if (st <= lx && rx <= dr) {
      update_node_set(x, lx, rx, val);
      return;
    }
    push_set(x, lx, rx);
    push_add(x, lx, rx);
    int mid = (lx + rx) >> 1, lSon = x << 1, rSon = x << 1 | 1;
    if (st <= mid)
      set_interval(lSon, lx, mid, st, dr, val);
    if (mid < dr)
      set_interval(rSon, mid + 1, rx, st, dr, val);
    tree[x] = tree[lSon] + tree[rSon];
  }

  void add_interval(int x, int lx, int rx, int st, int dr, int val) {
    if (st <= lx && rx <= dr) {
      update_node_add(x, lx, rx, val);
      return;
    }
    push_set(x, lx, rx);
    push_add(x, lx, rx);
    int mid = (lx + rx) >> 1, lSon = x << 1, rSon = x << 1 | 1;
    if (st <= mid)
      add_interval(lSon, lx, mid, st, dr, val);
    if (mid < dr)
      add_interval(rSon, mid + 1, rx, st, dr, val);
    tree[x] = tree[lSon] + tree[rSon];
  }

  int query_sum(int x, int lx, int rx, int st, int dr) {
    if (st <= lx && rx <= dr)
      return tree[x].val;
    push_set(x, lx, rx);
    push_add(x, lx, rx);
    int mid = (lx + rx) >> 1, ans = 0;
    if (st <= mid)
      ans += query_sum(x << 1, lx, mid, st, dr);
    if (mid < dr)
      ans += query_sum(x << 1 | 1, mid + 1, rx, st, dr);
    return ans;
  }

  int query_min(int x, int lx, int rx, int st, int dr) {
    if (st <= lx && rx <= dr)
      return tree[x].val;
    push_set(x, lx, rx);
    push_add(x, lx, rx);
    int mid = (lx + rx) >> 1, ans = INF;
    if (st <= mid)
      min_self(ans, query_min(x << 1, lx, mid, st, dr));
    if (mid < dr)
      min_self(ans, query_min(x << 1 | 1, mid + 1, rx, st, dr));
    return ans;
  }

  int query_max(int x, int lx, int rx, int st, int dr) {
    if (st <= lx && rx <= dr)
      return tree[x].val;
    push_set(x, lx, rx);
    push_add(x, lx, rx);
    int mid = (lx + rx) >> 1, ans = -INF;
    if (st <= mid)
      max_self(ans, query_max(x << 1, lx, mid, st, dr));
    if (mid < dr)
      max_self(ans, query_max(x << 1 | 1, mid + 1, rx, st, dr));
    return ans;
  }

  node query(int x, int lx, int rx, int st, int dr) {
    if (st <= lx && rx <= dr)
      return tree[x];
    int mid = (lx + rx) >> 1;
    node ans1 = empty_node, ans2 = empty_node;
    if (st <= mid)
      ans1 = query(x << 1, lx, mid, st, dr);
    if (mid < dr)
      ans2 = query(x << 1 | 1, mid + 1, rx, st, dr);
    return ans1 + ans2;
  }
};

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  /* fin.sync_with_stdio(false);
  fout.sync_with_stdio(false);
  fin.tie(nullptr);
  fout.tie(nullptr);
  int n;
  cin >> n;
  SegTree tree(n);
  tree.build(1, 1, n); */
  return 0;
}
