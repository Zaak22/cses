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
private:
    int n;
    vector<int> Parent, Rank;
public:
    DSU(int x) : n(x) {
        Parent.assign(n + 1, 0);
        Rank.assign(n + 1, 0);
        for (int i = 0; i <= n; i++)Parent[i] = i;
    }

    int FindSet(int i) {
        return (Parent[i] == i) ? i : Parent[i] = FindSet(Parent[i]);
    }

    void UnionSets(int a, int b) {
        a = FindSet(a);
        b = FindSet(b);
        if (a != b) {
            if (Rank[a] < Rank[b])
                swap(a, b);
            Parent[b] = a;
            if (Rank[a] == Rank[b])
                Rank[a]++;
        }
    }
};

vector<vector<pair<int, int> > > Kruskal_DSU(int n, vector<pair<int, pair<int, int> > > &E) {
    vector<vector<pair<int, int> > > MST(n + 1, vector<pair<int, int> >());
    DSU dsu(n);
    sort(E.begin(), E.end());
    int cnt = 0;
    for (auto e: E) {
        int u = e.second.first;
        int v = e.second.second;
        int w = e.first;
        if (dsu.FindSet(u) == dsu.FindSet(v))continue;
        cnt++;
        MST[u].push_back({v, w});
        MST[v].push_back({u, w});
        dsu.UnionSets(u, v);
        if (cnt == n - 1)break;
    }
    return (cnt == n - 1 ? MST : vector<vector<pair<int, int> > >());
}

void testCase() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, pair<int, int> > > E;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        E.push_back({w, {u, v}});
    }
    auto MST = Kruskal_DSU(n, E);
    if(MST.empty()){
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    ll ans = 0;
    for (auto u: MST)
        for (auto v: u)
            ans += v.second;
    cout << ans / 2 << endl;
}
