struct Poly {
    int len, deg;
    mint *a;
    // len = 2^k >= the original length
    Poly(): len(0), deg(0), a(nullptr) {}
    Poly(int _n) {
        len = 1;
        deg = _n - 1;
        while (len < _n) len <<= 1;
        a = new mint[len]();
    }
    Poly(int l, int d, mint *b) {
        len = l;
        deg = d;
        a = b;
    }
    void resize(int _n) {
        int len1 = 1;
        while (len1 < _n) len1 <<= 1;

        mint *res = new mint[len1]();
        for (int i = 0; i < min(len, _n); i++)
            res[i] = a[i];
        len = len1;
        deg = _n - 1;
        delete [] a;
        a = res;
    }
    Poly& operator=(const Poly rhs) {
        this->len = rhs.len;
        this->deg = rhs.deg;
        delete [] this->a;
        this->a = new mint[this->len]();
        copy(rhs.a, rhs.a + len, this->a);
        return *this;
    }
    Poly operator*(Poly rhs) {
        int l1 = this->len, l2 = rhs.len;
        int d1 = this->deg, d2 = rhs.deg;
        while (l1 > 0 and this->a[l1 - 1] == 0) l1--;
        while (l2 > 0 and rhs.a[l2 - 1] == 0) l2--;
        int l = 1;
        while (l < max(l1 + l2 - 1, d1 + d2 + 1)) l <<= 1;
        mint *x, *y, *res;
        x = new mint[l]();
        y = new mint[l]();
        res = new mint[l]();
        copy(this->a, this->a + l1, x);
        copy(rhs.a, rhs.a + l2, y);
        ntt.NTT(x, l, 1); ntt.NTT(y, l, 1);
        FOR (i, 0, l - 1) 
            res[i] = x[i] * y[i];
        ntt.NTT(res, l, -1);
        delete [] x; delete [] y;
        return Poly(l, d1 + d2, res);
    }
    Poly operator+(Poly rhs) {
        int l1 = this->len, l2 = rhs.len;
        int l = max(l1, l2);
        Poly res;
        res.len = l;
        res.deg = max(this->deg, rhs.deg);
        res.a = new mint[l]();
        FOR (i, 0, l1 - 1) res.a[i] += this->a[i];
        FOR (i, 0, l2 - 1) res.a[i] += rhs.a[i];
        return res;
    }
    Poly operator-(Poly rhs) {
        int l1 = this->len, l2 = rhs.len;
        int l = max(l1, l2);
        Poly res;
        res.len = l;
        res.deg = max(this->deg, rhs.deg);
        res.a = new mint[l]();
        FOR (i, 0, l1 - 1) res.a[i] += this->a[i];
        FOR (i, 0, l2 - 1) res.a[i] -= rhs.a[i];
        return res;
    }
    Poly operator*(const mint rhs) {
        Poly res;
        res = *this;
        FOR (i, 0, res.len - 1) res.a[i] = res.a[i] * rhs;
        return res;
    }
    Poly(vector<int> f) {
        int _n = f.size();
        len = 1;
        deg = _n - 1;
        while (len < _n) len <<= 1;
        a = new mint[len]();
        FOR (i, 0, deg) a[i] = f[i];
    }
    Poly derivative() {
        Poly g(this->deg);
        FOR (i, 1, this->deg) 
            g.a[i - 1] = this->a[i] * i;
        return g;
    }
    Poly integral() {
        Poly g(this->deg + 2);
        FOR (i, 0, this->deg) 
            g.a[i + 1] = this->a[i] / (i + 1);
        return g;
    }
    Poly inv(int len1 = -1) {
        if (len1 == -1) len1 = this->len;
        Poly g(1); g.a[0] = a[0].inv();
        for (int l = 1; l < len1; l <<= 1) {
            Poly t; t = *this;
            t.resize(l << 1);
            t = g * g * t;
            t.resize(l << 1);
            Poly g1 = g * mint(2) - t;
            swap(g, g1);
        }
        return g;
    }
    Poly ln(int len1 = -1) {
        if (len1 == -1) len1 = this->len;
        auto g = *this;
        auto x = g.derivative() * g.inv(len1);
        x.resize(len1);
        x = x.integral();
        x.resize(len1);
        return x;
    }
    Poly exp() {
        Poly g(1);
        g.a[0] = 1;
        for (int l = 1; l < len; l <<= 1) {
            Poly t, g1; t = *this;
            t.resize(l << 1); t.a[0]++;
            g1 = (t - g.ln(l << 1)) * g;
            g1.resize(l << 1);
            swap(g, g1);
        }
        return g;
    }
    Poly pow(ll n) {
        Poly &a = *this;
        int i = 0;
        while (i <= a.deg and a.a[i] == 0) i++;
        if (i and (n > a.deg or n * i > a.deg)) return Poly(a.deg + 1);
        if (i == a.deg + 1) {
            Poly res(a.deg + 1);
            res.a[0] = 1;
            return res;
        }
        Poly b(a.deg - i + 1);
        mint inv1 = a.a[i].inv();
        FOR (j, 0, b.deg) 
            b.a[j] = a.a[j + i] * inv1;
        Poly res1 = (b.ln() * mint(n % mod)).exp() * (a.a[i].pow(n));
        Poly res2(a.deg + 1);
        FOR (j, 0, min((ll)(res1.deg), (ll)(a.deg - n * i))) 
            res2.a[j + n * i] = res1.a[j];
        return res2;
    }
};