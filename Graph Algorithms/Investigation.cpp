#include<bits/stdc++.h>
//#include <ext/push_back_ds/assoc_container.hpp>
 
#define ll long long
#define oo 1e18
#define endl '\n'
#define all(v) v.begin(),v.end()
#define FASTIO ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
 
//#define ordered_set tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>
//#define ordered_multiset tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
//#define trie trie<string,null_type,trie_string_access_traits<>,pat_trie_tag,trie_prefix_search_node_update>
 
//using namespace __gnu_push_backds;
using namespace std;
 
int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};
 
const int N = 1e5 + 10, mod = 1e9 + 7;
const double EPS = 1e-9;
int n, m, in[N];
vector<pair<int, int> > G[N], R[N];
ll dis[2][N];
 
ll dijkstra(int st, int en, int t) {
    fill(dis[t], dis[t] + n + 1, oo);
    typedef pair<ll, ll> T;
    priority_queue<T, vector<T>, greater<T> > q;
    ll d = 0, w, v, u = st;
    dis[t][u] = d;
    q.push({dis[t][u], u});
    while (!q.empty()) {
        tie(d, u) = q.top();
        q.pop();
 
        if (d != dis[t][u]) continue;
 
        for (auto p: G[u]) {
            tie(v, w) = p;
 
            if (dis[t][u] + w < dis[t][v]) {
                dis[t][v] = dis[t][u] + w;
                q.emplace(dis[t][v], v);
            }
        }
    }
    return dis[t][en];
}
 
ll numberOfPaths(int st, int en) {
    vector<ll> dp(n + 1);
    dp[st] = 1;
 
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
 
        for (auto v: G[u]) {
            in[v.first]--;
            if (in[v.first] == 0) {
                q.push(v.first);
            }
        }
 
        for (auto v: R[u]) {
            dp[u] += dp[v.first];
            dp[u] %= mod;
        }
    }
    return dp[en];
}
 
ll shortestPath(int st, int en, int t) {
    vector<bool> v(n + 1, false);
    vector<ll> ans(n + 1, 0);
    fill(dis[t], dis[t] + n + 1, oo);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
 
    pq.push({dis[t][st] = 0, st});
    while (!pq.empty()) {
        int vert = pq.top().second;
        pq.pop();
 
        if (v[vert]) continue;
        v[vert] = true;
        for (auto p: G[vert]) {
            ll cost = p.second;
            ll next = p.first;
            ll alt = cost + dis[t][vert];
 
            if (alt == dis[t][next]) {
                ans[next] = min(ans[next], ans[vert] + 1);
            } else if (alt < dis[t][next]) {
                ans[next] = ans[vert] + 1;
                pq.push({dis[t][next] = alt, next});
            }
        }
    }
    return ans[en];
}
 
ll longestPath(int st, int en, int t) {
    vector<bool> v(n + 1, false);
    vector<ll> ans(n + 1, 0);
    fill(dis[t], dis[t] + n + 1, oo);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
 
    pq.push({dis[t][st] = 0, st});
    while (!pq.empty()) {
        int vert = pq.top().second;
        pq.pop();
 
        if (v[vert]) continue;
        v[vert] = true;
        for (auto p: G[vert]) {
            ll cost = p.second;
            ll next = p.first;
            ll alt = cost + dis[t][vert];
 
            if (alt == dis[t][next]) {
                ans[next] = max(ans[next], ans[vert] + 1);
            } else if (alt < dis[t][next]) {
                ans[next] = ans[vert] + 1;
                pq.push({dis[t][next] = alt, next});
            }
        }
    }
    return ans[en];
}
 
void testCase() {
    cin >> n >> m;
    vector<tuple<int, int, int> > edges, newEdges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
        G[u].push_back({v, w});
    }
 
    cout << dijkstra(1, n, 0) << ' ';
 
    for (int i = 1; i <= n; i++) G[i].clear();
 
    for (auto edge: edges) {
        int u, v, w;
        tie(u, v, w) = edge;
        G[v].push_back({u, w});
    }
 
    dijkstra(n, 1, 1);
 
    for (int i = 1; i <= n; i++) G[i].clear();
 
    for (auto edge: edges) {
        int u, v, w;
        tie(u, v, w) = edge;
        if (dis[0][u] + dis[1][v] + w == dis[0][n]) {
            newEdges.push_back(edge);
            G[u].push_back({v, w});
            R[v].push_back({u, w});
            in[v]++;
        }
    }
 
    cout << numberOfPaths(1, n) << ' ';
 
    cout << shortestPath(1, n, 0) << ' ';
 
    cout << longestPath(1, n, 0) << endl;
 
 
}
 
int main() {
    FASTIO
//    ::freopen("../test.txt", "r", stdin);
    int T = 1;
//    cin >> T;
    for (int i = 0; i < T; i++) {
        testCase();
    }
    return 0;
}