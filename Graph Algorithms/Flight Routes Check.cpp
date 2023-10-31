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

struct SCC {
    int n;
    vector<vector<int>> G, RG, components;
    vector<bool> used;
    vector<int> order;

    SCC(vector<vector<int> > G) : G(G), n(G.size()) {
        RG.assign(n, vector<int>());
        used.assign(n, false);
        for (int u = 0; u < n; u++)
            for (int v: G[u])
                RG[v].push_back(u);

        for (int i = 1; i < n; i++)
            if (!used[i]) dfs1(i);

        fill(all(used), false);

        for (int i = order.size() - 1; i >= 0; i--) {
            if (!used[order[i]]) {
                components.push_back({});
                dfs2(order[i]);
            }
        }
    }

    void dfs1(int v) {
        used[v] = true;
        for (auto u: G[v])
            if (!used[u]) dfs1(u);
        order.push_back(v);
    }

    void dfs2(int v) {
        used[v] = true;
        components.back().push_back(v);
        for (auto u: RG[v])
            if (!used[u]) dfs2(u);
    }
};

vector<vector<int> > G;

void testCase() {
    int n, m;
    cin >> n >> m;
    G.assign(n + 1, vector<int>());
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
    }

    SCC scc(G);
    vector<int> res;
    for (auto comp: scc.components) {
        res.push_back(comp.back());
        if (res.size() > 1) break;
    }

    if (res.size() < 2) return void(cout << "YES" << endl);

    cout << "NO" << endl;

    int st = res[0], en = res[1];
    vector<bool> vis(n + 1, false);
    function<void(int)> dfs = [&](int u) {
        vis[u] = true;
        for (auto v: G[u]) {
            if (!vis[v]) dfs(v);
        }
    };
    dfs(st);

    if (vis[en]) {
        cout << en << ' ' << st << endl;
    } else {
        cout << st << ' ' << en << endl;
    }

}
