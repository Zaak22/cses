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
int vis[N];
bool ok = false;
vector<int> ans;
stack<int> st;
 
void dfs(int u) {
    vis[u] = 1;
    st.push(u);
    for (auto v: G[u]) {
        if (vis[v] == 0) dfs(v);
        else if (vis[v] == 1 && !ok) {
            auto temp = st;
            ans.push_back(v);
            while (temp.top() != v) {
                ans.push_back(temp.top());
                temp.pop();
            }
            ans.push_back(v);
            ok = true;
        }
    }
    vis[u] = 2;
    st.pop();
}
 
 
void testCase() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) dfs(i);
    }
    if (!ok) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    reverse(all(ans));
    cout << ans.size() << endl;
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