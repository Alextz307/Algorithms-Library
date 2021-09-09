void add_self(int64_t &x, const int64_t &y) {
  x += y;
  if (x >= mod)
    x -= mod;
}

void sub_self(int64_t &x, const int64_t &y) {
  x -= y;
  if (x < 0)
    x += mod;
}

int64_t mul(int64_t x, int64_t y) {
  int64_t ans = 0;
  while (y) {
    if (y & 1)
      add_self(ans, x);
    add_self(x, x);
    y >>= 1;
  }
  return ans;
}

int64_t lg_put(int64_t x, int64_t y) {
  int64_t ans = 1;
  while (y) {
    if (y & 1)
      ans = ans * x % mod;
    x = x * x % mod;
    y >>= 1;
  }
  return ans;
}

int64_t invers(const int64_t &x) {
  return lg_put(x, mod - 2);
}
