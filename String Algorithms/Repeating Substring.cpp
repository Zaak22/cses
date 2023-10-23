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
 
const int N = 1e3 + 10, M = 1e2 + 10, mod = 1e9 + 7;
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
 
class SuffixArray {
public:
    string s;
    int n, log_n;
    const int alphabet = 256;
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
            while (i + k < n && j + k < n && s[i + k] == s[j + k] && s[i + k] != '#') k++;
            lcp[rank[i]] = k;
        }
        return lcp;
    }
 
    bool check(int mid, const string &t, bool greater = true) {
        int i = 0, j = sa[mid], m = (int) t.size();
        while (i < m && j < n) {
            if (t[i] > s[j]) return !greater;
            if (t[i] < s[j]) return greater;
            i++, j++;
        }
        return greater;
    }
 
    int lower_bound(const string &t) { // O(min(n,m)*log(n))
        int l = 0, r = n - 1, ans = n - 1, mid;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (check(mid, t)) r = mid - 1, ans = mid;
            else l = mid + 1;
        }
        return ans;
    }
 
    int upper_bound(const string &t) { // O(min(n,t,size())*log(n))
        int l = 0, r = n - 1, ans = n - 1, mid;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (check(mid, t, 0)) r = mid - 1, ans = mid;
            else l = mid + 1;
        }
        return ans;
    }
 
    bool exists_as_substr(const string t) {
        int j = sa[lower_bound(t)];
        for (int i = 0; i < (int) t.size(); i++, j++) {
            if (j >= n - 1) return false;
            if (t[i] != s[j]) return false;
        }
        return true;
    }
};
 
namespace sa_apps {
    vector<string> lcs(vector<string> s) { // longest common substring
        int k = s.size();
        string concat;
        for (int i = 0; i < k; i++)
            concat += s[i] + (i != k - 1 ? "#" : "");
        int n = concat.size(), cnt = 1, sum = 0, mx = 0;
        vector<int> mp(n);
        for (auto x: s) mp[sum] = cnt++, sum += x.size() + 1;
        for (auto &x: mp) x = mx = max(mx, x);
        SuffixArray sa(concat);
        auto lcp = sa.lcp_construction();
        set<pair<int, int> > st;
        map<int, int> Map;
        cnt = 0;
        k = (k + 1) / 2;
        for (int i = 0; i < k; i++) {
            cnt += (Map[mp[sa.p[i]]]++ == 0);
            if (i) st.insert({lcp[i], i});
        }
        auto pmx = *st.begin();
        set<pair<int, int> > v;
        v.insert(pmx);
        for (int i = 1, j = k; j < sa.n; i++, j++) {
            st.erase({lcp[i], i});
            st.insert({lcp[j], j});
            cnt -= (--Map[mp[sa.p[i - 1]]] == 0);
            cnt += (Map[mp[sa.p[j]]]++ == 0);
            v.insert(*st.begin());
            if (cnt == k) pmx = max(pmx, *st.begin());
        }
        auto it = v.end();
        it--;
        vector<string> ans;
        while (it->first == pmx.first) {
            ans.push_back(sa.s.substr(sa.sa[it->second], it->first));
            it--;
        }
        reverse(all(ans));
        return ans;
    }
 
    string lrs(string s) {
        SuffixArray sa(s);
        auto lcp = sa.lcp_construction();
        auto mx = max_element(all(lcp));
        int ind = mx - lcp.begin();
        return sa.s.substr(sa.sa[ind], *mx);
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
    string s;
    cin >> s;
    auto ans = sa_apps::lrs(s);
    if (ans.size() == 0) cout << -1 << endl;
    else cout << ans << endl;
}