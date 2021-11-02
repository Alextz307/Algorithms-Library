#include <bits/stdc++.h>

using namespace std;

ifstream fin("secv8.in");
ofstream fout("secv8.out");

const int mod = 805306457;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct treapNode {
  treapNode* l;
  treapNode* r;
  int key, prior, sz;
  bool rev;
};

using pt = pair<treapNode*, treapNode*>;
treapNode* emptyNode = new treapNode{nullptr, nullptr, -1, -1, 0, false};
treapNode* root = emptyNode;

void push(treapNode* node) {
  if (node != emptyNode && node->rev) {
    swap(node->l, node->r);
    node->l->rev ^= 1;
    node->r->rev ^= 1;
    node->rev = false;
  }
}

void updateSize(treapNode* node) {
  if (node != emptyNode) {
    node->sz = 1 + node->l->sz + node->r->sz;
  }
}

pt split(treapNode* node, int k) {
  if (node == emptyNode) {
    return {emptyNode, emptyNode};
  }
  push(node);
  if (node->l->sz < k) {
    pt p = split(node->r, k - node->l->sz - 1);
    node->r = p.first;
    updateSize(node);
    return {node, p.second};
  }
  pt p = split(node->l, k);
  node->l = p.second;
  updateSize(node);
  return {p.first, node};
}

treapNode* join(treapNode* A, treapNode* B) {
  if (A == emptyNode) {
    return B;
  }
  if (B == emptyNode) {
    return A;
  }
  push(A);
  push(B);
  if (B->prior < A->prior) {
    A->r = join(A->r, B);
    updateSize(A);
    return A;
  }
  B->l = join(A, B->l);
  updateSize(B);
  return B;
}

treapNode* ins(treapNode* node, int k, treapNode* newNode) {
  pt p = split(node, k - 1);
  return join(join(p.first, newNode), p.second);
}

treapNode* rev(treapNode* node, int st, int dr) {
  pt p1 = split(node, st - 1);
  pt p2 = split(p1.second, dr - st + 1);
  p2.first->rev ^= 1;
  return join(join(p1.first, p2.first), p2.second);
}

treapNode* rem(treapNode* node, int st, int dr) {
  pt p1 = split(node, st - 1);
  pt p2 = split(p1.second, dr - st + 1);
  return join(p1.first, p2.second);
}

int getElement(treapNode* node, int k) {
  push(node);
  if (node->l->sz + 1 == k) {
    return node->key;
  }
  if (k <= node->l->sz) {
    return getElement(node->l, k);
  }
  return getElement(node->r, k - node->l->sz - 1);
}

void inOrder(treapNode* node) {
  if (node == emptyNode) {
    return;
  }
  push(node);
  inOrder(node->l);
  fout << node->key << ' ';
  inOrder(node->r);
}

void solveQuery(int i) {
  char op;
  fin >> op;
  if (op == 'A') {
    int k;
    fin >> k;
    fout << getElement(root, k) << '\n';
    return;
  }
  if (op == 'I') {
    int k, x;
    fin >> k >> x;
    root = ins(root, k, new treapNode{emptyNode, emptyNode, x, rng() % mod, 1, false});
    return;
  }
  if (op == 'R') {
    int st, dr;
    fin >> st >> dr;
    root = rev(root, st, dr);
    return;
  }
  int st, dr;
  fin >> st >> dr;
  root = rem(root, st, dr);
}

void TestCase() {
  int q;
  bool ok_rev;
  fin >> q >> ok_rev;
  for (int i = 1; i <= q; ++i) {
    solveQuery(i);
  }
  inOrder(root);
  fout << '\n';
}

int main() {
  int tests = 1;
  for (int tc = 1; tc <= tests; ++tc) {
    TestCase();
  }
  fin.close();
  fout.close();
  return 0;
}
