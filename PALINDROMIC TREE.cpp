#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("unicat.in");
ofstream fout("unicat.out");
 
struct node {
  node* nxt[26];
  node* failLink; /// pointer la cel mai lung sufix care este palindrom(diferit de tot palindromul)
  int len; /// lungimea
  short mask;
 
  node() {
    for (int c = 0; c < 26; ++c) {
      nxt[c] = nullptr;
    }
    failLink = nullptr;
    len = 0;
    mask = 0;
  }
};
 
void maxSelf(int64_t &x, int64_t y) {
  if (x < y) {
    x = y;
  }
}
 
struct PalindromicTree {
  node* odd;
  node* even;
  node* last; /// ultimul nod in care am ajuns pana acum
  vector<node*> nodes; /// palindromurile obtinute in ordinea in care apar in sir
 
  PalindromicTree() {
    odd = new node();
    nodes.emplace_back(odd);
    even = new node();
    nodes.emplace_back(even);
    odd->len = -1;
    odd->failLink = odd;
    even->failLink = odd;
    last = odd;
  }
 
  void extend(const string &s, int pos, int bit) {
    while (last != odd && s[pos - last->len - 1] != s[pos]) {
      last = last->failLink;
    }
    int ch = s[pos] - 'a';
    if (last->nxt[ch]) {
      last = last->nxt[ch];
      last->mask |= (1 << bit);
      return;
    }
    last->nxt[ch] = new node();
    last->nxt[ch]->len = last->len + 2;
    node* suff = last->failLink;
    last = last->nxt[ch];
    last->mask = (1 << bit);
    last->failLink = even;
    nodes.emplace_back(last);
    if (last->len == 1) {
      return;
    }
    while (suff != odd && s[pos - suff->len - 1] != s[pos]) {
      suff = suff->failLink;
    }
    if (suff->nxt[ch]) {
      last->failLink = suff->nxt[ch];
    } else {
      last->failLink = even;
    }
  }
 
  int solve() {
    int ans = 0;
    for (auto it : nodes) {
      ans += it->mask == 3;
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
