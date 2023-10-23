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
 
const int MAX_N = 2e6 + 10, mod = 1e9 + 7;
const double EPS = 1e-12, Pi = acos(-1);
 
string least_rotation(string s) {
    s += s;
    vector<int> f(s.size(), -1);
    int k = 0;
    for (int j = 1; j < s.size(); j++) {
        char sj = s[j];
        int i = f[j - k - 1];
        while (i != -1 && sj != s[k + i + 1]) {
            if (sj < s[k + i + 1]) k = j - i - 1;
            i = f[i];
        }
        if (sj != s[k + i + 1]) {
            if (sj < s[k]) k = j;
            f[j - k] = -1;
        } else f[j - k] = i + 1;
    }
    return s.substr(k, s.size() / 2);
}
 
void testCase() {
    string s;
    cin >> s;
    cout << least_rotation(s) << endl;
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