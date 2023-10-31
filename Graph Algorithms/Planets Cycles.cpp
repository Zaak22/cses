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

int n;
vector<int> G[N], RG[N];
int vis[N], cycPos[N], c[N], dis[N], cycId[N], sz[N], id = 1;
stack<int> st;

void dfs(int u) {
    st.push(u);
    vis[u] = 1;
    for (int v: G[u]) {
        if (vis[v] == 0) dfs(v);
        else if (vis[v] == 1) {
            auto temp = st;
            sz[id] = 1;
            while (!st.empty() && st.top() != v) {
                cycPos[st.top()] = sz[id]++;
                cycId[st.top()] = id;
                st.pop();
            }
            cycPos[v] = sz[id];
            cycId[v] = id++;
            st = temp;
        }
    }
    st.pop();
    vis[u] = 2;
}

void bfs(int u, int col) {
    queue<int> q;
    q.push(u);
    dis[u] = 0;
    while (!q.empty()) {
        u = q.front(), q.pop();
        c[u] = col;
        for (int v: RG[u]) {
            if (vis[v] || cycPos[v])continue;
            q.push(v);
            vis[v] = 1;
            dis[v] = dis[u] + 1;
        }
    }
}

void testCase() {
    cin >> n;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        G[i].push_back(a[i]);
        RG[a[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        dfs(i);
    }
    for (int i = 1; i <= n; i++) vis[i] = 0;
    for (int i = 1; i <= n; i++) if (cycPos[i]) bfs(i, i);
    for (int i = 1; i <= n; i++) {
        int ans = dis[i] + sz[cycId[c[i]]];
        cout << ans << ' ';
    }
    cout << endl;
}
