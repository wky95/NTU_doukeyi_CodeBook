struct AugmentPath{
    int n, m;
    vector<vector<int>> G;
    vector<int> ma, mb;
    vector<int> vis;
    int now_time;
    int res;

    AugmentPath(int _n, int _m) : n(_n), m(_m), G(n), ma(n, -1), mb(m, -1), vis(n){
        now_time = 0;
        res = 0;
    }

    void add(int x, int y){
        G[x].push_back(y);
    }

    bool dfs(int now){
        vis[now] = now_time;

        for (auto x : G[now]){
            if (mb[x]==-1){
                ma[now] = x;
                mb[x] = now;
                return true;
            }
        }
        for (auto x : G[now]){
            if (vis[mb[x]]!=now_time && dfs(mb[x])){
                ma[now] = x;
                mb[x] = now;
                return true;
            }
        }
        return false;
    }

    int solve(){
        while (true){
            now_time++;
            int cnt = 0;
            for (int i=0 ; i<n ; i++){
                if (ma[i]==-1 && dfs(i)){
                    cnt++;
                }
            }
            if (cnt==0) break;
            res += cnt;
        }
        return res;
    }
};
