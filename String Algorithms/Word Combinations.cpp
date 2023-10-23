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
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
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
 
#define MAX_LETTERS 27
 
int getIdx(char x) {
    if (x >= 'a' && x <= 'z') return x - 'a';
    else return 26; //invalid char
}
 
struct trie {
    trie *a[MAX_LETTERS], *fail;
    vector<int> chars, patterns;
    int matchCnt;
 
    void insert(char *str, int patIndex) {
        if (*str == '\0') {
            matchCnt++;
            patterns.push_back(patIndex);
            return;
        }
        int idx = getIdx(*str);
        if (a[idx] == 0) chars.push_back(idx), a[idx] = new trie();
        a[idx]->insert(str + 1, patIndex);
    }
 
};
 
struct AhoCorasick {
    vector<string> patterns;
    int patternsNum;
    trie *root;
 
    AhoCorasick(vector<string> &patterns) {
        root = new trie();
        this->patterns = patterns;
        patternsNum = patterns.size();
        for (int i = 0; i < patternsNum; i++)
            root->insert(&patterns[i][0], i);
        bfs();
    }
 
    trie *getFail(trie *cur, int ch) {
        trie *ret = cur;
        while (ret->a[ch] == 0) ret = ret->fail;
        return ret->a[ch];
    }
 
    void bfs() {
        queue<trie *> q;
        root->fail = root;
        for (auto &x: root->a) {
            if (x == 0) x = root;
            else x->fail = root, q.push(x);
        }
        while (!q.empty()) {
            trie *cur = q.front();
            q.pop();
 
            for (int ch: cur->chars) {
                auto fail = getFail(cur->fail, ch);
                auto &x = cur->a[ch];
                x->fail = fail;
                x->patterns.insert(x->patterns.end(), all(fail->patterns));
                x->matchCnt += fail->matchCnt;
                q.push(x);
            }
        }
    }
 
    int match(string &s) {
        trie *now = root;
        int n = s.size();
        vector<ll> dp(n + 1);
        dp[0] = 1;
        for (int i = 0; i < n; i++) {
            now = getFail(now, getIdx(s[i]));
            for (int id: now->patterns) {
                dp[i + 1] = (dp[i + 1] + dp[i + 1 - patterns[id].size()]) % mod;
            }
        }
        return dp[n];
    }
};
 
void testCase() {
    string s;
    cin >> s;
    int n;
    cin >> n;
    vector<string> patterns(n);
    for (string &p: patterns) {
        cin >> p;
    }
    AhoCorasick aho(patterns);
    cout << aho.match(s) << endl;
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
        printf("\033[7;31mtakes: \033[1;31m%.1f\033[1;31m ms\033[0m", exc_time);
    } else {
        printf("\033[7;32mtakes: \033[1;32m%.1f\033[1;32m ms\033[0m", exc_time);
    }
#endif
    return 0;
}