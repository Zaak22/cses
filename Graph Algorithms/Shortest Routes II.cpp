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
 
const ll N = 5e2 + 10, mod = 1e9 + 7;
int n, m;
ll dis[N][N];
 
void floydWarshall() {
    for (int k = 1; k <= n; k++) {
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                dis[u][v] = min(dis[u][v], dis[u][k] + dis[k][v]);
            }
        }
    }
}
 
void testCase() {
    int q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j) dis[i][j] = oo;
        }
    }
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        dis[u][v] = min(dis[u][v], w);
        dis[v][u] = min(dis[v][u], w);
    }
 
    floydWarshall();
 
    while (q--) {
        int u, v;
        cin >> u >> v;
        ll ans = min(dis[u][v], dis[v][u]);
        if (ans == oo) {
            cout << -1 << endl;
            continue;
        }
 
        cout << ans << endl;
    }
 
 
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