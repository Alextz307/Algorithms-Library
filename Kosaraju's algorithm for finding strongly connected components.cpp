#include <bits/stdc++.h>
#define nmax 100005

using namespace std;

ifstream f ("ctc.in");
ofstream g ("ctc.out");

int n, m, x, y, viz[nmax], nr;
vector < int > G[nmax], GT[nmax], CTC[nmax];
stack < int > S;

void read () {
    f >> n >> m;
    while (m --) {
        f >> x >> y;
        G[x].push_back (y);
        GT[y].push_back (x);
    }
}

void DFSP (int k) {
    viz[k] = 1;
    for (unsigned int i = 0; i < G[k].size(); ++i) {
        int vecin = G[k][i];
        if (!viz[vecin]) DFSP (vecin);
    }
    S.push (k);
}

void DFSM (int k) {
    viz[k] = 2;
    CTC[nr].push_back (k);
    for (unsigned int i = 0; i < GT[k].size(); ++i) {
        int vecin = GT[k][i];
        if (viz[vecin] == 1) DFSM (vecin);
    }
}

void solve () {
    for (int i = 1; i <= n; ++i) if (!viz[i]) DFSP (i);
    while (!S.empty()) {
        int nod = S.top();
        S.pop();
        if (viz[nod] == 1) {
            nr ++;
            DFSM (nod);
        }
    }
}

void print () {
    g << nr << '\n';
    for (int i = 1; i <= nr; ++i, g << '\n')
    for (unsigned int j = 0; j < CTC[i].size(); ++j)
    g << CTC[i][j] << " ";
}

void Close () {
    f.close();
    g.close();
}

int main()
{
    read();
    solve();
    print();
    return 0;
}
