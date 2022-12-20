#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("ahocorasick.in");
ofstream fout("ahocorasick.out");
 
const int kN = 100;
const int kSigma = 26;
 
struct node {
  int index, dp;
  node* nxt[kSigma];
  node* failLink;
  node* outputLink;
 
  node() : index(-1), dp(0), failLink(nullptr), outputLink(nullptr) {
    for (int c = 0; c < kSigma; ++c) {
      nxt[c] = nullptr;
    }
  }
};
 
string A, s;
vector<node*> order;
node* ptr[kN];
 
void ins(node* root, int p, int index) {
  if (p == (int)s.size()) {
    root->index = index;
    ptr[index] = root;
    return;
  }
  int c = s[p] - 'a';
  if (!root->nxt[c]) {
    root->nxt[c] = new node;
  }
  ins(root->nxt[c], p + 1, index);
}
 
void buildAho(node* root) {
  root->failLink = root->outputLink = root;
  queue<node*> q;
  for (int c = 0; c < kSigma; ++c) {
    if (root->nxt[c]) {
      node* v = root->nxt[c];
      v->failLink = root;
      v->outputLink = root;
      q.emplace(v);
    }
  }
  order.emplace_back(root);
  while (!q.empty()) {
    node* u = q.front();
    q.pop();
    order.emplace_back(u);
    for (int c = 0; c < kSigma; ++c) {
      if (u->nxt[c]) {
        node* v = u->nxt[c];
        node* tmp = u->failLink;
        while (!tmp->nxt[c] && tmp != root) {
          tmp = tmp->failLink;
        }
        if (tmp->nxt[c]) {
          v->failLink = tmp->nxt[c];
        } else {
          v->failLink = root;
        }
        if (v->failLink->index != -1) {
          v->outputLink = v->failLink;
        } else {
          v->outputLink = v->failLink->outputLink;
        }
        q.emplace(v);
      }
    }
  }
}
 
void findAllOccurences(node* root) {
  node* u = root;
  for (size_t i = 0; i < A.size(); ++i) {
    int c = A[i] - 'a';
    while (!u->nxt[c] && u != root) {
      u = u->failLink;
    }
    if (u->nxt[c]) {
      u = u->nxt[c];
    }
    if (u->index != -1) {
      fout << u->index << ' ' << i << '\n';
    }
    node* tmp = u;
    while (tmp->outputLink != root) {
      tmp = tmp->outputLink;
      fout << tmp->index << ' ' << i << '\n';
    }
  }
}
 
void makeCount(node* root) {
  node* u = root;
  for (size_t i = 0; i < A.size(); ++i) {
    int c = A[i] - 'a';
    while (!u->nxt[c] && u != root) {
      u = u->failLink;
    }
    if (u->nxt[c]) {
      u = u->nxt[c];
    }
    u->dp += 1;
  }
  reverse(order.begin(), order.end());
  for (auto it : order) {
    it->outputLink->dp += it->dp;
  }
}
 
void testCase() {
  fin >> A;
  int n;
  fin >> n;
  node* root = new node;
  for (int i = 0; i < n; ++i) {
    fin >> s;
    ins(root, 0, i);
  }
  buildAho(root);
  /// findAllOccurences(root);
  makeCount(root);
  for (int i = 0; i < n; ++i) {
    fout << ptr[i]->dp << '\n';
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
