// ax + by = c
int extgcd_abc(int a, int b, int c, int &x, int &y) {
    if (b == 0) {
        if (c % a) return INF;
        x = c / a, y = 0;
        return abs(a);
    }
    int x1, y1;
    int g = extgcd_abc(b, a % b, c, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return g;
}
// Sorry that I don't know how to merge two functions
int extgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int ret = extgcd(b, a % b, y, x);
    y -= a / b * x;
    return ret;
}

// 有 n 個式子，求解 x ≡ a_i (mod m_i)
int CRT_m_coprime(int n, vector<int> &a, vector<int> &m) {
    int p = 1, ans = 0;
    vector<int> M(n), inv_M(n);

    for (int i = 0; i < n; i++) p *= m[i];
    for (int i = 0; i < n; i++) {
        M[i] = p / m[i];
		int tmp;
        extgcd(M[i], m[i], inv_M[i], tmp);
        ans += a[i] * inv_M[i] * M[i];
        ans %= p;
    }
    return (ans % p + p) % p;
}

// 對於方程組的式子兩兩求解
// 回傳：{是否有解, {a, m}}
pair<bool, pair<int, int>> CRT_m_NOT_coprime(int a1, int m1, int a2, int m2) {
    int g = __gcd(m1, m2);
    if ((a2 - a1) % g != 0) return {0, {-1, -1}};

    int x, y; extgcd(m1, m2, x, y);

    x = (a2 - a1) * x / g; // 兩者不能相反
    a1 = x * m1 + a1;
    m1 = m1 * m2 / g;
    a1 = (a1 % m1 + m1) % m1;
    return {1, {a1, m1}};
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
