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
 
#define MAX_LETTERS 27
 
struct trie {
    trie *a[MAX_LETTERS], *fail;
    vector<int> chars, patterns;
 
    void insert(char *str, int patIndex) {
        if (*str == '\0') {
            patterns.push_back(patIndex);
            return;
        }
        int idx = *str - 'a';
        if (a[idx] == 0) chars.push_back(idx), a[idx] = new trie();
        a[idx]->insert(str + 1, patIndex);
    }
 
};
 
map<string, int> acc;
 
 
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
                q.push(x);
            }
        }
    }
 
    void match(string &s) {
        trie *now = root;
        int n = s.size();
        vector<int> vis(patternsNum, -1);
        for (int i = 0; i < n; i++) {
            now = getFail(now, s[i] - 'a');
            for (int id: now->patterns) {
                if (vis[id] == -1) vis[id] = i - patterns[id].size() + 2;
            }
        }
 
        for (int i = 0; i < patternsNum; i++) {
            acc[patterns[i]] = vis[i];
        }
    }
};
 
void testCase() {
    string s;
    cin >> s;
    int k;
    cin >> k;
    vector<string> allPatterns;
    vector<string> patterns;
    map<string, bool> Map;
    for (int i = 0; i < k; i++) {
        string pat;
        cin >> pat;
        allPatterns.push_back(pat);
        if (!Map[pat]) {
            patterns.push_back(pat);
            Map[pat] = 1;
        }
    }
 
    AhoCorasick aho(patterns);
 
    aho.match(s);
 
    for (string pat: allPatterns) {
        cout << acc[pat] << endl;
    }
 
}