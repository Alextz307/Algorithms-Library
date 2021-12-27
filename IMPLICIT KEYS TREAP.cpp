#include <bits/stdc++.h>

using namespace std;

ifstream fin("grid.in");
ofstream fout("grid.out");

struct treapNode {
  treapNode* l;
  treapNode* r;
  int key, prior, sz;
};

using ptr = treapNode*;
using pt = pair<ptr, ptr>;
const int mod = 1610612741;
ptr emptyNode = new treapNode{nullptr, nullptr, 0, -1, 0};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int n, k;

void updateNode(ptr node) {
  if (node != emptyNode) {
    node->sz = node->l->sz + 1 + node->r->sz;
  }
}

void heapify(treapNode* node) {
  if (node == emptyNode) {
    return;
  }
  treapNode* best = node;
  if (best->prior < node->l->prior) {
    best = node->l;
  }
  if (best->prior < node->r->prior) {
    best = node->r;
  }
  if (best != node) {
    swap(node->prior, best->prior);
    heapify(best);
  }
}

treapNode* build(int st, int dr, int lin) {
  int mid = (st + dr) >> 1;
  treapNode* node = new treapNode{emptyNode, emptyNode, mid + lin * n, rng() % mod, 1};
  if (st < mid) {
    node->l = build(st, mid - 1, lin);
  }
  if (mid < dr) {
    node->r = build(mid + 1, dr, lin);
  }
  heapify(node);
  updateNode(node);
  return node;
}

pt split(ptr node, int k) {
  if (node == emptyNode) {
    return {emptyNode, emptyNode};
  }
  if (node->l->sz < k) {
    pt p = split(node->r, k - node->l->sz - 1);
    node->r = p.first;
    updateNode(node);
    return {node, p.second};
  }
  pt p = split(node->l, k);
  node->l = p.second;
  updateNode(node);
  return {p.first, node};
}

ptr join(ptr A, ptr B) {
  if (A == emptyNode) {
    return B;
  }
  if (B == emptyNode) {
    return A;
  }
  if (B->prior < A->prior) {
    A->r = join(A->r, B);
    updateNode(A);
    return A;
  }
  B->l = join(A, B->l);
  updateNode(B);
  return B;
}

int getElement(ptr node, int k) {
  if (node->l->sz + 1 == k) {
    return node->key;
  }
  if (k <= node->l->sz) {
    return getElement(node->l, k);
  }
  return getElement(node->r, k - node->l->sz - 1);
}

ptr ins(ptr node, int k, ptr newNode) {
  pt p = split(node, k - 1);
  return join(join(p.first, newNode), p.second);
}

ptr del(ptr node, int k) {
  pt p1 = split(node, k - 1);
  pt p2 = split(p1.second, 1);
  return join(p1.first, p2.second);
}

void dfs(ptr node) {
  if (node == emptyNode) {
    return;
  }
  dfs(node->l);
  fout << node->key << ' ';
  dfs(node->r);
}

void testCase() {
  fin >> n >> k;
  ptr roots[3];
  for (int i = 0; i < 3; ++i) {
    roots[i] = build(1, n, i);
  }
  for (int i = 0; i < k; ++i) {
    int x1, y1, x2, y2;
    fin >> x1 >> y1 >> x2 >> y2;
    y1 += 1, y2 += 1;
    int key = getElement(roots[x1], y1);
    roots[x1] = del(roots[x1], y1);
    roots[x2] = ins(roots[x2], y2, new treapNode{emptyNode, emptyNode, key, rng() % mod, 1});
  }
  for (int i = 0; i < 3; ++i) {
    dfs(roots[i]);
    fout << '\n';
  }
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
