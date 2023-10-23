#include<bits/stdc++.h>
 
using namespace std;
 
#define ll long long
#define ld long double
#define oo 1e18
#define endl '\n'
#define all(v) v.begin(),v.end()
 
#ifdef LOCAL
 
#include "debug.h"
#include <chrono>
 
using namespace std::chrono;
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x);
#define FASTIO ios_base::sync_with_stdio(0),cin.tie(0),cerr.tie(0),cout.tie(0)
#define TL 1000
#else
#define debug(x...)
#define FASTIO ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#endif
 
int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};
 
const int N = 2e6 + 10, mod = 1e9 + 7;
const double EPS = 1e-12, Pi = acos(-1);
 
int odd[N];
int even[N];
 
void manacher(string t) {
    string s = " ";
    for (auto c: t)
        s += string(1, c) + ' ';
    int len = (int) s.size();
    vector<int> ans(len);
    int maxi = 0;
    for (int i = 1; i < len; i++) {
        int k = 0;
        if (maxi + ans[maxi] >= i)
            k = min(ans[maxi] + maxi - i, ans[2 * maxi - i]);
        for (; s[i + k] == s[i - k] && i - k >= 0 && i + k < len; k++);
        ans[i] = k - 1;
        if (i + ans[i] > maxi + ans[maxi])
            maxi = i;
    }
    for (int i = 1, j = 0; i < len; i += 2)
        odd[j++] = ans[i];
    for (int i = 2, j = 0; i + 1 < len; i += 2)
        even[j++] = ans[i];
}
 
bool isPal(int l, int r) {
    int len = (r - l + 1);
    int center = (l + r) / 2;
    if (len % 2) return odd[center] >= len;
    else return even[center] >= len;
}
 
void testCase() {
    string s;
    cin >> s;
    manacher(s);
    int n = s.size();
    auto it = max_element(odd, odd + n);
    int oddMax = it - odd;
    string ans = s.substr(oddMax - (*it) / 2, *it);
    it = max_element(even, even + n);
    int evenMax = it - even;
    if (evenMax - (*it) / 2 + 1 >= 0) {
        string evenAns = s.substr(evenMax - (*it) / 2 + 1, *it);
        if (evenAns.size() > ans.size()) ans = evenAns;
    }
 
    cout << ans << endl;
 
}
 
int main() {
    FASTIO;
#ifdef LOCAL
    auto start = high_resolution_clock::now();
#endif
 
    int T = 1;
//    cin >> T;
    for (int i = 0; i < T; i++) {
        testCase();
    }
 
#ifdef LOCAL
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
 
    auto exc_time = duration.count() / 1e3;
    if (exc_time > TL) {
        printf("\n\033[7;31mtakes: \033[1;31m%.1f\033[1;31m ms\033[0m", exc_time);
    } else {
        printf("\n\033[7;32mtakes: \033[1;32m%.1f\033[1;32m ms\033[0m", exc_time);
    }
#endif
    return 0;
}