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

struct SuffixArray {
    string s;
    vector<int> sa; // suffix array
    vector<int> lcp; // longest common prefix

    SuffixArray() {};

    SuffixArray(string str) {
        this->s = str;
        sa = suffix_array(str);
        lcp = lcp_array(str, sa);
    }

    vector<int> sa_naive(const vector<int> &s) {
        int n = (int) s.size();
        vector<int> v(n);
        iota(v.begin(), v.end(), 0);
        sort(v.begin(), v.end(), [&](int l, int r) {
            if (l == r) return false;
            while (l < n && r < n) {
                if (s[l] != s[r]) return s[l] < s[r];
                l++;
                r++;
            }
            return l == n;
        });
        return v;
    }

    vector<int> sa_doubling(const vector<int> &str) {
        int n = (int) str.size();
        vector<int> v(n), rnk = str, tmp(n);
        iota(v.begin(), v.end(), 0);
        for (int k = 1; k < n; k *= 2) {
            auto cmp = [&](int x, int y) {
                if (rnk[x] != rnk[y]) return rnk[x] < rnk[y];
                int rx = x + k < n ? rnk[x + k] : -1;
                int ry = y + k < n ? rnk[y + k] : -1;
                return rx < ry;
            };
            sort(v.begin(), v.end(), cmp);
            tmp[v[0]] = 0;
            for (int i = 1; i < n; i++) {
                tmp[v[i]] = tmp[v[i - 1]] + (cmp(v[i - 1], v[i]) ? 1 : 0);
            }
            swap(tmp, rnk);
        }
        return v;
    }

    template<int THRESHOLD_NAIVE = 10, int THRESHOLD_DOUBLING = 40>
    vector<int> sa_is(const vector<int> &str, int upper) {
        int n = (int) str.size();
        if (n == 0) return {};
        if (n == 1) return {0};
        if (n == 2) {
            if (str[0] < str[1]) {
                return {0, 1};
            } else {
                return {1, 0};
            }
        }
        if (n < THRESHOLD_NAIVE) {
            return sa_naive(str);
        }
        if (n < THRESHOLD_DOUBLING) {
            return sa_doubling(str);
        }

        vector<int> t_sa(n);
        vector<bool> ls(n);
        for (int i = n - 2; i >= 0; i--) {
            ls[i] = (str[i] == str[i + 1]) ? ls[i + 1] : (str[i] < str[i + 1]);
        }
        vector<int> sum_l(upper + 1), sum_s(upper + 1);
        for (int i = 0; i < n; i++) {
            if (!ls[i]) {
                sum_s[str[i]]++;
            } else {
                sum_l[str[i] + 1]++;
            }
        }
        for (int i = 0; i <= upper; i++) {
            sum_s[i] += sum_l[i];
            if (i < upper) sum_l[i + 1] += sum_s[i];
        }

        auto induce = [&](const vector<int> &lms) {
            fill(t_sa.begin(), t_sa.end(), -1);
            vector<int> buf(upper + 1);
            copy(sum_s.begin(), sum_s.end(), buf.begin());
            for (auto d: lms) {
                if (d == n) continue;
                t_sa[buf[str[d]]++] = d;
            }
            copy(sum_l.begin(), sum_l.end(), buf.begin());
            t_sa[buf[str[n - 1]]++] = n - 1;
            for (int i = 0; i < n; i++) {
                int v = t_sa[i];
                if (v >= 1 && !ls[v - 1]) {
                    t_sa[buf[str[v - 1]]++] = v - 1;
                }
            }
            copy(sum_l.begin(), sum_l.end(), buf.begin());
            for (int i = n - 1; i >= 0; i--) {
                int v = t_sa[i];
                if (v >= 1 && ls[v - 1]) {
                    t_sa[--buf[str[v - 1] + 1]] = v - 1;
                }
            }
        };

        vector<int> lms_map(n + 1, -1);
        int m = 0;
        for (int i = 1; i < n; i++) {
            if (!ls[i - 1] && ls[i]) {
                lms_map[i] = m++;
            }
        }
        vector<int> lms;
        lms.reserve(m);
        for (int i = 1; i < n; i++) {
            if (!ls[i - 1] && ls[i]) {
                lms.push_back(i);
            }
        }

        induce(lms);

        if (m) {
            vector<int> sorted_lms;
            sorted_lms.reserve(m);
            for (int v: t_sa) {
                if (lms_map[v] != -1) sorted_lms.push_back(v);
            }
            vector<int> rec_s(m);
            int rec_upper = 0;
            rec_s[lms_map[sorted_lms[0]]] = 0;
            for (int i = 1; i < m; i++) {
                int l = sorted_lms[i - 1], r = sorted_lms[i];
                int end_l = (lms_map[l] + 1 < m) ? lms[lms_map[l] + 1] : n;
                int end_r = (lms_map[r] + 1 < m) ? lms[lms_map[r] + 1] : n;
                bool same = true;
                if (end_l - l != end_r - r) {
                    same = false;
                } else {
                    while (l < end_l) {
                        if (str[l] != str[r]) {
                            break;
                        }
                        l++;
                        r++;
                    }
                    if (l == n || str[l] != str[r]) same = false;
                }
                if (!same) rec_upper++;
                rec_s[lms_map[sorted_lms[i]]] = rec_upper;
            }

            auto rec_sa =
                    sa_is<THRESHOLD_NAIVE, THRESHOLD_DOUBLING>(rec_s, rec_upper);

            for (int i = 0; i < m; i++) {
                sorted_lms[i] = lms[rec_sa[i]];
            }
            induce(sorted_lms);
        }
        return t_sa;
    }


    vector<int> suffix_array(const vector<int> &str, int upper) {
        assert(0 <= upper);
        for (int d: str) {
            assert(0 <= d && d <= upper);
        }
        return sa_is(str, upper);
    }

