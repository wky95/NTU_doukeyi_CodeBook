#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
vector <int> G[N];
int low[N], depth[N];
bool vis[N];
vector <vector <int>> bcc;
stack <int> stk;

void dfs(int v, int p) {
    stk.push(v);
    vis[v] = true;
    low[v] = depth[v] = (p == -1 ? 1 : depth[p] + 1);
    for (int u : G[v]) {
        if (u == p) continue;
        if (!vis[u]) {
            /// (v, u) 是樹邊
            dfs(u, v);
            low[v] = min(low[v], low[u]);
        } else {
            /// (v, u) 是回邊
            low[v] = min(low[v], depth[u]);
        }
    }
    /// v 在不依靠父邊的情況下永遠沒辦法走到它的祖先
    if (low[v] == depth[v]) {
        bcc.emplace_back();
        while (stk.top() != v) {
            bcc.back().push_back(stk.top());
            stk.pop();
        }
        bcc.back().push_back(stk.top());
        stk.pop();
    }
}