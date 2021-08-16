#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("secv8.in");
ofstream fout("secv8.out");
 
struct treap {
  treap* l;
  treap* r;
  int val, priority, sz;
  bool rev;
};
 
using pt = pair<treap*,treap*>;
const int mod = 1e9 + 7;
const int NMAX = 5e5 + 5;
int a[NMAX];
treap* emptyNode = new treap{nullptr, nullptr, 0, 0, 0, false};
treap* root = emptyNode;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
void update_sz(treap* nod) {
  if (nod != emptyNode)
    nod->sz = nod->l->sz + nod->r->sz + 1;
}
 
void heapify(treap* nod) {
  if (nod == emptyNode)
    return;
  treap* best = nod;
  if (nod->l != nullptr && nod->l->priority > best->priority)
    best = nod->l;
  if (nod->r != nullptr && nod->r->priority > best->priority)
    best = nod->r;
  if (best != nod) {
    swap(nod->priority, best->priority);
    heapify(best);
  }
}
 
treap* build(int st, int dr) {
  int mid = (st + dr) >> 1;
  treap* nod = new treap{emptyNode, emptyNode, a[mid], rng() % mod, 1};
  if (st < mid)
    nod->l = build(st, mid - 1);
  if (mid < dr)
    nod->r = build(mid + 1, dr);
  heapify(nod);
  update_sz(nod);
  return nod;
}
 
void push_rev(treap* nod) {
  if (nod != emptyNode && nod->rev) {
    swap(nod->l, nod->r);
    nod->l->rev ^= true;
    nod->r->rev ^= true;
    nod->rev = false;
  }
}
 
pt split(treap* nod, int poz) {
  if (nod == emptyNode)
    return {emptyNode, emptyNode};
  push_rev(nod);
  pt ans;
  if (nod->l->sz >= poz) {
    ans.second = nod;
    pt aux = split(nod->l, poz);
    ans.first = aux.first;
    ans.second->l = aux.second;
    update_sz(ans.second);
  } else {
    ans.first = nod;
    pt aux = split(nod->r, poz - nod->l->sz - 1);
    ans.first->r = aux.first;
    ans.second = aux.second;
    update_sz(ans.first);
  }
  return ans;
}
 
treap* join(treap* st, treap* dr) {
  push_rev(st), push_rev(dr);
  if (st == emptyNode)
    return dr;
  if (dr == emptyNode)
    return st;
  if (st->priority > dr->priority) {
    st->r = join(st->r, dr);
    update_sz(st);
    return st;
  }
  dr->l = join(st, dr->l);
  update_sz(dr);
  return dr;
}
 
treap* add(treap* nod, int poz, int val) {
  pt aux = split(nod, poz - 1);
  treap* newNode = new treap{emptyNode, emptyNode, val, rng() % mod, 1, false};
  return join(join(aux.first, newNode), aux.second);
}
 
treap* invers(treap* nod, int st, int dr) {
  pt p1 = split(nod, st - 1);
  pt p2 = split(p1.second, dr - st + 1);
  p2.first->rev ^= true;
  return join(join(p1.first, p2.first), p2.second);
}
 
treap* del(treap* nod, int st, int dr) {
  pt p1 = split(nod, st - 1);
  pt p2 = split(p1.second, dr - st + 1);
  return join(p1.first, p2.second);
}
 
int element(treap* nod, int poz) {
  push_rev(nod);
  if (nod->l->sz + 1 == poz)
    return nod->val;
  if (nod->l->sz >= poz)
    return element(nod->l, poz);
  return element(nod->r, poz - nod->l->sz - 1);
}
 
void solve_query() {
  char op;
  fin >> op;
  if (op == 'A') {
    int k;
    fin >> k;
    fout << element(root, k) << '\n';
    return;
  }
  if (op == 'I') {
    int k, x;
    fin >> k >> x;
    root = add(root, k, x);
    return;
  }
  if (op == 'R') {
    int st, dr;
    fin >> st >> dr;
    root = invers(root, st, dr);
    return;
  }
  int st, dr;
  fin >> st >> dr;
  root = del(root, st, dr);
}
 
void solve() {
  int Q;
  bool ok_rev;
  fin >> Q >> ok_rev;
  for (int q = 0; q < Q; ++q)
    solve_query();
  for (int i = 1; i <= root->sz; ++i)
    fout << element(root, i) << ' ';
  fout << '\n';
}
 
void close_files() {
  fin.close();
  fout.close();
}
 
int main() {
  solve();
  close_files();
  return 0;
}