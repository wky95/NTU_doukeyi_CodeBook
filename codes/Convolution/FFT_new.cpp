typedef complex<double> cd;

// b9c90a
void FFT(vector<cd> &a) {
    int n = a.size(), L = 31-__builtin_clz(n);
    vector<complex<long double>> R(2, 1);
    vector<cd> rt(2, 1);
    for (int k=2 ; k<n ; k*=2){
        R.resize(n);
        rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        for (int i=k ; i<2*k ; i++){
            rt[i] = R[i] = (i&1 ? R[i/2]*x : R[i/2]);
        }
    }

    vector<int> rev(n);
    for (int i=0 ; i<n ; i++){
        rev[i] = (rev[i/2] | (i&1)<<L)/2;
    }
    for (int i=0 ; i<n ; i++){
        if (i<rev[i]) swap(a[i], a[rev[i]]);
    }
    for (int k=1 ; k<n ; k*=2){
        for (int i=0 ; i<n ; i+=2*k){
            for (int j=0 ; j<k ; j++){
                auto x = (double *)&rt[j+k];
                auto y = (double *)&a[i+j+k];
                cd z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);
                a[i+j+k] = a[i+j]-z;
                a[i+j] += z;
            }
        }
    }
    return;
}

// 39029d
vector<double> PolyMul(const vector<double> a, const vector<double> b){
    if (a.empty() || b.empty()) return {};
    vector<double> res(a.size()+b.size()-1);
    int L = 32 - __builtin_clz(res.size()), n = 1 << L;
    vector<cd> in(n), out(n);

    copy(a.begin(), a.end(), begin(in));
    for (int i=0 ; i<b.size() ; i++){
        in[i].imag(b[i]);
    }
    FFT(in);
    for (cd& x : in) x *= x;
    for (int i=0 ; i<n ; i++){
        out[i] = in[-i & (n - 1)] - conj(in[i]);
    }
    FFT(out);

    for (int i=0 ; i<res.size() ; i++){
        res[i] = imag(out[i]) / (4 * n);
    }

    return res;
}