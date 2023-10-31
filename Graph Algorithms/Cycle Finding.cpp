#include<bits/stdc++.h>
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
 
const ll N = 3e3 + 10, mod = 1e9 + 7;
vector<tuple<int, int, ll>> edges;
ll dis[N], par[N];
 
void testCase() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        edges.push_back(tie(u, v, w));
    }
    fill(dis, dis + n + 1, oo);
    int cycle = -1;
    dis[1] = 0;
    for (int i = 0; i < n; i++) {
        cycle = -1;
        for (auto edge: edges) {
            ll u, v, w;
            tie(u, v, w) = edge;
            if (dis[u] + w < dis[v]) {
                cycle = v;
                dis[v] = max(-oo, dis[u] + w);
                par[v] = u;
            }
        }
    }
 
    if (cycle == -1) {
        cout << "NO" << endl;
        return;
    }
 
    cout << "YES" << endl;
    int y = cycle;
    for (int i = 0; i < n; ++i)
        y = par[y];
 
    vector<int> path;
    for (int cur = y;; cur = par[cur]) {
        path.push_back(cur);
        if (cur == y && path.size() > 1)
            break;
    }
    reverse(path.begin(), path.end());
    for (auto v: path) cout << v << ' ';
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