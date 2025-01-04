/*
Problem:
    Given w = [w_0, w_1, ..., w_{n-1}] (which can be
    either positive or negative or 0), you can choose
    to take w_i (0 < i < n) or not, but if edge u -> v
    exists, you must take w_v if you want to take w_u
    (in other words, you can't take w_u without taking
     w_v), this function returns the maximum value(> 0)
     you can get. If you need a construction, you can
     output the minimum cut of the S(source) side.
Complexity:
    MaxFlow(n, m) (Non-Biparte:O(n²m) / Bipartite:O(m√n))
*/
int maximum_closure(vector<int> w, vector<pair<int,int>> EV) {
    int n = w.size(), S = n + 1, T = n + 2;
    Flow G(T + 5); // Graph/Dinic.cpp
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        if (w[i] > 0) {
            G.add(S, i, w[i]);
            sum += w[i];
        }
        else if (w[i] < 0) {
            G.add(i, T, abs(w[i]));
        }
    }
    for (auto &[u, v] : EV) { // You should make sure that INF > Σ|w_i|
        G.add(u, v, INF);
    }
    int cut = G.flow(S, T);
    return sum - cut;
}
