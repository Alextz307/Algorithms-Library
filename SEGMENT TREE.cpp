const int NIL = 0; /// !!!

struct node {
  int val, lazy;

  friend node operator + (const node &A, const node &B) { /// !!!
    node ans;
    ans.val = A.val + B.val;
    ans.lazy = NIL;
    return ans;
  }
};

const node empty_node = {0, NIL}; /// !!!

struct SegTree {
  int n;
  vector<node> t;

  void init(int N) {
    n = N;
    int Size = 1;
    while (Size < n) {
      Size <<= 1;
    }
    t.resize(Size << 1, empty_node);
  }

  void update_node(int x, int len) { /// !!!
    t[x].val = len - t[x].val;
    t[x].lazy ^= 1;
  }

  void push(int x, int lx, int rx) {
    if (t[x].lazy == NIL) {
      return;
    }
    int mid = (lx + rx) >> 1;
    int len[] = {mid - lx + 1, rx - mid};
    for (int i = 0; i <= 1; ++i) {
      update_node(x << 1 | i, len[i]);
    }
    t[x].lazy = NIL;
  }

  void update_pos(int x, int lx, int rx, int pos) {
    if (lx == rx) {
      update_node(x, rx - lx + 1);
      return;
    }
    push(x, lx, rx);
    int mid = (lx + rx) >> 1, lSon = x << 1, rSon = x << 1 | 1;
    if (pos <= mid) {
      update_pos(lSon, lx, mid, pos);
    } else {
      update_pos(rSon, mid + 1, rx, pos);
    }
    t[x] = t[lSon] + t[rSon];
  }

  void update_pos(int pos) {
    update_pos(1, 1, n, pos);
  }

  void update_interval(int x, int lx, int rx, int st, int dr) {
    if (st <= lx && rx <= dr) {
      update_node(x, rx - lx + 1);
      return;
    }
    push(x, lx, rx);
    int mid = (lx + rx) >> 1, lSon = x << 1, rSon = x << 1 | 1;
    if (st <= mid) {
      update_interval(lSon, lx, mid, st, dr);
    }
    if (mid + 1 <= dr) {
      update_interval(rSon, mid + 1, rx, st, dr);
    }
    t[x] = t[lSon] + t[rSon];
  }

  void update_interval(int st, int dr) {
    update_interval(1, 1, n, st, dr);
  }

  node query(int x, int lx, int rx, int st, int dr) {
    if (st <= lx && rx <= dr) {
      return t[x];
    }
    push(x, lx, rx);
    int mid = (lx + rx) >> 1;
    node ans1 = empty_node, ans2 = empty_node;
    if (st <= mid) {
      ans1 = query(x << 1, lx, mid, st, dr);
    }
    if (mid + 1 <= dr) {
      ans2 = query(x << 1 | 1, mid + 1, rx, st, dr);
    }
    return ans1 + ans2;
  }

  node query(int st, int dr) {
    return query(1, 1, n, st, dr);
  }
};
