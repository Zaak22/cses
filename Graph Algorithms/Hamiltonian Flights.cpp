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
const int N = 2e5 + 10, M = 1e2 + 10, mod = 1e9 + 7;
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

void testCase() {
    int m, n;
    cin >> n >> m;
    vector<vector<ll> > G(n + 1, vector<ll>(n + 1, 0));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u != v) G[u][v]++;
    }
    int all = (1 << (n - 1)) - 1;
    vector<vector<ll> > dp(all + 1, vector<ll>(n, 0));
    dp[all][n - 1] = 1;
    for (int mask = all; mask >= 0; mask--) {
        for (int u = 0; u < n - 1; u++) {
            if (mask & (1 << u)) continue;
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;
                dp[mask][u] += dp[mask | (1 << u)][v] * G[u][v];
                dp[mask][u] %= mod;
            }
        }
    }
    cout << dp[0][0] << endl;
}
