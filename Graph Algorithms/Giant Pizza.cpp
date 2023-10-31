#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define oo 1e18
#define endl '\n'
#define all(v) v.begin(),v.end()

#ifdef LOCAL

#include "assets/debug.h"

#else
#define dd(x...)
#define ExeTime
#endif

void testCase();

int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};
const int N = 2e5 + 10, M = 1e2 + 10, mod = 998244353;
const double EPS = 1e-12, PI = acos(-1);

void init() {}

int main() {
    init();
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
//    cin >> T;
    while (T--) testCase();
    ExeTime;
}


struct var {
    int name, idx;
    bool isNeg;

    var(int name = 0, bool isNeg = false) : name(name), isNeg(isNeg) {
        idx = 2 * name + !isNeg;
    }

    var neg() {
        return var(name, !isNeg);
    }
};

struct SAT {
    int n;
    vector<vector<int> > g, gt;
    vector<bool> used;
    vector<int> order, comp;

    SAT(int sz) : n(sz * 2) {
        g.resize(n), used.resize(n);
        gt.resize(n), comp.resize(n);
    }

    void dfs1(int u) {
        used[u] = true;
        for (int v: g[u]) if (!used[v]) dfs1(v);
        order.push_back(u);
    }

    void dfs2(int u, int cl) {
        comp[u] = cl;
        for (int v: gt[u]) if (!comp[v]) dfs2(v, cl);
    }

    vector<int> apply() {
        vector<int> sol;
        for (int i = 0; i < n; i++) if (!used[i]) dfs1(i);
        for (int i = 0, j = 1; i < n; ++i) {
            int v = order[n - i - 1];
            if (!comp[v]) dfs2(v, j++);
        }
        for (int i = 0; i < n; i++)
            if (comp[i] == comp[i ^ 1])
                return vector<int>();
        for (int i = 0; i < n; i += 2) {
            int ans = comp[i] > comp[i ^ 1] ? i : i ^ 1;
            sol.push_back(ans & 1);
        }
        return sol;
    }

    void imply(var a, var b) {
        g[a.idx].push_back(b.idx);
        g[b.idx ^ 1].push_back(a.idx ^ 1);
        gt[b.idx].push_back(a.idx);
        gt[a.idx ^ 1].push_back(b.idx ^ 1);
    }

    void addOr(var a, var b) {
        imply(a.neg(), b);
        imply(b.neg(), a);
    }

    void addTrue(var a) {
        imply(a.neg(), a);
        imply(a, a.neg());
    }

    void addXOR(var a, var b) {
        addOr(a, b);
        addOr(a.neg(), b.neg());
    }
};

void testCase() {
    int n, m;
    cin >> n >> m;
    SAT sat(m);
    for (int i = 0; i < n; i++) {
        char c;
        int x;
        cin >> c >> x;
        x--;
        var p, q;
        if (c == '+') {
            p = var(x, false);
        } else {
            p = var(x, true);
        }
        cin >> c >> x;
        x--;
        if (c == '+') {
            q = var(x, false);
        } else {
            q = var(x, true);
        }
        sat.addOr(p, q);
    }

    auto ans = sat.apply();
    if (ans.empty()) return void(cout << "IMPOSSIBLE" << endl);
    for (int i = 0; i < m; i++) cout << (ans[i] ? '+' : '-') << ' ';
    cout << endl;
}
