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
 
const ll N = 3e3 + 10, mod = 1e9 + 7;
vector<int> G[2][N];
vector<tuple<int, int, ll>> edges;
bool vis[2][N];
ll dis[N];
 
void dfs(int u, bool t) {
    vis[t][u] = true;
    for (auto v: G[t][u]) {
        if (!vis[t][v]) dfs(v, t);
    }
}
 
void testCase() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        G[0][u].push_back(v);
        G[1][v].push_back(u);
        edges.push_back(tie(u, v, w));
    }
    dfs(1, 0);
    dfs(n, 1);
    fill(dis, dis + n + 1, -oo);
    bool cycle;
    dis[1] = 0;
    for (int i = 0; i < n; i++) {
        cycle = false;
        for (auto edge: edges) {
            ll u, v, w;
            tie(u, v, w) = edge;
            if (vis[0][u] && vis[1][v] && dis[u] + w > dis[v]) {
                cycle = true;
                dis[v] = dis[u] + w;
            }
        }
    }
 
    if (cycle) {
        cout << -1 << endl;
        return;
    }
 
    cout << dis[n] << endl;
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