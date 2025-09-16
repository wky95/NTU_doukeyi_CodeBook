// 求出 d = gcd(a,b)，並找出 x, y 使 ax + by = d
tuple<int, int, int> extgcd(int a, int b){
    if (!b) return {a, 1, 0};
    auto [d, x, y] = extgcd(b, a%b);
    return {d, y, x-a/b*y};
}

// CRT maybe need use int128
int CRT_m_coprime(vector<int> &a, vector<int> &m) {
    int n = a.size(), p = 1, ans = 0;
    vector<int> M(n), invM(n);

    for (int i=0 ; i<n ; i++) p *= m[i];
    for (int i=0 ; i<n ; i++){
        M[i] = p/m[i];
        auto [d, x, y] = extgcd(M[i], m[i]);
        invM[i] = x;
        ans += a[i]*invM[i]*M[i];
        ans %= p;
    }
    return (ans%p+p)%p;
}

// CRT maybe need use int128
int CRT_m_not_coprime(vector<int> &a, vector<int> &m) {
    int n = a.size();

    for (int i=1 ; i<n ; i++){
        int g = __gcd(m[0], m[i]);
        if ((a[i]-a[0])%g!=0) return -1;

        auto [d, x, y] = extgcd(m[0], m[i]);
        x = (a[i]-a[0])*x/g;

        a[0] = x*m[0]+a[0];
        m[0] = m[0]*m[i]/g;
        a[0] = (a[0]%m[0]+m[0])%m[0];
    }

    if (a[0]<0) return a[0]+m[0];
    return a[0];
}

// ans = a / b (mod m)
// ans = ret.F + k * ret.S, k is integer
pair<int, int> div(int a, int b, int m) {
    int flag = 1;
    if (a < 0) { a = -a; flag *= -1; }
    if (b < 0) { b = -b; flag *= -1; }
    int t = -1, k = -1;
    int res = extgcd_abc(b, m, a, t, k);
    if (res == INF) return {INF, INF};
    m = abs(m / res);
    t = t * flag;
    t = (t % m + m) % m;
    return {t, m};
}
