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
 
class SuffixArray {
public:
    string s;
    int n, log_n;
    const int alphabet = 124;
    // p = position, g = group, sa = suffix array
    vector<int> p, new_g, cnt, new_p, sa;
    vector<vector<int> > g;
 
    SuffixArray(string s) {
        this->s = s + "$";
        n = this->s.size();
        log_n = log2(n);
        p.resize(n);
        g.resize(log_n + 2, vector<int>(n));
        cnt.resize(max(n, alphabet));
        new_g.resize(n);
        new_p.resize(n);
        sa = sort_cyclic_shifts();
        //sorted_shifts.erase(sorted_shifts.begin());
    }
 
    vector<int> sort_cyclic_shifts() {
        for (int i = 0; i < n; i++) cnt[s[i]]++;
        for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
        g[0][p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; i++) {
            classes += (s[p[i]] != s[p[i - 1]]);
            g[0][p[i]] = classes - 1;
        }
        for (int h = 0; h <= log_n; ++h) {
            for (int i = 0; i < n; i++) {
                new_p[i] = p[i] - (1 << h);
                if (new_p[i] < 0) new_p[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < n; i++) cnt[g[h][new_p[i]]]++;
            for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--) p[--cnt[g[h][new_p[i]]]] = new_p[i];
            new_g[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; i++) {
                int stpI = (p[i] + (1 << h)) % n;
                int stpI1 = (p[i - 1] + (1 << h)) % n;
                pair<int, int> cur = {g[h][p[i]], g[h][stpI]};
                pair<int, int> prev = {g[h][p[i - 1]], g[h][stpI1]};
                classes += (cur != prev);
                new_g[p[i]] = classes - 1;
            }
            g[h + 1].swap(new_g);
        }
        return p;
    }
 
    int compare(int i, int j, int l) {
        int k = log_n;
        while ((1 << k) > l) k--;
        int nextI = (i + l - (1 << k)) % (n - 1);
        int nextJ = (j + l - (1 << k)) % (n - 1);
        pair<int, int> a = {g[k][i], g[k][nextI]};
        pair<int, int> b = {g[k][j], g[k][nextJ]};
        return (a == b ? 0 : a < b ? -1 : 1);
    }
 
    int lcp(int i, int j) {
        int ans = 0;
        for (int k = log_n, q = 1 << k; k >= 0; k--, q >>= 1)
            if (g[k][i] == g[k][j]) ans += q, i += q, j += q;
        return ans;
    }
 
    vector<int> lcp_construction() {
        vector<int> rank(n, 0), lcp(n - 1, 0);
        for (int i = 0; i < n; i++) rank[p[i]] = i;
        for (int i = 0, k = 0; i < n; i++, k -= (k != 0)) {
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = p[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            lcp[rank[i]] = k;
        }
        return lcp;
    }
 
    bool check(int mid, string &t, bool greater = true) {
        int i = 0, j = sa[mid], m = (int) t.size();
        while (i < m && j < n) {
            if (t[i] > s[j]) return !greater;
            if (t[i] < s[j]) return greater;
            i++, j++;
        }
        return greater;
    }
 
    int lower_bound(string t) { // O(min(n,m)*log(n))
        int l = 0, r = n - 1, ans = n - 1, mid;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (check(mid, t)) r = mid - 1, ans = mid;
            else l = mid + 1;
        }
        return ans;
    }
 
    int upper_bound(string t) { // O(min(n,t,size())*log(n))
        int l = 0, r = n - 1, ans = n - 1, mid;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (check(mid, t, 0)) r = mid - 1, ans = mid;
            else l = mid + 1;
        }
        return ans;
    }
};
 
namespace sa_apps {
    string lcs(string s, string t) { // longest common substring
        SuffixArray sa(s + "#" + t);
        auto lcp = sa.lcp_construction();
        int m = s.size(), mx = 0, ind = 0, n = sa.n - 1;
        string lcs;
        for (int i = 0; i < n; i++)
            if ((sa.p[i] < m && sa.p[i + 1] > m) || (sa.p[i] > m && sa.p[i + 1] < m))
                if (lcp[i] > mx) mx = lcp[i], ind = i;
        for (int i = sa.p[ind]; i < sa.p[ind] + mx; i++) lcs += s[i];
        return lcs;
    }
 
    ll distinct_substr_num(string s) { // returns number of distinct substrings
        SuffixArray sa(s);
        auto lcp = sa.lcp_construction();
        ll n = (int) s.size();
        ll sum = sa.p[n];
        for (int i = 0; i < n; i++) sum += sa.p[i] + lcp[i];
        return n * (n + 1) - sum;
    }
}
 
void testCase() {
    using namespace sa_apps;
    string s;
    cin >> s;
    cout << distinct_substr_num(s) << endl;
}