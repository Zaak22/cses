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

int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};
const int N = 1e5 + 10, M = 1e2 + 10, mod = 1e9 + 7;
const double EPS = 1e-12, PI = acos(-1);

void init() {}

void testCase();

int main() {
    init();
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
//    cin >> T;
    for (int i = 0; i < T; i++) testCase();
    ExeTime;
}

struct FlowEdge {
    int v, u;
    ll cap, flow = 0;
    bool cutEdge = false;

    FlowEdge(int v, int u, ll cap) : v(v), u(u), cap(cap) {}
};

struct MaxFlow {
    vector<FlowEdge> E; // edges
    vector<vector<int>> G;
    int n, m = 0, s, t;
    vector<int> dis, ptr;

    MaxFlow(int n, int s, int t) : n(n), s(s), t(t) {
        G.resize(n);
        dis.resize(n);
        ptr.resize(n);
    }

    void addEdge(int v, int u, ll cap) {
        E.push_back({v, u, cap}), G[v].push_back(m++);
        E.push_back({u, v, 0ll}), G[u].push_back(m++);
    }

    bool havePath() {
        fill(all(dis), -1);
        queue<int> q;
        dis[s] = 0, q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id: G[v]) {
                int u = E[id].u;
                ll cur = E[id].cap - E[id].flow;
                if (cur <= 0 || dis[u] != -1) continue;
                dis[u] = dis[v] + 1, q.push(u);
            }
        }
        return dis[t] != -1;
    }

    ll getMinOnPath(int v, ll pushed = oo) {
        if (pushed == 0) return 0;
        if (v == t) return pushed;
        for (int &cid = ptr[v]; cid < (int) G[v].size(); cid++) {
            int id = G[v][cid], u = E[id].u;
            ll cur = E[id].cap - E[id].flow;
            if (dis[v] + 1 != dis[u] || cur < 1) continue;
            ll tr = getMinOnPath(u, min(cur, pushed));
            if (tr == 0) continue;
            E[id].flow += tr, E[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    ll flow() {
        ll f = 0;
        while (true) {
            if (!havePath()) break;
            fill(all(ptr), 0);
            while (ll pushed = getMinOnPath(s)) f += pushed;
        }
        markFlowEdges();
        return f;
    }

    void markFlowEdges() {
        for (auto &edge: E)
            edge.cutEdge = (dis[edge.u] == -1) ^ (dis[edge.v] == -1);
    }

    vector<pair<int, int> > minCut() {
        set<pair<int, int> > ans;
        for (auto edge: E)
            if (edge.cutEdge) {
                if (edge.u < edge.v) swap(edge.u, edge.v);
                ans.emplace(edge.v, edge.u);
            }
        return vector<pair<int, int> >(all(ans));
    }

    vector<pair<int, int> > bipartiteMatching() {
        set<pair<int, int> > ans;
        for (auto edge: E)
            if (edge.flow > 0) {
                if (edge.u < edge.v) swap(edge.u, edge.v);
                ans.emplace(edge.v, edge.u);
            }
        return vector<pair<int, int> >(all(ans));
    }

    vector<vector<int> > flowPaths() {
        vector<vector<int> > g(n + 1);
        for (auto edge: E)
            if (edge.flow > 0) g[edge.v].push_back(edge.u);

        vector<vector<int> > paths;
        vector<vector<bool> > vis(n + 1, vector<bool>(n + 1, false));
        for (int x: g[s]) {
            vector<int> cur(1, s);
            function<bool(int, int)> dfs = [&](int u, int p) {
                cur.push_back(u);
                vis[u][p] = 1;
                vis[p][u] = 1;
                if (u == t) {
                    paths.push_back(cur);
                    cur.pop_back();
                    return true;
                }
                bool ret = false;
                for (auto v: g[u]) {
                    if (vis[v][u]) continue;
                    if (dfs(v, u)) {
                        ret = true;
                        break;
                    }
                }
                cur.pop_back();
                return ret;
            };
            dfs(x, 1);

            return paths;
        }
    }
};

void testCase() {
    int n, m, k;
    cin >> n >> m >> k;
    MaxFlow flow(n + m + 2, 0, n + m + 1);
    for (int i = 1; i <= n; i++) flow.addEdge(0, i, 1);
    for (int i = n + 1; i <= n + m; i++) flow.addEdge(i, n + m + 1, 1);
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> v >> u;
        flow.addEdge(v, u + n, 1);
    }

    cout << flow.flow() << endl;
    for (auto [u, v]: flow.bipartiteMatching()) {
        if (u == 0 || v == 0 || u == n + m + 1 || v == n + m + 1) continue;
        if (u > n) u -= n;
        if (v > n) v -= n;
        cout << u << ' ' << v << endl;
    }
}
