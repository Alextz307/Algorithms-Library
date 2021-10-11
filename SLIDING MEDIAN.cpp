int median = -1;
multiset<int> low, big;
int64_t sum_low, sum_big;
 
void fix() {
  int m = (low.size() + big.size()) >> 1;
  if ((int)low.size() < m) {
    low.emplace(median);
    sum_low += median;
    median = *big.begin();
    big.erase(big.begin());
    sum_big -= median;
  }
  if ((int)low.size() > m) {
    big.emplace(median);
    sum_big += median;
    median = *--low.end();
    low.erase(--low.end());
    sum_low -= median;
  }
}
 
void add(int x) {
  if (median == -1) {
    median = x;
    return;
  }
  if (x < median) {
    low.emplace(x);
    sum_low += x;
  } else {
    big.emplace(x);
    sum_big += x;
  }
  fix();
}
 
void rem(int x) {
  if (x == median) {
    median = *big.begin();
    big.erase(big.begin());
    sum_big -= median;
  } else {
    if (x < median) {
      low.erase(low.find(x));
      sum_low -= x;
    } else {
      big.erase(big.find(x));
      sum_big -= x;
    }
  }
  fix();
}
