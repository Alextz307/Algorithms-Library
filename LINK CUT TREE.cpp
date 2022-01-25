/*
       r                              R
      / \      Left Rotate(zag)      / \
     L  R        --->               r  Y
       / \                         / \
      X  Y                        L  X
*/

/// inOrder: L r X R Y
/// inOrder(zag): L r X R Y


/*
      r                              L
     / \     Right Rotate(zig)      / \
    L  R         --->              X   r
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
  bool rev;
  node* l; /// pointer la copilul stang in splay tree
  node* r; /// pointer la copilul drept in splay tree
  node* p; /// parintele in splay tree sau intre chain-uri(nu are rost sa tin 2 pointeri ca unul va fi mereu NULL)

  node() : rev(false), l(nullptr), r(nullptr), p(nullptr) {}
};

struct LCT {
  vector<node*> nodes;

  LCT(int n) {
    nodes.resize(n);
    for (int i = 0; i < n; ++i) {
      nodes[i] = new node();
    }
  }

  bool isChainTop(node* x) {
    return x->p == nullptr || (x->p->l != x && x->p->r != x);
  }

  void push(node* x) {
    if (x->rev) {
      swap(x->l, x->r);
      if (x->l) {
        x->l->rev ^= 1;
      }
      if (x->r) {
        x->r->rev ^= 1;
      }
      x->rev = false;
    }
  }

  void makeRotation(node* x) {
    node* y = x->p;
    node* z = y->p;
    if (!isChainTop(y)) {
      if (y == z->l) {
        z->l = x;
      } else {
        z->r = x;
      }
    }
    push(y);
    push(x);
    if (y->l == x) { /// zig
      y->l = x->r;
      x->r = y;
      if (y->l) {
        y->l->p = y;
      }
    } else { /// zag
      y->r = x->l;
      x->l = y;
      if (y->r) {
        y->r->p = y;
      }
    }
    y->p = x;
    x->p = z;
  }

  void splay(node* x) {
    while (!isChainTop(x)) {
      node* y = x->p;
      node* z = y->p;
      if (!isChainTop(y)) {
        if ((z->l == y) == (y->l == x)) {
          makeRotation(y);
        } else {
          makeRotation(x);
        }
      }
      makeRotation(x);
    }
    push(x);
  }

  node* access(node* x) { /// creeaza un chain de la v la radacina arborelui din care face parte v si in care v este cel mai de jos nod
    node* curr = x;
    node* last = nullptr;
    while (curr) {
      splay(curr);
      curr->r = last; /// schimb ce era dupa cu continuarea chain-ului
      last = curr;
      curr = curr->p;
    }
    splay(x);
    return last;
  }

  void reroot(node* x) { /// il fac pe x radacina
    access(x); /// creez chain-ul root->x
    if (x->l) { /// tot ce e mai sus de x inversez si pun intr-un chain separat
      x->l->rev ^= 1;
      x->l = nullptr;
    }
  }

  void link(int u, int v) {
    node* x = nodes[u];
    node* y = nodes[v];
    reroot(y); /// fac y radacina
    y->p = x; /// adaug legatura intre x si y
  }

  void cut(int u, int v) {
    node* x = nodes[u];
    node* y = nodes[v];
    reroot(x); /// fac pe x radacina
    splay(y);
    y->p = nullptr; /// elimin legatura dintre x si y
  }

  bool connected(int u, int v) {
    node* x = nodes[u];
    node* y = nodes[v];
    access(x);
    access(y);
    return x->p; /// daca sunt in acelasi arbore, dupa al doilea access x sigur are parinte
  }
};
