struct BoundedFlow : Dinic {
	vector<ll> tot;
	void init(int _n) {
		Dinic::init(_n + 2);
		tot.assign(n, 0);
	}
	void add_edge(int u, int v, ll lcap, ll rcap) {
		tot[u] -= lcap, tot[v] += lcap;
		g[u].pb(edge{v, rcap, lcap, SZ(g[v])});
		g[v].pb(edge{u, 0, 0, SZ(g[u]) - 1});
	}
	bool feasible() {
		ll sum = 0;
		int vs = n - 2, vt = n - 1;
		for(int i = 0; i < n - 2; ++i)
			if(tot[i] > 0)
				add_edge(vs, i, 0, tot[i]), sum += tot[i];
			else if(tot[i] < 0) add_edge(i, vt, 0, -tot[i]);
		if(sum != maxflow(vs, vt)) sum = -1;
		for(int i  =0; i < n - 2; i ++){
			if(tot[i] > 0)
				g[vs].pop_back(), g[i].pop_back();
			else if(tot[i] < 0)
				g[i].pop_back(), g[vt].pop_back();
		}
		return sum != -1;
	}
	ll boundedflow(int _s, int _t) {
		add_edge( _t, _s, 0, INF);
		if(!feasible()) return -1;
		ll x = g[_t].back().flow;
		g[_t].pop_back(), g[_s].pop_back();
		return x - maxflow(_t, _s);
	}
};