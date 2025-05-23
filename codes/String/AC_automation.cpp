const int MAXN = 5e5 + 5;
struct ac_automation {

    int go[MAXN][26], fail[MAXN], is_end[MAXN];
    int sz;

    void add(string s) {
        int now = 0;
        for (char c : s) {
            if (!go[now][c - 'a']) 
                go[now][c - 'a'] = ++sz;
            now = go[now][c - 'a'];
        }
        is_end[now]++;
    }
    vector<int> que;
    void build() {
        que.pb(0);
        for (int i = 0; i < ssize(que); i++) {
            auto u = que[i];
            FOR (c, 0, 25) {
                if (go[u][c]) {
                    int v = go[u][c];
                    fail[v] = !u ? 0 : go[fail[u]][c];
                    is_end[v] += is_end[fail[v]];
                    que.pb(v);
                }
                else {
                    go[u][c] = go[fail[u]][c];
                }
            }
        }
    }

} AC;
