// O(m sqrt m) 枚舉無向圖所有三角形，0-based
void Enumerate_Triangle(vector<pair<int, int>> &edge, vector<int> &deg){
    int n = deg.size();
    int m = edge.size();
    vector<vector<int>> G(n);

    for (int i=0 ; i<m ; i++){
        if (deg[edge[i].first] > deg[edge[i].second]) swap(edge[i].first, edge[i].second);
        if (deg[edge[i].first] == deg[edge[i].second] && edge[i].first > edge[i].second) swap(edge[i].first, edge[i].second);
        G[edge[i].first].push_back(edge[i].second);
    }

    vector<int> vis(n, false);
    for (int i=0 ; i<n ; i++){
        for (auto j : G[i]) vis[j] = true;
        for (auto j : G[i]){
            for (auto k : G[j]){
                if (vis[k]){
                    // i, j, k is a triangle
                }
            }
        }
        for (auto j : G[i]) vis[j] = false;
    }
}