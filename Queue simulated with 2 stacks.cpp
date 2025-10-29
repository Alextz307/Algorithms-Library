#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Queue_t {
private:
  int resNonReady;
  stack<int> stkNonReady;
  stack<int> stkReady;

  int combineValues(int x, int y) { return x | y; }

public:
  int size() { return stkNonReady.size() + stkReady.size(); }

  void push(int x) {
    if (stkNonReady.empty()) {
      resNonReady = x;
    } else {
      resNonReady = combineValues(resNonReady, x);
    }

    stkNonReady.emplace(x);
  }

  void pop() {
    if (stkReady.empty()) {
      while (!stkNonReady.empty()) {
        int x = stkNonReady.top();
        stkNonReady.pop();

        if (stkReady.empty()) {
          stkReady.emplace(x);
        } else {
          stkReady.emplace(combineValues(stkReady.top(), x));
        }
      }
    }

    stkReady.pop();
  }

  int getValue() {
    if (stkNonReady.empty()) {
      return stkReady.top();
    }
    if (stkReady.empty()) {
      return resNonReady;
    }
    return combineValues(resNonReady, stkReady.top());
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k, x, a, b, c;
  cin >> n >> k >> x >> a >> b >> c;

  int res = 0;
  Queue_t q;

  for (int i = 1; i <= n; ++i) {
    if (i > 1) {
      x = ((int64_t)a * x + b) % c;
    }

    q.push(x);

    if (q.size() == k + 1) {
      q.pop();
    }

    if (i >= k) {
      res ^= q.getValue();
    }
  }

  cout << res << '\n';

  return 0;
}
