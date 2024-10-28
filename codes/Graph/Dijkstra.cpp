// 可以在 O(E log E) 的時間複雜度解決在無負權有向圖單點源最短路
const int INF = 2e18; // 要確保 INF 開的足夠大

vector<vector<pair<int, int>>> G(n); // G[i] = <節點, 權重>
vector<int> dis(n, INF);
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
dis[s] = 0;
pq.push({0, s});

while (pq.size()){
    int now_dis = pq.top().first;
    int now_node = pq.top().second;
    pq.pop();

    if (now_dis>dis[now_node]) continue;

    for (auto x : G[now_node]){
        if (now_dis+x.second<dis[x.first]){
            dis[x.first] = now_dis+x.second;
            pq.push({dis[x.first], x.first});
        }
    }
}
