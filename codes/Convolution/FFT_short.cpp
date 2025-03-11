#define int long long

using Cplx = complex<double>;
const double pi = acos(-1);
const int mod = 998244353, g = 3;
int power(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
int inv(int x) { return power(x, mod - 2); }
// FFT use Cplx, NTT use ll
void FFT(vector<int> &a, int n, int op) {
    // n must be 2^k
    vector<int> R(n);
    FOR (i, 0, n - 1) 
        R[i] = R[i/2]/2 + (i&1)*(n/2);
    FOR (i, 0, n - 1) 
        if (i < R[i]) swap(a[i], a[R[i]]);
    for (int m = 2; m <= n; m *= 2) {
        // Cplx w1({cos(2*pi/m), sin(2*pi/m)*op});
        int w1 = power(g, (mod-1)/m * op + mod-1);
        for (int i = 0; i < n; i += m) {
            // Cplx wk({1, 0});
            int wk = 1;
            FOR (k, 0, m / 2 - 1) {
                auto x = a[i+k], y = a[i+k+m/2] * wk % mod;
                a[i+k] = (x+y) % mod;
                a[i+k+m/2] = (x-y+mod) % mod;
                wk = wk * w1 % mod;
            }
        }
    }
    if (op == -1) 
        FOR (i, 0, n - 1) {
            // a[i] = a[i] / n;
            a[i] = a[i] * inv(n) % mod;
        }
}