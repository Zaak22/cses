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
pair<pair<int, int>, int> par[N][N];
int ans;
 
void bfs(vector<pair<int, int> > monsters, pair<int, int> st) {
    queue<pair<pair<int, int>, int>> q;
 
    for (auto p: monsters) {
        q.push({p, 0});
        vis[p.first][p.second] = 0;
        par[p.first][p.second] = {{-1, -1}, 1};
    }
 
    q.push({st, 0});
    vis[st.first][st.second] = 0;
    par[st.first][st.second] = {{-1, -1}, 0};
 
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        int i = p.first.first;
        int j = p.first.second;
        int d = p.second;
 
        for (int k = 0; k < 4; k++) {
            int newi = i + dx[k];
            int newj = j + dy[k];
 
            if (newi < 0 || newi > n - 1) continue;
            if (newj < 0 || newj > m - 1) continue;
            if (vis[newi][newj] < 1e9) continue;
            if (a[newi][newj] == '#') continue;
 
            vis[newi][newj] = d + 1;
            par[newi][newj] = {{i, j}, par[i][j].second};
            q.push({{newi, newj}, d + 1});
        }
    }
 
}
 
string trace(int x, int y) {
    string s;
    while (par[x][y].first.first != -1) {
        int xx = par[x][y].first.first;
        int yy = par[x][y].first.second;
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
    pair<int, int> st;
    vector<pair<int, int> > starts, monsters;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j < m; j++) {
            vis[i][j] = 1e9;
            if (a[i][j] == 'A') st = {i, j};
            if (a[i][j] == 'M') monsters.push_back({i, j});
        }
    }
 
    bfs(monsters, st);
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i == 0 || j == 0 || i == n - 1 || j == m - 1) && (a[i][j] == '.' || a[i][j] == 'A')) {
                if(par[i][j].first.first != 0 && par[i][j].second == 0){
                    cout << "YES" << endl;
                    string s = trace(i,j);
                    cout << s.size() << endl;
                    cout << s << endl;
                    return;
                }
            }
        }
    }
 
    cout << "NO" << endl;
}
 
int main() {
//    ::freopen("bla.in", "r", stdin);
//    FASTIO
    int T = 1;
//    cin >> T;
    for (int i = 0; i < T; i++) {
        testCase();
    }
    return 0;
}