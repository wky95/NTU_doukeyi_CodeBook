// 0-based
struct PlanarGraph{
    int n, m, id;
    vector<point<int>> v;
    vector<vector<pair<int, int>>> G;
    vector<int> conv, nxt, vis;

    PlanarGraph(int n, int m, vector<point<int>> _v) : 
    n(n), m(m), id(0),
    v(_v), G(n),
    conv(2*m), nxt(2*m), vis(2*m) {}

    void add_edge(int x, int y){
        G[x].push_back({y, 2*id});
        G[y].push_back({x, 2*id+1});
        conv[2*id] = x;
        conv[2*id+1] = y;
        id++;
    }

    vector<int> enumerate_face(){
        for (int i=0 ; i<n ; i++){
            sort(G[i].begin(), G[i].end(), [&](pair<int, int> a, pair<int, int> b){
                return (v[a.first]-v[i])<(v[b.first]-v[i]);
            });
            
            int sz = G[i].size(), pre = sz-1;
            for (int j=0 ; j<sz ; j++){
                nxt[G[i][pre].second] = G[i][j].second^1;
                pre = j;
            }
        }

        vector<int> ret;
        for (int i=0 ; i<2*m ; i++){
            if (vis[i]==false){
                int area = 0, now = i;
                vector<int> pt;

                while (!vis[now]){
                    vis[now] = true;
                    pt.push_back(conv[now]);
                    now = nxt[now];
                }

                pt.push_back(pt.front());
                for (int i=0 ; i+1<pt.size() ; i++){
                    area -= (v[pt[i]]^v[pt[i+1]]);
                }
                
                // pt = face boundary
                if (area>0){
                    ret.push_back(area);
                }else{
                    // pt is outer face
                }
            }
        }
        return ret;
    }
};