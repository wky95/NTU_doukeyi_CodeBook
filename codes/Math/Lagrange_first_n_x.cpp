#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 5e5 + 10;
const int mod = 1e9 + 7;

long long inv_fac[MAX_N];

inline int fp(long long x, int y) {
    int ret = 1;
    for (; y; y >>= 1) {
        ret = (y & 1) ? (ret * x % mod) : ret;
        x = x * x % mod;
    }
    return ret;
}

// TO USE THIS TEMPLATE, YOU MUST MAKE SURE THAT THE MOD NUMBER IS A PRIME.
struct Lagrange {
    /*
        Initialize a polynomial with f(1), f(2), ..., f(n).
        This determines a polynomial f(x) whose degree is at most (n - 1).
        Then you can call sample(x) and you get the value of f(x).
    */
    int n;
    vector<int> v, mul;

    // O(log p + MAX_N) You can use this function if you don't have inv_fac array already.
    void construct_inv_fac() {
        long long fac = 1;
        for (int i = 2; i < MAX_N; ++i) {
            fac = fac * i % mod;
        }
        inv_fac[MAX_N - 1] = fp(fac, mod - 2);
        for (int i = MAX_N - 1; i >= 1; --i) {
            inv_fac[i - 1] = inv_fac[i] * i % mod;
        }
    }

    // O(n), You call init() many times without having a second instance of this struct.
    void init(vector<int> &u) {
        v = u;
        if (v.size() == 1) v.push_back(v[0]);
        n = v.size();
        mul.resize(n);
    }

    // O(n) You can use sample(x) instead of sample(x % mod).
    int sample(int x) {
        x = (x < 0) ? (x % mod + mod * 2) : (x % mod + mod);
        long long now = 1;
        for (int i = n; i >= 1; --i) {
            mul[i - 1] = now;
            now = now * (x - i) % mod;
        }
        int ret = 0;
        bool neg = (n - 1) & 1;
        now = 1;
        for (int i = 1; i <= n; ++i) {
            int up = now * mul[i - 1] % mod;
            int down = inv_fac[n - i] * inv_fac[i - 1] % mod;
            int tmp = ((long long)v[i - 1] * up % mod) * down % mod;
            ret += (neg && tmp) ? (mod - tmp) : (tmp);
            ret = (ret >= mod) ? (ret - mod) : ret;
            now = now * (x - i) % mod;
            neg ^= 1;
        }
        return ret;
    }
};

int main() {
    int n; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    Lagrange L;
    L.construct_inv_fac();
    L.init(v);
    int x; cin >> x;
    cout << L.sample(x);
}
