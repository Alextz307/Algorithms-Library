/*
       r                              R
      / \      Left Rotate(zag)      / \
     L  R        ———>               r  Y
       / \                         / \
      X  Y                        L  X
*/

/// inOrder: L r X R Y
/// inOrder(zag): L r X R Y


/*
      r                              L
     / \     Right Rotate(zig)      / \
    L  R         ———>              X   r
   / \                                / \
  X  Y                               Y  R
*/

/// inOrder: X L Y r R
/// inOrder(zig): X L Y r R

/// splay(x): => x - devine radacina
/// Fie y = parent(x)

/// Cazul 1: x - radacina => nu se mai face nimic

/// Cazul 2: y - radacina => se face zig sau zag daca x este fiu stang sau drept

/// Cazul 3: x si y sunt "in aceeasi directie"(ambii copii stangi sau drepti) => se face zig sau zag de 2 ori, dar prima data cu muchia de sus.

/// Cazul 4: x si y sunt "in directii diferite" => se incepe acum cu muchia de jos si se face zig sau zag dupa caz

/// De aici Link-Cut tree:
/// La Link-Cut tree se descompune un arbore in chain-uri si se tine cate un splay-tree pe fiecare chain.
/// Chain-urile respecta proprietatea ca orice nod dintr-un arbore are maxim o muchie de la el la un copil "marcata"(muchie dintr-un chain)
/// Splay-tree-urile sunt create pe chain-uri astfel incat din parcurgerile lor in ordine(stanga, radacina, dreapta) sa rezulte chiar chain-ul de sus in jos

struct node {
  int label, sz;
  node* l; /// pointer la copilul stang in splay tree
  node* r; /// pointer la copilul drept in splay tree
  node* p; /// parintele in splay tree
  node* pp; /// parintele din urmatorul chain(legatura e de forma root->nod_din_urmatorul_chain,
           /// unde nod_din_urmatorul_chain e chiar nodul, nu neaparat root-ul urmatorului chain)

  node(int v) : label(v), sz(1), l(nullptr), r(nullptr), p(nullptr), pp(nullptr) {}
};

struct LCT {
  vector<node*> nodes;

  LCT(int n) {
    nodes.reserve(n);
    for (int v = 0; v < n; ++v) {
      nodes.emplace_back(new node(v));
    }
  }

  void updateNode(node* x) {
    if (x) {
      x->sz = 1;
      if (x->l) {
        x->sz += x->l->sz;
      }
      if (x->r) {
        x->sz += x->r->sz;
      }
    }
  }

  void zig(node* x) {
    node* y = x->p;
    node* z = y->p;
    y->l = x->r;
    x->r = y;
    if (y->l) {
      y->l->p = y;
    }
    y->p = x;
    x->pp = y->pp;
    y->pp = nullptr;
    x->p = z;
    if (z) {
      if (y == z->l) {
        z->l = x;
      } else {
        z->r = x;
      }
    }
    updateNode(y);
    updateNode(x);
    updateNode(z);
  }

  void zag(node* x) {
    node* y = x->p;
    node* z = y->p;
    y->r = x->l;
    x->l = y;
    if (y->r) {
      y->r->p = y;
    }
    y->p = x;
    x->pp = y->pp;
    y->pp = nullptr;
    x->p = z;
    if (z) {
      if (y == z->l) {
        z->l = x;
      } else {
        z->r = x;
      }
    }
    updateNode(y);
    updateNode(x);
    updateNode(z);
  }

  void splay(node* x) {
    while (x->p) {
      node* y = x->p;
      if (y->p == nullptr) { /// Cazul 2
        if (x == y->l) {
          zig(x);
        } else {
          zag(x);
        }
      } else {
        node* z = y->p;
        if (y == z->l) {
          if (x == y->l) { /// Cazul 3
            zig(y);
            zig(x);
          } else { /// Cazul 4
            zag(x);
            zig(x);
          }
        } else {
          if (x == y->r) { /// Cazul 3
            zag(y);
            zag(x);
          } else { /// Cazul 4
            zig(x);
            zag(x);
          }
        }
      }
    }
    updateNode(x);
  }

  node* access(node* x) { /// creeaza un chain de la v la radacina arborelui din care face parte v si in care v este cel mai de jos nod
    splay(x); /// fac x radacina in splay
    if (x->r) { /// fac un nou chain cu partea de jos a chain-ului curent(pentru ca v trebuie sa fie cel mai de jos nod)
      x->r->pp = x;
      x->r->p = nullptr;
      x->r = nullptr;
      updateNode(x);
    }
    node* last = x;
    while (x->pp) {
      node* y = x->pp;
      last = y;
      splay(y); /// fac y radacina sa scap usor de ce vine dupa el in jos(seamana aici cu split-ul de la treapuri)
      if (y->r) { /// fac un nou chain cu partea de jos a chain-ului cu care trebuie sa unesc chain-ul curent
        y->r->pp = y;
        y->r->p = nullptr;
      }
      y->r = x; /// in dreapta ca e mai jos
      x->p = y;
      x->pp = nullptr;
      updateNode(y);
      splay(x); /// pentru ca am facut x radacina, pp-ul splay-ului din care face parte x trece la x
    }
    return last;
  }

  node* getRoot(node* x) { /// radacina arborelui din care face parte x
    access(x); /// fac un splay pe root->x in care la final x va fi radacina
    while (x->l) { /// ma duc in stanga ca sa ajung la radacina arborelui
      x = x->l;
    }
    splay(x);
    return x;
  }

  void link(node* x, node* y) { /// il face pe x copilul lui y
    access(x);
    access(y);
    x->l = y;
    y->p = x;
    y->pp = nullptr;
    updateNode(x);
  }

  void link(int u, int v) {
    link(nodes[u], nodes[v]);
  }

  void cut(node* x) { /// taie legatura parinte->x
    access(x);
    x->l->p = nullptr;
    x->l = nullptr;
    updateNode(x);
  }

  void cut(int v) {
    cut(nodes[v]);
  }

  bool connected(node* x, node* y) {
    return getRoot(x)->label == getRoot(y)->label;
  }

  bool connected(int u, int v) {
    return connected(nodes[u], nodes[v]);
  }

  int depth(node* x) {
    access(x); /// fac chain-ul
    return x->sz - 1; /// x e cel mai de jos
  }

  int depth(int v) {
    return depth(nodes[v]);
  }

  int lca(node* x, node* y) {
    access(x);
    return access(y)->label; /// y se opreste cand da de chain-ul root->x in lca(x, y)
  }

  int lca(int u, int v) {
    return lca(nodes[u], nodes[v]);
  }
};
