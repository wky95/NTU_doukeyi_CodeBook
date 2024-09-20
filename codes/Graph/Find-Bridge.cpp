vector<int> dep(MAX_N), low(MAX_N);
vector<pair<int, int>> bridge;
bitset<MAX_N> vis;
 
void dfs(int now, int pre){
    vis[now] = 1;
    low[now] = dep[now] = (now==1 ? 0 : dep[pre]+1);
 
    for (auto x : G[now]){
        if (x==pre){
            continue;
        }else if (vis[x]==0){
            // 沒有走過的節點
            dfs(x, now);
            low[now] = min(low[now], low[x]);
        }else if (vis[x]==1){
            low[now] = min(low[now], dep[x]);
        }
    }
 
    if (now!=1 && low[now]==dep[now]){
        bridge.push_back({now, pre});
    }
    return;
}