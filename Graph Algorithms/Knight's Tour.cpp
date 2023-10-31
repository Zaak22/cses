#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define oo 1e18
#define endl '\n'
#define all(v) v.begin(),v.end()

#ifdef LOCAL

#include "assets/debug.h"

#else
#define dd(x...)
#define ExeTime
#endif

void testCase();

//int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
//int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};
const int N = 2e5 + 10, M = 1e2 + 10, mod = 1e9 + 7;
const double EPS = 1e-12, PI = acos(-1);

void init() {}

int main() {
    init();
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
//    cin >> T;
    while (T--) testCase();
    ExeTime;
}

int dx[] = {1, 1, 2, 2, -1, -1, -2, -2};
int dy[] = {2, -2, 1, -1, 2, -2, 1, -1};
int ans[8][8];

bool valid(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

int n = 0;
void dfs(int x, int y, int cnt) {
    ans[x][y] = cnt;
    if (cnt == 64) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cout << ans[i][j] << ' ';
            }
            cout << endl;
        }
        exit(0);
    }
    vector<pair<int, pair<int, int> >> v;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (!valid(nx, ny)) continue;
        if (ans[nx][ny]) continue;
        int sum = 0;
        for (int j = 0; j < 8; j++) {
            int nxx = nx + dx[j];
            int nyy = ny + dy[j];
            if (!valid(nxx, nyy)) continue;
            if (ans[nxx][nyy]) continue;
            sum++;
        }
        if (sum >= 0) {
            v.push_back({sum, {nx, ny}});
        }
    }
    sort(all(v));
    for (auto [c, p]: v) {
        dfs(p.first, p.second, cnt + 1);
    }
    ans[x][y] = 0;
}

void testCase() {
    int x, y;
    cin >> y >> x;
    x--, y--;
    dfs(x, y, 1);
}
