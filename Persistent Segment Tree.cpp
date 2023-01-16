#include <bits/stdc++.h>
// Sample problem: https://oj.uz/problem/view/COCI21_index?locale=en

using namespace std;

const int N = 2e5;

struct node {
  node *l;
  node *r;
  int sum;

  node() : sum(0) {
    l = nullptr;
    r = nullptr;
  }
} *roots[1 + N];

void build(node *root, int lx, int rx) {
  if (lx == rx) {
    return;
  }

  int mid = (lx + rx) / 2;

  root->l = new node;
  build(root->l, lx, mid);

  root->r = new node;
  build(root->r, mid + 1, rx);
}

void update(node *prevRoot, node *root, int lx, int rx, int pos, int val) {
  if (lx == rx) {
    root->sum = prevRoot->sum + val;
    return;
  }

  int mid = (lx + rx) / 2;

  if (pos <= mid) {
    root->l = new node;

    root->r = prevRoot->r;

    update(prevRoot->l, root->l, lx, mid, pos, val);
  } else {
    root->l = prevRoot->l;

    root->r = new node;

    update(prevRoot->r, root->r, mid + 1, rx, pos, val);
  }

  root->sum = root->l->sum + root->r->sum;
}

int query(node *root, int lx, int rx, int st, int dr) {
  if (st <= lx && rx <= dr) {
    return root->sum;
  }

  int mid = (lx + rx) / 2;

  int sum = 0;

  if (st <= mid) {
    sum += query(root->l, lx, mid, st, dr);
  }

  if (mid < dr) {
    sum += query(root->r, mid + 1, rx, st, dr);
  }

  return sum;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  roots[0] = new node;
  build(roots[0], 1, N);

  for (int i = 1; i <= n; ++i) {
    int x;
    cin >> x;

    roots[i] = new node;
    update(roots[i - 1], roots[i], 1, N, x, 1);
  }

  for (int i = 0; i < q; ++i) {
    int l, r;
    cin >> l >> r;

    int st = 2, dr = r - l + 1, res = 1;

    while (st <= dr) {
      int mid = (st + dr) / 2;

      if (query(roots[r], 1, N, mid, N) - query(roots[l - 1], 1, N, mid, N) >= mid) {
        res = mid;
        st = mid + 1;
      } else {
        dr = mid - 1;
      }
    }

    cout << res << '\n';
  }

  return 0;
}
