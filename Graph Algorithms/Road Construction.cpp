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
const int N = 2e5 + 10, M = 1e2 + 10, mod = 998244353;
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

class DSU {
public:
    int n, compNum;
    vector<int> Parent, Rank, Size;

    DSU(int x) : n(x) {
        Parent.assign(n + 1, 0);
        Size.assign(n + 1, 1);
        Rank.assign(n + 1, 0);
        compNum = n;
        for (int i = 0; i <= n; i++) Parent[i] = i;
    }

    int FindSet(int i) {
        return (Parent[i] == i) ? i : Parent[i] = FindSet(Parent[i]);
    }

    int GetComponentSize(int i) {
        return Size[FindSet(i)];
    }

    void UnionSets(int a, int b) {
        a = FindSet(a);
        b = FindSet(b);
        if (a != b) {
            if (Rank[a] < Rank[b])
                swap(a, b);
            Parent[b] = a;
            Size[a] += Size[b];
            compNum--;
            if (Rank[a] == Rank[b])
                Rank[a]++;
        }
    }
};

void testCase() {
    int n, m, ans = 0;
    cin >> n >> m;
    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        dsu.UnionSets(u, v);
        ans = max(ans, dsu.GetComponentSize(u));
        cout << dsu.compNum << ' ' << ans << endl;
    }
    cout << endl;
}
