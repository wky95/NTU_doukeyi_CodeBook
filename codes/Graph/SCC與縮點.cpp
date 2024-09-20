/*
給定一個有向圖，迴回傳縮點後的圖、SCC 的資訊
所有點都以 based-0 編號

函式：
SCC_compress G(n): 宣告一個有 n 個點的圖
.add_edge(u, v): 加上一條邊 u -> v
.compress: O(n log n) 計算 G3、SCC、SCC_id 的資訊，並把縮點後的結果存在 result 裡
*/
struct SCC_compress{
    int n = 0, m = 0;
    vector<vector<int>> G, inv_G, result;
    vector<pair<int, int>> edges;
    vector<bool> vis;
    vector<int> order;

    vector<vector<int>> SCC; // SCC[i] = 某個 SCC 中的所有點
    vector<int> SCC_id;      // SCC_id[i] = 第 i 個點在第幾個 SCC

    SCC_compress(int _n){ // 點的數量
        n = _n;
        G.resize(n);
        inv_G.resize(n);
        result.resize(n);
        vis.resize(n);
        SCC_id.resize(n);
    }

    void add_edge(int u, int v){
        G[u].push_back(v);
        inv_G[v].push_back(u);
        edges.push_back({u, v});
        m++;
    }

    void dfs1(vector<vector<int>> &G, int now){
        vis[now] = 1;
        for (auto x : G[now]){
            if (vis[x]==0){
                dfs1(G, x);
            }
        }
        order.push_back(now);
        return;
    }
    
    void dfs2(vector<vector<int>> &G, int now){
        SCC_id[now] = SCC.size()-1;
        SCC.back().push_back(now);
        vis[now] = 1;
    
        for (auto x : G[now]){
            if (vis[x]==0){
                dfs2(G, x);
            }
        }
        return;
    }

    void compress(){
        // 找反圖順序
        fill(vis.begin(), vis.end(), 0);
        for (int i=0 ; i<n ; i++){
            if (vis[i]==0){
                dfs1(G, i);
            }
        }

        // 找到 SCC
        fill(vis.begin(), vis.end(), 0);
        reverse(order.begin(), order.end());
        for (int i=0 ; i<n ; i++){
            if (vis[order[i]]==0){
                SCC.push_back(vector<int>());
                dfs2(inv_G, order[i]);
            }
        }

        // 縮點做 DAG
        for (int i=0 ; i<m ; i++){
            if (SCC_id[edges[i].first]!=SCC_id[edges[i].second]){
                result[SCC_id[edges[i].first]].push_back(SCC_id[edges[i].second]);
            }
        }
        for (int i=0 ; i<SCC.size() ; i++){
            sort(result[i].begin(), result[i].end());
            result[i].resize(unique(result[i].begin(), result[i].end())-result[i].begin());
        }
    }
};