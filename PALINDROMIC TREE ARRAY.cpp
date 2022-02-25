#include <bits/stdc++.h>

using namespace std;

ifstream fin("dorel.in");
ofstream fout("dorel.out");

const int kN = 1e4 + 4;

struct node {
  short nxt[26];
  short len, failLink;
  char mask;

  node() {
    for (int c = 0; c < 26; ++c) {
      nxt[c] = 0;
    }
    len = 0;
    failLink = 0;
    mask = 0;
  }
} ptr[kN];

void maxSelf(int &x, int y) {
  if (x < y) {
    x = y;
  }
}

void minSelf(int &x, int y) {
  if (y < x) {
    x = y;
  }
}

node NIL;

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
        maxSelf(ans, ptr[i].len);
      }
    }
    return ans;
  }
};

void testCase() {
  string ss;
  fin >> ss;
  int n = ss.size();
  ss = '$' + ss;
  int q;
  fin >> q;
  for (int qq = 0; qq < q; ++qq) {
    int k;
    fin >> k;
    int st = k - 1, dr = k + 1;
    while (st > 0 && ss[st] < ss[k]) {
      st -= 1;
    }
    maxSelf(st, 1);
    while (dr <= n && ss[k] < ss[dr]) {
      dr += 1;
    }
    minSelf(dr, n);
    string s = "$", t = "$";
    for (int i = 1; i <= n; ++i) {
      if (st <= i && i <= dr) {
        t += ss[i];
      } else {
        s += ss[i];
      }
    }
    PalindromicTree pt;
    for (int i = 1; i < (int)s.size(); ++i) {
      pt.extend(s, i, 0);
    }
    pt.last = 1;
    for (int i = 1; i < (int)t.size(); ++i) {
      pt.extend(t, i, 1);
    }
    fout << pt.solve() << ' ';
  }
  fout << '\n';
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
