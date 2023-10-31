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
    vector<vector<int>> G, RG, components;
    vector<bool> used;
    vector<int> order;
    int n;

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

void testCase() {
    int n, m;
    cin >> n >> m;
    int oldN = n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<vector<int> > G(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
    }
    SCC scc(G);

    n = scc.components.size();
    vector<ll> c(oldN + 1), b(n + 1);
    for (int i = 0; i < n; i++)
        for (auto v: scc.components[i])
            c[v] = i + 1, b[c[v]] += a[v];

    vector<set<int> > newG(n + 1);

    for (int i = 1; i <= oldN; i++) {
        for (auto v: G[i]) {
            if (c[i] ^ c[v])
                newG[c[i]].insert(c[v]);
        }
    }

    vector<ll> dp(n + 1, -1);
    function<ll(int u)> solve = [&](int u) {
        ll &ret = dp[u];
        if (ret + 1) return ret;
        ret = b[u];
        for (auto v: newG[u]) ret = max(ret, solve(v) + b[u]);
        return ret;
    };

    ll ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, solve(i));

    cout << ans << endl;
}
