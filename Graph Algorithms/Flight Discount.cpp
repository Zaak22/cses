#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
 
#define ll long long
#define oo 1e15
#define endl '\n'
#define all(v) v.begin(),v.end()
#define FASTIO ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
 
//#define ordered_set tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>
//#define ordered_multiset tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
//#define trie trie<string,null_type,trie_string_access_traits<>,pat_trie_tag,trie_prefix_search_node_update>
 
//using namespace __gnu_pbds;
using namespace std;
 
int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};
 
const ll N = 1e5 + 10, mod = 1e9 + 7;
vector<pair<ll, ll> > G[2][N];
vector<ll> Path;
ll n, m, dis[2][N];
 
void dijkstra(int t) {
    fill(dis[t], dis[t] + n + 1, oo);
    typedef tuple<ll, ll> T;
    priority_queue<T, vector<T>, greater<T> > q;
    ll d = 0, w, v, u = 1;
    if (t) u = n;
    dis[t][u] = d;
    q.push({dis[t][u], u});
    while (!q.empty()) {
        tie(d, u) = q.top();
        q.pop();
 
        if (d != dis[t][u]) continue;
 
        for (auto p: G[t][u]) {
            tie(v, w) = p;
            if (dis[t][u] + w < dis[t][v]) {
                dis[t][v] = dis[t][u] + w;
                q.push({dis[t][v], v});
            }
        }
    }
}
 
void testCase() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        G[0][u].emplace_back(v, w);
        G[1][v].emplace_back(u, w);
    }
 
    dijkstra(0);
    dijkstra(1);
 
    ll ans = oo;
    for (int u = 1; u <= n; u++) {
        for (auto p: G[0][u]) {
            ll v, w;
            tie(v, w) = p;
            ans = min(ans, dis[0][u] + w / 2 + dis[1][v]);
        }
    }
    cout << ans << endl;
}
 
int main() {
//    ::freopen("bla.in", "r", stdin);
    FASTIO
    int T = 1;
//    cin >> T;
    for (int i = 0; i < T; i++) {
        testCase();
    }
    return 0;
}