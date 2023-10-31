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
int vis[N][N];
pair<int, int> par[N][N];
int ans;
 
void bfs(int i, int j) {
    queue<pair<pair<int, int>, int>> q;
    vis[i][j] = 0;
    q.push({{i, j}, 0});
    par[i][j] = {-1, -1};
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        i = p.first.first;
        j = p.first.second;
        int d = p.second;
 
        for (int k = 0; k < 4; k++) {
            int newi = i + dx[k];
            int newj = j + dy[k];
 
            if (newi < 0 || newi > n - 1) continue;
            if (newj < 0 || newj > m - 1) continue;
            if (vis[newi][newj] < 1e9) continue;
            if (a[newi][newj] == '#') continue;
 
            vis[newi][newj] = d + 1;
            par[newi][newj] = {i, j};
            q.push({{newi, newj}, d + 1});
        }
    }
 
}
 
string trace(int x, int y) {
    string s;
    while (par[x][y].first != -1) {
        int xx = par[x][y].first;
        int yy = par[x][y].second;
        if (xx < x) s += 'D';
        else if (xx > x) s += 'U';
        else if (yy > y) s += 'L';
        else if (yy < y) s += 'R';
        x = xx;
        y = yy;
    }
    reverse(all(s));
    return s;
}
 
void testCase() {
    cin >> n >> m;
    pair<int, int> st, en;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j < m; j++) {
            vis[i][j] = 1e9;
            if (a[i][j] == 'A') st = {i, j};
            if (a[i][j] == 'B') en = {i, j};
        }
    }
 
    bfs(st.first, st.second);
 
    if (vis[en.first][en.second] == 1e9) {
        cout << "NO" << endl;
        return;
    } else {
        cout << "YES" << endl;
        cout << vis[en.first][en.second] << endl;
    }
 
    cout << trace(en.first, en.second) << endl;
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