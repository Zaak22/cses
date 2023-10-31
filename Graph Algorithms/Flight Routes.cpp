#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
 
#define ll long long
#define oo (1LL << 60)
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
 
string yes(bool ok) {
    return ok ? "YES" : "NO";
}
 
const double eps = 1e-9;
const ll N = 1e5 + 10, mod = 1e9 + 7;
vector<pair<ll, ll> > G[N];
ll n, m, k;
priority_queue<ll> dis[N];
 
void dijkstra(int u) {
    typedef pair<ll, ll> T;
    priority_queue<T, vector<T>, greater<T> > q;
    ll d = 0, w, v;
    dis[u].push(d);
    q.push({d, u});
    while (!q.empty()) {
        tie(d, u) = q.top();
        q.pop();
 
        if (!dis[u].empty() && d > dis[u].top()) continue;
 
        for (auto p: G[u]) {
            tie(v, w) = p;
 
            if (dis[v].size() < k || d + w < dis[v].top()) {
                if (dis[v].size() >= k) dis[v].pop();
                dis[v].push(d + w);
                q.emplace(d + w, v);
            }
        }
    }
}
 
void testCase() {
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
    }
 
    dijkstra(1);
 
    vector<ll> ans;
    while (!dis[n].empty()) {
        ans.push_back(dis[n].top());
        dis[n].pop();
    }
    reverse(all(ans));
 
    for (auto x: ans) cout << x << ' ';
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