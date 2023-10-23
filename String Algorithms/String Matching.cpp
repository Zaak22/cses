#include<bits/stdc++.h>
 
#pragma GCC optimize("Ofast,O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
 
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
 
class Hash {
    vector<int> p, ip, pr;
    int n, b, m;
 
    int inv(int i) {
        return i <= 1 ? i : m - 1ll * (m / i) * inv(m % i) % m;
    }
 
public:
    static const int mod1 = 1e9 + 123, mod2 = 1e9 + 321;
 
    Hash(const string &s, int _mod, int _b = 1331) {
        m = _mod, b = _b, n = s.size();
        pr.resize(n + 1);
        p.resize(n);
        ip.resize(n);
        p[0] = ip[0] = 1;
        for (int i = 1, ib = inv(b); i < n; i++) {
            p[i] = 1ll * p[i - 1] * b % m;
            ip[i] = 1ll * ib * ip[i - 1] % m;
        }
        for (int i = 0; i < n; i++)
            pr[i + 1] = (pr[i] + 1ll * s[i] * p[i] % m) % m;
    }
 
    int query(int pos, int len) {
        int ret = (pr[pos + len] - pr[pos]) % m;
        if (ret < 0) ret += m;
        return 1ll * ret * ip[pos] % m;
    }
};
 
 
void testCase() {
    string s, p;
    cin >> s >> p;
    int n = s.size(), m = p.size(), ans = 0;
    Hash hs(s, Hash::mod1);
    int hp = Hash(p, Hash::mod1).query(0, m);
    for (int i = 0; i + m - 1 < n; i++)
        ans += hs.query(i, m) == hp;
    cout << ans << endl;
}