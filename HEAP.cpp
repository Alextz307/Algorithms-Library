struct Heap {
  vector<int> h{0}, entry{0}, pos{0};

  void swapNodes(int u, int v) {
    swap(h[u], h[v]);
    swap(pos[entry[u]], pos[entry[v]]);
    swap(entry[u], entry[v]);
  }

  void upHeap(int v) {
    while (1 < v && h[v] < h[v >> 1]) {
      swapNodes(v, v >> 1);
      v >>= 1;
    }
  }

  void Insert(int x) {
    entry.emplace_back(pos.size());
    pos.emplace_back(h.size());
    h.emplace_back(x);
    upHeap(h.size() - 1);
  }

  void EraseMin() {
    swapNodes(1, h.size() - 1);
    h.pop_back();
    entry.pop_back();
    int v = 1;
    while ((v << 1) < (int)h.size()) {
      int son = v << 1;
      if ((son | 1) < (int)h.size() && h[son | 1] < h[son]) {
        son |= 1;
      }
      if (h[v] <= h[son]) {
        break;
      }
      swapNodes(v, son);
      v = son;
    }
  }

  void Erase(int k) {
    int v = pos[k];
    h[v] = -1;
    upHeap(v);
    EraseMin();
  }

  int getMin() {
    return h[1];
  }
};
