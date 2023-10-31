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
 
const ll N = 1e3 + 10, mod = 1e9 + 7;
int n, m;
string a[N];
bool vis[N][N];
 
void dfs(int i, int j) {
    vis[i][j] = 1;
    for (int k = 0; k < 4; k++) {
        int newi = i + dx[k];
        int newj = j + dy[k];
 
        if (newi < 0 || newi > n - 1) continue;
        if (newj < 0 || newj > m - 1) continue;
        if (vis[newi][newj]) continue;
        if (a[newi][newj] == '#') continue;
 
        dfs(newi, newj);
    }
}
 
void testCase() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '#' || vis[i][j]) continue;
            dfs(i, j);
            ans++;
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