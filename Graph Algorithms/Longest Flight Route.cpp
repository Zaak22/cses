#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
 
#define ll long long
#define oo 1e18
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
 
vector<pair<ll, ll> > G[N];
vector<ll> Path;
ll n, m, dis[N], par[N];
 
void dijkstra(int u) {
    fill(dis, dis + n + 1, oo);
    fill(par, par + n + 1, -1);
    typedef pair<ll, ll> T;
    stack<T> q;
    ll d = 0, w, v;
    dis[u] = d;
    q.push({dis[u], u});
    while (!q.empty()) {
        tie(d, u) = q.top();
        q.pop();
 
        if (d != dis[u]) continue;
 
        for (auto p: G[u]) {
            tie(v, w) = p;
 
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                par[v] = u;
                q.emplace(dis[v], v);
            }
        }
    }
}
 
void Trace(int s, int t) {
    Path.push_back(t);
    if (s == t) return;
    while (t != -1 && t != s) {
        t = par[t];
        Path.push_back(t);
    }
    reverse(all(Path));
    if (t == -1)Path.clear();
}
 
void testCase() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].emplace_back(v, -1);
    }
    dijkstra(1);
    if (dis[n] == oo) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
 
    Trace(1, n);
 
    cout << Path.size() << endl;
    for(auto x:Path) cout << x << ' ';
    cout << endl;
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