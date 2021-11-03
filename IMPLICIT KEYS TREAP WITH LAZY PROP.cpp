#include <bits/stdc++.h>

using namespace std;

const int buffDim = 1 << 13;

struct InParser {
  FILE* fin;
  char* buff;
  int sp;

  char read_ch() {
    ++sp;
    if (sp == buffDim) {
      sp = 0;
      fread(buff, 1, buffDim, fin);
    }
    return buff[sp];
  }

  InParser(const char* nume) {
    fin = fopen(nume, "r");
    buff = new char[buffDim]();
    sp = buffDim - 1;
  }

  InParser& operator >> (char &ch) {
    char c = read_ch();
    ch = c;
    return *this;
  }

  InParser& operator >> (int &n) {
    char c;
    while (!isdigit(c = read_ch()) && c != '-');
    int sgn = 1;
    if (c == '-') {
      n = 0;
      sgn = -1;
    } else {
      n = c - '0';
    }
    while (isdigit(c = read_ch())) {
      n = 10 * n + c - '0';
    }
    n *= sgn;
    return *this;
  }

  InParser & operator >> (long long &n) {
    char c;
    n = 0;
    while (!isdigit(c = read_ch()) && c != '-');
    long long sgn = 1;
    if (c == '-') {
      n = 0;
      sgn = -1;
    } else {
      n = c - '0';
    }
    while (isdigit(c = read_ch())) {
      n = 10 * n + c - '0';
    }
    n *= sgn;
    return *this;
  }

  void close() {
    fclose(fin);
  }
};

InParser fin("diez.in");
ofstream fout("diez.out");

const int base = 53;
const int mod = 805306457;
const int kLen = 5e5;
const int kN = 2e5 + 5e4;
int n, m, p[1 + kLen], invp[1 + kLen];
char s[1 + kLen];

void multSelf(int &x, const int &y) {
  x = (int64_t)x * y % mod;
}

int mult(int x, const int &y) {
  multSelf(x, y);
  return x;
}


void addSelf(int &x, const int &y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int add(int x, const int &y, const int &z) {
  addSelf(x, y);
  addSelf(x, z);
  return x;
}

int Pow(int x, int n) {
  int ans = 1;
  while (n) {
    if (n & 1) {
      multSelf(ans, x);
    }
    multSelf(x, x);
    n >>= 1;
  }
  return ans;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct treapNode {
  treapNode* l;
  treapNode* r;
  int key, prior, sz, sum, lazy;
};

treapNode* emptyNode = new treapNode{nullptr, nullptr, 0, -1, 0, 0, 1};
using pt = pair<treapNode*, treapNode*>;

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
    swap(best->prior, node->prior);
    heapify(best);
  }
}

void update(treapNode* node) {
  if (node != emptyNode) {
    node->sz = 1 + node->l->sz + node->r->sz;
    node->sum = add(node->key, node->l->sum, node->r->sum);
  }
}

treapNode* build(int st, int dr) {
  int mid = (st + dr) >> 1;
  int val = s[mid] - 'a' + 1;
  treapNode* node = new treapNode{emptyNode, emptyNode, mult(p[n - mid], val), rng() % mod, 1, mult(p[n - mid], val), 1};
  if (st < mid) {
    node->l = build(st, mid - 1);
  }
  if (mid < dr) {
    node->r = build(mid + 1, dr);
  }
  heapify(node);
  update(node);
  return node;
}

void updateNode(treapNode* node, int val) {
  multSelf(node->key, val);
  multSelf(node->sum, val);
  multSelf(node->lazy, val);
}

void push(treapNode* node) {
  if (node != emptyNode && node->lazy != 1) {
    updateNode(node->l, node->lazy);
    updateNode(node->r, node->lazy);
    node->lazy = 1;
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
    update(node);
    return {node, p.second};
  }
  pt p = split(node->l, k);
  node->l = p.second;
  update(node);
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
    update(A);
    return A;
  }
  B->l = join(A, B->l);
  update(B);
  return B;
}

treapNode* ins(treapNode* node, int k, treapNode* newNode) {
  pt p = split(node, k - 1);
  updateNode(p.first, base);
  return join(join(p.first, newNode), p.second);
}

int query(treapNode* node, int st, int dr) {
  pt p1 = split(node, st - 1);
  pt p2 = split(p1.second, dr - st + 1);
  int ans = p2.first->sum, expo = n - dr;
  multSelf(ans, invp[expo]);
  p1.second = join(p2.first, p2.second);
  node = join(p1.first, p1.second);
  return ans;
}

void TestCase() {
  fin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    fin >> s[i];
  }
  p[0] = invp[0] = 1;
  for (int i = 1; i <= n + m; ++i) {
    p[i] = mult(p[i - 1], base);
    invp[i] = Pow(p[i], mod - 2);
  }
  treapNode* root = build(1, n);
  for (int i = 1; i <= m; ++i) {
    int op;
    fin >> op;
    if (op == 1) {
      int pos;
      char c;
      fin >> pos >> c;
      ++pos;
      ++n;
      int val = c - 'a' + 1;
      treapNode* newNode = new treapNode{emptyNode, emptyNode, mult(p[n - pos], val), rng() % mod, 1, mult(p[n - pos], val), 1};
      root = ins(root, pos, newNode);
    } else {
      int q1, q2, len;
      fin >> q1 >> q2 >> len;
      if (query(root, q1 + 1, q1 + len) == query(root, q2 + 1, q2 + len)) {
        fout << "1\n";
      } else {
        fout << "0\n";
      }
    }
  }
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
