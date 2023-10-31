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
 
vector<vector<int> > G;
vector<int> vis;
 
bool dfs(int v, vector<int> &ret) {
    vis[v] = 1;
    bool ok = 1;
    for (auto u: G[v]) {
        if (vis[u] == 1)return 0;
        if (!vis[u]) ok &= dfs(u, ret);
    }
    vis[v] = 2;
    ret.push_back(v);
    return ok;
}
 
vector<int> TopologicalSort(vector<bool> start) {
    vector<int> ret;
    bool ok = 1;
    for (size_t i = 1; i < start.size(); i++)
        if (start[i] && !vis[i]) ok &= dfs(i, ret);
    reverse(ret.begin(), ret.end());
    return (ok && ret.size() == start.size()-1 ? ret : vector<int>());
}
 
 
void testCase() {
    int n, m;
    cin >> n >> m;
    G.assign(n + 1, vector<int>());
    vis.assign(n + 1, 0);
    vector<bool> start(n + 1, true);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        start[v] = false;
    }
    vector<int> ans = TopologicalSort(start);
    if (ans.empty()) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    for (auto x: ans)cout << x << ' ';
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