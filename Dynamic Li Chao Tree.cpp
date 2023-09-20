/// MIN
struct line {
  int m;
  int64_t b;
 
  int64_t eval(int x) {
    return (int64_t)m * x + b;
  }
};
 
struct node {
  line l;
  node* lSon;
  node* rSon;
 
  node(line _l) : l(_l), lSon(nullptr), rSon(nullptr) {}
};
 
void minSelf(int64_t &x, const int64_t &y) {
  if (y < x) {
    x = y;
  }
}
 
void addLine(node* x, int lx, int rx, line l) {
  if (lx == rx) {
    if (l.eval(lx) < x->l.eval(lx)) {
      x->l = l;
    }
    return;
  }
  int mid = (lx + rx) >> 1;
  
  if (l.m < x->l.m) {
    swap(x->l, l);
  }
  
  if (l.eval(mid) < x->l.eval(mid)) {
    swap(x->l, l);
    
    if (x->rSon) {
      addLine(x->rSon, mid + 1, rx, l);
    } else {
      x->rSon = new node(l);
    }
  } else {
    if (x->lSon) {
      addLine(x->lSon, lx, mid, l);
    } else {
      x->lSon = new node(l);
    }
  }
}
 
int64_t query(node* x, int lx, int rx, int pos) {
  int64_t val = x->l.eval(pos);
  
  if (lx == rx) {
    return val;
  }
  
  int mid = (lx + rx) >> 1;
  
  if (pos <= mid) {
    if (x->lSon) {
      minSelf(val, query(x->lSon, lx, mid, pos));
    }
  } else {
    if (x->rSon) {
      minSelf(val, query(x->rSon, mid + 1, rx, pos));
    }
  }
  
  return val;
}
