#include <bits/stdc++.h>

using namespace std;

ifstream fin("bst.in");
ofstream fout("bst.out");

const int mod = 805306457;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct treapNode {
  treapNode* l;
  treapNode* r;
  int key, prior;

  treapNode(int _key) : l(nullptr), r(nullptr), key(_key), prior(rng() % mod) {}
};

using pt = pair<treapNode*, treapNode*>;

/*
      r                         R
     / \      Left Rotate      / \
    L   R        ———>         r  Y
       / \                   / \
      X   Y                 L   X
*/

void rotateLeft(treapNode* &node) {
  treapNode* R = node->r;
  treapNode* X = R->l;
  R->l = node;
  node->r = X;
  node = R;
}

/*
        r                        L
       / \     Right Rotate     / \
      L   R       ———>         X   r
     / \                          / \
    X   Y                        Y   R
*/

void rotateRight(treapNode* &node) {
  treapNode* L = node->l;
  treapNode* Y = L->r;
  L->r = node;
  node->l = Y;
  node = L;
}

pt split(treapNode* node, int x) {
  if (node == nullptr) {
    return {nullptr, nullptr};
  }
  if (node->key < x) {
    pt p = split(node->r, x);
    node->r = p.first;
    return {node, p.second};
  }
  pt p = split(node->l, x);
  node->l = p.second;
  return {p.first, node};
}

treapNode* join(treapNode* A, treapNode* B) {
  if (A == nullptr) {
    return B;
  }
  if (B == nullptr) {
    return A;
  }
  if (B->prior < A->prior) {
    A->r = join(A->r, B);
    return A;
  }
  B->l = join(A, B->l);
  return B;
}

void add(treapNode* &node, int key) {
  if (node == nullptr) {
    node = new treapNode(key);
    return;
  }
  if (key < node->key) {
    add(node->l, key);
    if (node->l != nullptr && node->l->prior < node->prior) {
      rotateRight(node);
    }
  } else {
    add(node->r, key);
    if (node->r != nullptr && node->r->prior < node->prior) {
      rotateLeft(node);
    }
  }
}

void rem(treapNode* &node, int key) {
  if (node == nullptr) {
    return;
  }
  if (key == node->key) {
    if (node->l == nullptr && node->r == nullptr) {
      delete node;
      node = nullptr;
      return;
    }
    if (node->l != nullptr && node->r != nullptr) {
      if (node->r->prior < node->l->prior) {
        rotateLeft(node);
        rem(node->l, key);
      } else {
        rotateRight(node);
        rem(node->r, key);
      }
      return;
    }
    treapNode* son = (node->l != nullptr) ? node->l : node->r;
    treapNode* victim = node;
    node = son;
    delete victim;
    return;
  }
  if (key < node->key) {
    rem(node->l, key);
  } else {
    rem(node->r, key);
  }
}

int getMin(treapNode* node) {
  if (node->l != nullptr) {
    return getMin(node->l);
  }
  return node->key;
}

int getMax(treapNode* node) {
  if (node->r != nullptr) {
    return getMax(node->r);
  }
  return node->key;
}

bool check(treapNode* node, int x) {
  if (node == nullptr) {
    return false;
  }
  if (node->key == x) {
    return true;
  }
  if (x < node->key) {
    return check(node->l, x);
  }
  return check(node->r, x);
}

void TestCase() {
  int n;
  fin >> n;
  treapNode* root = nullptr;
  for (int i = 1; i <= n; ++i) {
    int x;
    fin >> x;
    add(root, x);
  }
  for (int i = 1; i <= n; ++i) {
    int x = getMin(root);
    fout << x << ' ';
    rem(root, x);
  }
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
