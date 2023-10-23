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
 
const int N = 1e6 + 10, mod = 998244353;
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
 
 
class DynamicHash {
public:
 
    static const int mod1 = 1e9 + 123, mod2 = 1e9 + 321;
    vector<ll> pw, inv_pw;
    ll n, base, mod, m;
    vector<ll> seg;
    string s;
 
    int inv(int i) {
        return i <= 1 ? i : mod - (mod / i) * inv(mod % i) % mod;
    }
 
    DynamicHash(string s, ll mod, int base = 1331) {
        this->s = s;
        this->mod = mod;
        this->base = base;
        this->n = s.size();
        seg.assign(4 * n, 0);
        pw.resize(n + 1);
        inv_pw.resize(n + 1);
        pw[0] = inv_pw[0] = 1;
        int inv = this->inv(base);
        for (int i = 1; i <= n; i++) {
            pw[i] = 1ll * pw[i - 1] * base % mod;
            inv_pw[i] = 1ll * inv * inv_pw[i - 1] % mod;
        }
        build(1, 1, n);
    }
 
    void build(int p, int L, int R) {
        if (L == R) {
            seg[p] = (s[L] * pw[L]) % mod;
            return;
        }
        int mid = (L + R) >> 1;
        build(p * 2, L, mid);
        build(p * 2 + 1, mid + 1, R);
        seg[p] = seg[p * 2] + seg[p * 2 + 1];
        if (seg[p] >= mod) seg[p] -= mod;
    }
 
    void update(int i, ll val, int p, int L, int R) {
        if (L > i || R < i) return;
        if (L >= i && R <= i) {
            seg[p] = (val * pw[i]) % mod;
            return;
        }
 
        int mid = (L + R) / 2;
        update(i, val, p * 2, L, mid);
        update(i, val, p * 2 + 1, mid + 1, R);
        seg[p] = seg[p * 2] + seg[p * 2 + 1];
        if (seg[p] >= mod) seg[p] -= mod;
    }
 
    int query(int i, int j, int p, int L, int R) {
        if (L > j || R < i) return 0;
        if (L >= i && R <= j) return seg[p] % mod;
 
        int mid = (L + R) / 2;
        int c1 = query(i, j, p * 2, L, mid) % mod;
        int c2 = query(i, j, p * 2 + 1, mid + 1, R) % mod;
        int ret = c1 + c2;
        if (ret >= mod) ret -= mod;
        return ret;
    }
 
    int get(int l, int r) {
        int ret = query(l, r, 1, 1, n);
        ret = 1ll * ret * inv_pw[l] % mod;
        return ret;
    }
};
 
void testCase() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    s = "#" + s + "#";
    string rev = s;
    reverse(all(rev));
 
    DynamicHash h1(s, DynamicHash::mod1);
    DynamicHash h2(rev, DynamicHash::mod1);
 
    while (m--) {
        int t;
        cin >> t;
        if (t == 1) {
            int a;
            char c;
            cin >> a >> c;
            h1.update(a, c, 1, 1, n + 2);
            h2.update(n - a + 1, c, 1, 1, n + 2);
        }
        if (t == 2) {
            int a, b;
            cin >> a >> b;
            auto q1 = h1.get(a, b);
            auto q2 = h2.get(n - b + 1, n - a + 1);
            if (q1 == q2) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
}