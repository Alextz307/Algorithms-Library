#include <bits/stdc++.h>

using namespace std;

struct treapNode {
  treapNode* l;
  treapNode* r;
  int key, prior, sz;
  int64_t sum;
  bool rev;
};

using ptr = treapNode*;
using pt = pair<ptr, ptr>;
const int kN = 2e5;
const int mod = 1610612741;
ptr emptyNode = new treapNode{nullptr, nullptr, 0, -1, 0, 0, 0};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int a[1 + kN];
ptr root;

void updateNode(ptr node) {
  if (node != emptyNode) {
    node->sz = node->l->sz + 1 + node->r->sz;
    node->sum = node->l->sum + node->key + node->r->sum;
  }
}

void push(ptr node) {
  if (node != emptyNode && node->rev) {
    swap(node->l, node->r);
    node->l->rev ^= 1;
    node->r->rev ^= 1;
    node->rev = false;
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

ptr build(int st, int dr) {
  int mid = (st + dr) / 2;
  ptr node = new treapNode{emptyNode, emptyNode, a[mid], rng() % mod, 1, a[mid], 0};
  if (st < mid) {
    node->l = build(st, mid - 1);
  }
  if (mid < dr) {
    node->r = build(mid + 1, dr);
  }
  heapify(node);
  updateNode(node);
  return node;
}

pt split(ptr node, int k) {
  if (node == emptyNode) {
    return {emptyNode, emptyNode};
  }
  push(node);
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
  push(A);
  push(B);
  if (B->prior < A->prior) {
    A->r = join(A->r, B);
    updateNode(A);
    return A;
  }
  B->l = join(A, B->l);
  updateNode(B);
  return B;
}

ptr update(ptr node, int l, int r) {
  pt p1 = split(node, l - 1);
  pt p2 = split(p1.second, r - l + 1);
  p2.first->rev ^= 1;
  p1.second = join(p2.first, p2.second);
  node = join(p1.first, p1.second);
}

int64_t query(ptr node, int l, int r) {
  pt p1 = split(node, l - 1);
  pt p2 = split(p1.second, r - l + 1);
  int64_t ret = p2.first->sum;
  p1.second = join(p2.first, p2.second);
  node = join(p1.first, p1.second);
  return ret;
}

void testCase() {
  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  root = build(1, n);
  for (int i = 0; i < q; ++i) {
    char op;
    int l, r;
    cin >> op >> l >> r;
    if (op == '1') {
      root = update(root, l, r);
    } else {
      cout << query(root, l, r) << '\n';
    }
  }
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
