#include <bits/stdc++.h>

using namespace std;

const int kN = 4e5;
const int kSigma = 26; /// !!!
int n, idx[kSigma], order[kN], code[kN], nextCode[kN], aux[kN], inv[kN], lcp[kN], freq[1 + kN], pos[1 + kN];
string s;

void countingSort(int a[], int c[]) {
  for (int i = 0; i <= n; ++i) {
    freq[i] = 0;
  }
  for (int i = 0; i < n; ++i) {
    aux[i] = a[i];
    freq[c[i]] += 1;
  }
  pos[0] = 0;
  for (int i = 1; i <= n; ++i) {
    pos[i] = pos[i - 1] + freq[i - 1];
  }
  for (int i = 0; i < n; ++i) {
    a[pos[c[aux[i]]]++] = aux[i];
  }
}

void buildSuff() {
  for (int i = 0; i < n; ++i) {
    idx[s[i] - 'a'] = 1; /// !!!
  }
  int cnt = 0;
  for (int i = 0; i < kSigma; ++i) {
    if (idx[i]) {
      idx[i] = ++cnt;
    }
  }
  for (int i = 0; i < n; ++i) {
    order[i] = i;
    code[i] = idx[s[i] - 'a']; /// !!!
  }
  countingSort(order, code);
  int k = 1;
  while (code[order[n - 1]] < n) {
    for (int i = 0; i < n; ++i) {
      if (order[i] + k < n) {
        nextCode[order[i]] = code[order[i] + k];
      } else {
        nextCode[order[i]] = 0;
      }
    }
    countingSort(order, nextCode);
    countingSort(order, code);
    pair<int, int> last{-1, -1};
    int newCode = 0;
    for (int i = 0; i < n; ++i) {
      pair<int, int> curr{code[order[i]], nextCode[order[i]]};
      if (curr != last) {
        newCode += 1;
        last = curr;
      }
      code[order[i]] = newCode;
    }
    k *= 2;
  }
}

void buildLcp() {
  for (int i = 0; i < n; ++i) {
    inv[order[i]] = i;
  }
  int k = 0;
  for (int i = 0; i < n; ++i) {
    if (inv[i] == n - 1) {
      k = 0;
      continue;
    }
    int j = order[inv[i] + 1];
    while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
      k += 1;
    }
    lcp[inv[i]] = k;
    if (k > 0) {
      k -= 1;
    }
  }
}

void testCase() {
  cin >> s;
  n = s.size();
  buildSuff();
  buildLcp();
  
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int tests = 1;
  for (int tc = 0; tc < tests; ++tc) {
    testCase();
  }
  return 0;
}
