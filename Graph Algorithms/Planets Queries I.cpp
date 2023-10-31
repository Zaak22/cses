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
 
int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};
const int N = 1e6 + 10, M = 1e2 + 10, mod = 998244353;
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
 
 
#define MAX  '>'
#define MIN '<'
#define SUM '+'
 
template<typename T, char TYPE = MAX>
class SparseTable {
private:
    int N, K;
    vector<vector<T>> st;
    vector<ll> po;
 
public:
    SparseTable(vector<T> a) {
        N = a.size();
        K = 32;
        po.resize(K + 1, 1);
        st.resize(K + 1, a);
        for (int i = 1; i <= K; i++) po[i] = po[i - 1] << 1;
        for (int i = 1; i <= K; i++)
            for (int j = 0; j < N; j++)
                st[i][j] = st[i - 1][st[i - 1][j]];
    }
 
    T query(int x, int k) {
        int cur = x;
        for (int i = K; i >= 0; i--) {
            if (po[i] <= k) {
                k -= po[i];
                cur = st[i][cur];
            }
        }
        return cur;
    }
};
 
void testCase() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    SparseTable<ll> st(a);
    while (q--) {
        int x, k;
        cin >> x >> k;
        cout << st.query(x, k) << endl;
    }
}