struct ST {
  vector<line> t;

  ST(int n) {
    int dim = 1;
    while (dim < n) {
      dim <<= 1;
    }
    t.resize(dim << 1);
  }

  void addLine(int x, int lx, int rx, line l) {
    if (lx == rx) {
      if (t[x].eval(lx) < l.eval(lx)) {
        t[x] = l;
      }
      return;
    }
    int mid = (lx + rx) >> 1;
    if (l.m < t[x].m) {
      swap(t[x], l);
    }
    if (t[x].eval(mid) < l.eval(mid)) {
      swap(t[x], l);
      addLine(x << 1, lx, mid, l);
    } else {
      addLine(x << 1 | 1, mid + 1, rx, l);
    }
  }

  int query(int x, int lx, int rx, int pos) {
    int val = t[x].eval(pos);
    if (lx == rx) {
      return val;
    }
    int mid = (lx + rx) >> 1;
    if (pos <= mid) {
      return max(val, query(x << 1, lx, mid, pos));
    }
    return max(val, query(x << 1 | 1, mid + 1, rx, pos));
  }
};
