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
int n, m;
vector<int> G[N];
bool vis[N];
 
void dfs(int u) {
    vis[u] = true;
    for (auto v: G[u]) {
        if (vis[v]) continue;
        dfs(v);
    }
}
 
void testCase() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vector<int> pars;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            pars.push_back(i);
            dfs(i);
        }
    }
    cout << pars.size() - 1 << endl;
    for (int i = 1; i < pars.size(); i++) {
        cout << pars[i - 1] << ' ' << pars[i] << endl;
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