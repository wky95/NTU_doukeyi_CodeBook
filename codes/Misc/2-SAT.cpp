#include <bits/stdc++.h>
using namespace std;

struct TWO_SAT {
    int n, N;
    vector<vector<int>> G, rev_G;
    deque<bool> used;
    vector<int> order, comp;
    deque<bool> assignment;
    void init(int _n) {
        n = _n;
        N = _n * 2;
        G.resize(N + 5);
        rev_G.resize(N + 5);
    }
    void dfs1(int v) {
        used[v] = true;
        for (int u : G[v]) {
            if (!used[u])
                dfs1(u);
        }
        order.push_back(v);
    }
    void dfs2(int v, int cl) {
        comp[v] = cl;
        for (int u : rev_G[v]) {
            if (comp[u] == -1)
                dfs2(u, cl);
        }
    }
    bool solve() {
        order.clear();
        used.assign(N, false);
        for (int i = 0; i < N; ++i) {
            if (!used[i])
                dfs1(i);
        }
        comp.assign(N, -1);
        for (int i = 0, j = 0; i < N; ++i) {
            int v = order[N - i - 1];
            if (comp[v] == -1)
                dfs2(v, j++);
        }
        assignment.assign(n, false);
        for (int i = 0; i < N; i += 2) {
            if (comp[i] == comp[i + 1])
                return false;
            assignment[i / 2] = (comp[i] > comp[i + 1]);
        }
        return true;
    }
    void add_disjunction(int a, bool na, int b, bool nb) { // A or B
        // na means whether a is negative or not
        // nb means whether b is negative or not
        a = 2 * a ^ na;
        b = 2 * b ^ nb;
        int neg_a = a ^ 1;
        int neg_b = b ^ 1;
        G[neg_a].push_back(b);
        G[neg_b].push_back(a);
        rev_G[b].push_back(neg_a);
        rev_G[a].push_back(neg_b);
        return;
    }
    void get_result(vector<int>& res) {
        res.clear();
        for (int i = 0; i < n; i++)
            res.push_back(assignment[i]);
    }
};
/* CSES Giant Pizza
3 5
+ 1 + 2
- 1 + 3

- + + + -
*/
int main() {
    int n, m;
    cin >> n >> m;
    TWO_SAT E;
    E.init(m);

    char c1, c2;
    int inp1, inp2;
    for (int i = 0; i < n; i++) {
        cin >> c1 >> inp1;
        cin >> c2 >> inp2;
        E.add_disjunction(inp1 - 1, c1 == '-', inp2 - 1, c2 == '-');
    }

    bool able = E.solve();
    if (able) {
        vector <int> ans;
        E.get_result(ans);
        for (int i : ans)
            cout << (i == true ? '+' : '-') << ' ';
        cout << '\n';
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}