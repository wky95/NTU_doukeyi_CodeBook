// 需要重構、需要增加註解
#include <bits/stdc++.h>
#define F first
#define S second
#define all(x) begin(x), end(x)
#ifdef LOCAL
#define HEHE freopen("in.txt", "r", stdin);
#else
#define HEHE ios_base::sync_with_stdio(0), cin.tie(0);
#endif
using namespace std;

#define chmax(a, b) (a) = (a) < (b) ? (b) : (a)
#define chmin(a, b) (a) = (a) < (b) ? (a) : (b)

#define ll long long

#define FOR(i, a, b) for (int i = a; i <= b; i++)

int N, W, cur;
vector<int> w, v, sz;
vector<vector<int>> adj, dp;

void dfs(int x) {
    sz[x] = 1;
    for (int i : adj[x]) dfs(i), sz[x] += sz[i];
    cur++;
    // choose x
    FOR (i, w[x], W) {
        dp[cur][i] = dp[cur - 1][i - w[x]] + v[x];
    }
    // not choose x
    FOR (i, 0, W) {
        chmax(dp[cur][i], dp[cur - sz[x]][i]);
    }
}

signed main() {
    HEHE
    cin >> N >> W;
    adj.resize(N + 1);
    w.assign(N + 1, 0);
    v.assign(N + 1, 0);
    sz.assign(N + 1, 0);
    dp.assign(N + 2, vector<int>(W + 1, 0));
    FOR (i, 1, N) {
        int p; cin >> p;
        adj[p].push_back(i);
    }
    FOR (i, 1, N) cin >> w[i];
    FOR (i, 1, N) cin >> v[i]; 
    dfs(0);
    cout << dp[N + 1][W] << '\n';
}