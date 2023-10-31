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
    vector<int> path, in, out, deg;
    int n, v1, v2; // v1/v2: first/second node with odd degree
    bool ok, isDirected; // could have euler tour

    EulerPath(vector<vector<int>> G, bool isDirected = false) : n(G.size()), isDirected(isDirected) {
        this->G.assign(n, multiset<int>());
        for (int i = 0; i < n; i++)
            for (auto v: G[i]) this->G[i].insert(v);
        v1 = -1, v2 = -1;
        ok = true;
        if (isDirected) {
            in.resize(n), out.resize(n);
            for (int i = 0; i < n; ++i)
                for (auto v: this->G[i]) in[v]++, out[i]++;
            for (int i = 0; i < n; ++i) {
                if (in[i] != out[i]) {
                    if (in[i] == out[i] - 1 && v1 == -1) v1 = i;
                    else if (in[i] == out[i] + 1 && v2 == -1) v2 = i;
                    else ok = false;
                }
            }
        } else {
            deg.resize(n);
            for (int i = 0; i < n; ++i) deg[i] = this->G[i].size();
            for (int i = 0; i < n; ++i) {
                if (deg[i] & 1) {
                    if (v1 == -1) v1 = i;
                    else if (v2 == -1) v2 = i;
                    else ok = false;
                }
            }
        }
    }

    vector<int> getEulerPath() {
        for (int u = 0; v1 == -1 && u < n; u++)
            if ((!isDirected && deg[u]) || (isDirected && out[u]))
                return getEulerPath(u, u);
        return getEulerPath(v1, v2);
    }

    vector<int> getEulerPath(int s, int e) {
        path.clear();
        if (!ok) return path;
        if (v1 == -1 && s != e) return path;
        if (v1 != -1 && !((v1 == s && v2 == e) ||
                          (!isDirected && v1 == e && v2 == s)))
            return path;
        stack<int> st;
        st.push(s);
        while (!st.empty()) {
            int v = st.top();
            if (G[v].empty()) {
                path.push_back(v), st.pop();
                continue;
            }
            int u = *G[v].begin();
            G[v].extract(u);
            if (!isDirected) G[u].extract(v);
            st.push(u);
        }
        for (int i = 0; i < n; ++i)
            if (!G[i].empty()) path.clear();
        reverse(all(path));
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
    }

    EulerPath eulerPath(G, true);

    auto path = eulerPath.getEulerPath(1, n);

    if (path.empty()) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }

    for (auto x: path) cout << x << ' ';
    cout << endl;
}
