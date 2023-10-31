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

struct EulerPath {
    vector<multiset<int>> G;
    vector<int> path, deg;
    int n, v1, v2; // v1/v2: first/second node with odd degree
    bool ok; // could have euler tour

    EulerPath(vector<vector<int>> G) : n(G.size()) {
        this->G.assign(n, multiset<int>());
        for (int i = 0; i < n; i++)
            for (auto v: G[i]) this->G[i].insert(v);
        deg.resize(n);
        for (int i = 0; i < n; ++i) deg[i] = this->G[i].size();
        v1 = -1, v2 = -1;
        ok = true;
        for (int i = 0; i < n; ++i) {
            if (deg[i] & 1) {
                if (v1 == -1) v1 = i;
                else if (v2 == -1) v2 = i;
                else ok = false;
            }
        }
    }

    vector<int> getEulerPath() {
        for (int u = 0; v1 == -1 && u < n; u++)
            if (deg[u]) return getEulerPath(u, u);
        return getEulerPath(v1, v2);
    }

    vector<int> getEulerPath(int s, int e) {
        path.clear();
        if (!ok) return path;
        if (v1 == -1 && s != e) return path;
        if (v1 != -1 && !((v1 == s && v2 == e) || (v1 == e && v2 == s))) return path;

        stack<int> st;
        st.push(e);
        while (!st.empty()) {
            int v = st.top();
            if (G[v].empty()) {
                path.push_back(v), st.pop();
                continue;
            }
            int u = *G[v].begin();
            G[v].extract(u);
            G[u].extract(v);
            st.push(u);
        }

        for (int i = 0; i < n; ++i)
            if (!G[i].empty()) path.clear();


        return path;
    }
};

void testCase() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > G(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    EulerPath eulerPath(G);
    auto path = eulerPath.getEulerPath(1, 1);
    if (path.empty()) return void(cout << "IMPOSSIBLE" << endl);
    for (auto x: eulerPath.path) cout << x << ' ';
    cout << endl;
}
