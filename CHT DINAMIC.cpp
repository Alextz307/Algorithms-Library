const int64_t INF = -1e18L;

struct line {
  int64_t m, b;

  mutable function<const line*()> succ;

  bool operator < (const line &rhs) const {
    if (rhs.b != INF) {
      return m < rhs.m;
    }
    const line* s = succ();
    if (!s) {
      return 0;
    }
    int64_t x = rhs.m;
    return b - s->b < (s->m - m) * x;
  }
};

struct dynamicHull : public multiset<line> {
  const int64_t inf = -INF;
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) {
        return 0;
      }
      return y->m == z->m && y->b <= z->b;
    }
    auto x = prev(y);
    if (z == end()) {
      return y->m == x->m && y->b <= x->b;
    }
    int64_t v1 = (x->b - y->b);
    if (y->m == x->m) {
      v1 = x->b > y->b ? inf : -inf;
    } else {
      v1 /= (y->m - x->m);
    }
    int64_t v2 = (y->b - z->b);
    if (z->m == y->m) {
      v2 = y->b > z->b ? inf : -inf;
    } else {
      v2 /= (z->m - y->m);
    }
    return v1 >= v2;
  }

  void insertLine(int64_t m, int64_t b) {
    auto y = insert({m, b});
    y->succ = [=] {
      return next(y) == end() ? 0 : &*next(y);
    };
    if (bad(y)) {
      erase(y);
      return;
    }
    while (next(y) != end() && bad(next(y))) {
      erase(next(y));
    }
    while (y != begin() && bad(prev(y))) {
      erase(prev(y));
    }
  }

  int64_t eval(int64_t x) {
    auto l = *lower_bound((line) {x, INF});
    return l.m * x + l.b;
  }
};
