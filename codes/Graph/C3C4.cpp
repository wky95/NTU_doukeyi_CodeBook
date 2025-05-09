// 0-based
void C3C4(vector<int> deg, vector<array<int, 2>> edges){
    int N = deg.size();
    int M = deges.size();
    
    vector<int> ord(N), rk(N);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int x, int y) { return deg[x] > deg[y]; });
    for (int i=0 ; i<N ; i++) rk[ord[i]] = i;
    
    vector<vector<int>> D(N), adj(N);
    for (auto [u, v] : e) {
        if (rk[u] > rk[v]) swap(u, v);
        D[u].emplace_back(v);
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    
    vector<int> vis(N);
    
    int c3 = 0, c4 = 0;
    for (int x : ord) { // c3
        for (int y : D[x]) vis[y] = 1;
        for (int y : D[x]) for (int z : D[y]){
            c3 += vis[z]; // xyz is C3
        }
        for (int y : D[x]) vis[y] = 0;
    }
    for (int x : ord) { // c4
        for (int y : D[x]) for (int z : adj[y])
            if (rk[z] > rk[x]) c4 += vis[z]++;
        for (int y : D[x]) for (int z : adj[y])
            if (rk[z] > rk[x]) --vis[z];
    }   // both are O(M*sqrt(M)), test @ 2022 CCPC guangzhou
    cout << c4 << "\n";
}