#include <bits/stdc++.h>

using namespace std;

ifstream fin("unicat.in");
ofstream fout("unicat.out");

const int kN = 5e5 + 5;

struct node {
  int nxt[26];
  int len, failLink;
  char mask;

  node() {
    for (int c = 0; c < 26; ++c) {
      nxt[c] = 0;
    }
    len = 0;
    failLink = 0;
    mask = 0;
  }
} NIL, ptr[kN];

struct PalindromicTree {
  int cnt, last;

  PalindromicTree() {
    cnt = 2;
    ptr[1] = NIL;
    ptr[2] = NIL;
    ptr[1].len = -1;
    ptr[1].failLink = 1;
    ptr[2].failLink = 1;
    last = 1;
  }

  void extend(const string &s, int pos, int bit) {
    while (s[pos - ptr[last].len - 1] != s[pos]) {
      last = ptr[last].failLink;
    }
    int ch = s[pos] - 'a';
    if (ptr[last].nxt[ch]) {
      last = ptr[last].nxt[ch];
      ptr[last].mask |= (1 << bit);
      return;
    }
    cnt += 1;
    ptr[cnt] = NIL;
    ptr[last].nxt[ch] = cnt;
    ptr[cnt].len = ptr[last].len + 2;
    ptr[cnt].mask = (1 << bit);
    ptr[cnt].failLink = 2;
    int suff = ptr[last].failLink;
    last = cnt;
    if (ptr[last].len == 1) {
      return;
    }
    while (s[pos - ptr[suff].len - 1] != s[pos]) {
      suff = ptr[suff].failLink;
    }
    ptr[last].failLink = ptr[suff].nxt[ch];
  }

  int solve() {
    int ans = 0;
    for (int i = 1; i <= cnt; ++i) {
      if (ptr[i].mask == 3) {
        ans += 1;
      }
    }
    return ans;
  }
};

void testCase() {
  string s, t;
  fin >> s >> t;
  int n = s.size(), m = t.size();
  s = '$' + s;
  t = '$' + t;
  PalindromicTree pt;
  for (int i = 1; i <= n; ++i) {
    pt.extend(s, i, 0);
  }
  pt.last = 1;
  for (int i = 1; i <= m; ++i) {
    pt.extend(t, i, 1);
  }
  fout << pt.solve() << '\n';
}

int main() {
  int tests = 1;
  for (int tc = 0; tc < tests; ++tc) {
    testCase();
  }
  fin.close();
  fout.close();
  return 0;
}
