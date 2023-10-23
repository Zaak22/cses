#include<bits/stdc++.h>
 
using namespace std;
 
#define ll long long
#define oo 1e18
#define endl '\n'
#define all(v) v.begin(),v.end()
 
#ifdef LOCAL
 
#include "debug.h"
 
#else
#define dd(x...)
#define ExeTime
#endif
int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};
 
const int N = 1e6 + 10, M = 1e2 + 10, mod = 1e9 + 7;
const double EPS = 1e-12, Pi = acos(-1);
 
void testCase();
 
int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
//    cin >> T;
    while (T--) testCase();
    ExeTime;
    return 0;
}
 
template<class T>
vector<int> z_algorithm(const vector<T> &s) {
    int n = s.size();
    if (n == 0) return {};
    vector<int> z(n, 0);
    for (int i = 1, j = 0; i < n; i++) {
        int &k = z[i];
        k = (j + z[j] <= i) ? 0 : min(j + z[j] - i, z[i - j]);
        while (i + k < n && s[k] == s[i + k]) k++;
        if (j + z[j] < i + z[i]) j = i;
    }
    return z;
}
 
vector<int> z_algorithm(const string &s) {
    int n = s.size();
    vector<int> s2(n);
    for (int i = 0; i < n; i++) s2[i] = s[i];
    return z_algorithm(s2);
}
 
vector<int> buildLps(const string &p) {
    int m = p.size();
    vector<int> lps(m);
    for (int i = 1, j = 0; i < m; i++)
        if (p[i] == p[j]) lps[i] = ++j;
        else if (j) j = lps[j - 1], i--;
    return lps;
}
 
void testCase() {
    string s;
    cin >> s;
    auto z = z_algorithm(s);
    auto pi = buildLps(s);
 
    for (auto x: z) cout << x << ' ';
    cout << endl;
 
    for (auto x: pi) cout << x << ' ';
    cout << endl;
 
}