    template<class T>
    vector<int> suffix_array(const vector<T> &str) {
        int n = int(str.size());
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int l, int r) { return str[l] < str[r]; });
        vector<int> s2(n);
        int now = 0;
        for (int i = 0; i < n; i++) {
            if (i && str[idx[i - 1]] != str[idx[i]]) now++;
            s2[idx[i]] = now;
        }
        return sa_is(s2, now);
    }

    vector<int> suffix_array(const string &str) {
        int n = int(str.size());
        vector<int> s2(n);
        for (int i = 0; i < n; i++) {
            s2[i] = str[i];
        }
        return sa_is(s2, 255);
    }

    template<class T>
    vector<int> lcp_array(const vector<T> &str, const vector<int> &s_a) {
        int n = int(str.size());
        assert(n >= 1);
        vector<int> rnk(n);
        for (int i = 0; i < n; i++) {
            rnk[s_a[i]] = i;
        }
        vector<int> v(n - 1);
        int h = 0;
        for (int i = 0; i < n; i++) {
            if (h > 0) h--;
            if (rnk[i] == 0) continue;
            int j = s_a[rnk[i] - 1];
            for (; j + h < n && i + h < n; h++) {
                if (str[j + h] != str[i + h]) break;
            }
            v[rnk[i] - 1] = h;
        }
        return v;
    }

    vector<int> lcp_array(const string &str, const vector<int> &s_a) {
        int n = int(str.size());
        vector<int> s2(n);
        for (int i = 0; i < n; i++) {
            s2[i] = str[i];
        }
        return lcp_array(s2, s_a);
    }

    bool check(int mid, const string &t, bool greater = true) {
        int i = 0, j = sa[mid], m = (int) t.size();
        while (i < m && j < s.size()) {
            if (t[i] > s[j]) return false;
            if (t[i++] < s[j++]) return true;
        }
        return greater;
    }

    int lower_bound(const string &t) { // O(min(n,m)*log(n))
        int l = 0, r = s.size() - 1, ans = s.size(), mid;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (check(mid, t)) r = mid - 1, ans = mid;
            else l = mid + 1;
        }
        return ans;
    }

    int upper_bound(const string &t) { // O(min(n,t,size())*log(n))
        int l = 0, r = s.size() - 1, ans = s.size(), mid;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (check(mid, t, 0)) r = mid - 1, ans = mid;
            else l = mid + 1;
        }
        return ans;
    }

    bool exists_as_substr(const string t) {
        return occurrence_as_substr(t);
    }

    int occurrence_as_substr(const string &t) {
        return upper_bound(t) - lower_bound(t);
    }
};

template<typename T, bool LAZY = true>
class SegmentTree {
public:
    int n;
    vector<T> a, seg, lazy;

    SegmentTree(int n) : n(n) {
        a.resize(n);
        seg.resize(4 * n);
        if (LAZY) lazy.resize(8 * n);
    }

    SegmentTree(vector<T> a) {
        n = a.size();
        this->a = a;
        seg.resize(4 * n);
        if (LAZY) lazy.resize(8 * n);
        build(1, 1, n);
    }

    void update(int l, int r, T val) { // zeros indices
        if (r < l) swap(l, r);
        update(l + 1, r + 1, val, 1, 1, n);
    }

    void update(int ind, T val) { // zeros indices
        update(ind + 1, ind + 1, val, 1, 1, n);
    }

    T query(int l, int r) {
        if (r < l) swap(l, r);
        return query(l + 1, r + 1, 1, 1, n);
    }

private:
    T f(T x, T y) { // check this
        return x + y;
    }

    void build(int p, int l, int r) {
        if (LAZY) lazy[p] = 0;
        if (l == r) {
            seg[p] = a[l - 1]; // check this
            return;
        }
        int mid = (l + r) >> 1;
        build(p * 2, l, mid);
        build(p * 2 + 1, mid + 1, r);
        seg[p] = f(seg[p << 1], seg[(p << 1) + 1]);
    }

    void pushLazy(int p) { // check this
        if (!LAZY || lazy[p] == 0) return;
        lazy[p * 2] += lazy[p];
        lazy[p * 2 + 1] += lazy[p];
        seg[p] += lazy[p];
        lazy[p] = 0;
    }

    void update(int i, int j, T val, int p, int l, int r) {
        pushLazy(p);
        if (l > j || r < i) return;
        if (l >= i && r <= j) {
            if (LAZY) lazy[p] += val; // check this
            else seg[p] += val;
            pushLazy(p);
            return;
        }
        int mid = (l + r) / 2;
        update(i, j, val, p * 2, l, mid);
        update(i, j, val, p * 2 + 1, mid + 1, r);
        seg[p] = f(seg[p * 2], seg[p * 2 + 1]);
    }


    T query(int i, int j, int p, int l, int r) {
        if (LAZY) pushLazy(p);
        if (l > j || r < i) return 0; // check this
        if (l >= i && r <= j) return seg[p];
        int mid = (l + r) / 2;
        T c1 = query(i, j, p * 2, l, mid);
        T c2 = query(i, j, p * 2 + 1, mid + 1, r);
        return f(c1, c2);
    }
};

void testCase() {
    string s;
    cin >> s;
    int n = s.size();
    SuffixArray sa(s);
    SegmentTree<ll, true> st(n + 1);
    auto lcp = sa.lcp;
    lcp.insert(lcp.begin(), 0);
    for (int i = 1; i < n + 1; i++) {
        st.update(lcp[i - 1] + 1, n - sa.sa[i - 1], 1);
    }
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = st.query(i + 1, i + 1);
    }
    for (int x: ans) cout << x << ' ';
    cout << endl;
}
