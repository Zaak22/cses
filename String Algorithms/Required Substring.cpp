#include<bits/stdc++.h>
 
using namespace std;
 
#define ll long long
#define oo 1e18
#define endl '\n'
#define all(v) v.begin(),v.end()
 
#ifdef LOCAL
 
#include "debug.h"
 
#else
#define debug(x...)
#define ExeTime
#endif
 
int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};
 
const int N = 1e3 + 10, M = 1e2 + 10, mod = 1e9 + 7;
const double EPS = 1e-12, Pi = acos(-1);
 
void testCase();
 
int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
//    cin >> T;
    for (int i = 0; i < T; i++) testCase();
    ExeTime;
    return 0;
}
 
vector<int> buildLps(string p) {
    int m = p.size();
    vector<int> lps(m);
    for (int i = 1, j = 0; i < m; i++) {
        if (p[i] == p[j]) lps[i] = ++j;
        else if (j) {
            j = lps[j - 1];
            i--;
        }
    }
    return lps;
}
 
vector<int> lps;
ll dp[N][M];
int n, m;
string s;
 
ll solve(int i, int match) {
    if (i == n) return match == m;
    auto &ret = dp[i][match];
    if (ret + 1) return ret;
    ret = 0;
    if (match == m) {
        ret = (26 * solve(i + 1, match)) % mod;
        return ret;
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        int cur = match;
        while (cur > 0 && c != s[cur]) {
            cur = lps[cur - 1];
        }
        ret += solve(i + 1, cur + (s[cur] == c));
        ret %= mod;
    }
 
    return ret;
}
 
void testCase() {
    cin >> n;
    cin >> s;
    m = s.size();
    lps = buildLps(s);
    memset(dp, -1, sizeof dp);
    cout << solve(0, 0) << endl;
}