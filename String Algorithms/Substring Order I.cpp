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
 
struct SuffixAutomaton {
    struct state {
        int len = 0, link = -1, cnt = 1;
        bool cloned = 0, terminal = 0;
        map<int, int> G;
    };
 
    vector<state> st;
    int sz, last;
 
    SuffixAutomaton(const string &s) {
        initialize();
        for (char c: s) extend(c);
        markTerminals();
    }
 
    void markTerminals() {
        for (auto &x: st) x.terminal = 0;
        for (int p = last; p > 0; p = st[p].link)
            st[p].terminal = 1;
    }
 
    void initialize() {
        st.clear(), st.push_back({});
        sz = 1, last = 0;
    }
 
    void extend(int c) {
        st.push_back({});
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && !st[p].G.count(c))
            st[p].G[c] = cur, p = st[p].link;
        if (p == -1) st[cur].link = 0;
        else {
            int q = st[p].G[c];
            if (st[p].len + 1 == st[q].len) st[cur].link = q;
            else {
                st.push_back({});
                state &x = st[sz];
                x.len = st[p].len + 1, x.G = st[q].G;
                x.link = st[q].link, x.cloned = 1;
                st[cur].cnt++;
                st[q].cnt++;
                while (p != -1 && st[p].G[c] == q)
                    st[p].G[c] = sz, p = st[p].link;
                st[q].link = st[cur].link = sz++;
            }
        }
        last = cur;
    }
 
    bool isASubstring(const string &t) {
        int u = 0;
        for (char c: t) {
            if (!st[u].G.count(c)) return 0;
            u = st[u].G[c];
        }
        return 1;
    }
 
    ll numDiffSubstrings() {
        ll ans = 0;
        for (int i = 1; i < sz; i++)
            ans += st[i].len - st[st[i].link].len;
        return ans;
    }
 
    ll totalLenDiffSubstrings() {
        ll ans = 0;
        for (int i = 1; i < sz; i++) {
            int shortest = st[st[i].link].len + 1;
            int longest = st[i].len;
            int num_strings = longest - shortest + 1;
            ans += 1LL * num_strings * (longest + shortest) / 2;
        }
        return ans;
    }
};
 
namespace sam_apps {
    string kthSubstring(const string &s, ll k) {
        SuffixAutomaton sam(s);
        vector<ll> dp(sam.sz, 0);
        auto st = sam.st;
        function<void(int)> dfs = [&](int u) {
            if (dp[u]) return;
            dp[u] = 1;
            for (auto x: st[u].G)
                dfs(x.second), dp[u] += dp[x.second];
            return;
        };
        dfs(0);
        int u = 0;
        string ret;
        while (k) {
            if (st[u].G.empty()) break;
            for (auto x: st[u].G) {
                if (dp[x.second] < k) k -= dp[x.second];
                else {
                    ret += x.first, u = x.second, k--;
                    break;
                }
            }
        }
        return ret;
    }
}
 
 
void testCase() {
    string s;
    ll k;
    cin >> s >> k;
    cout << sam_apps::kthSubstring(s, k) << endl;
}