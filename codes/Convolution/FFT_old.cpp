typedef complex<double> cd;
const double PI = acos(-1);

void FFT(vector<cd> &a, bool inv){

    int n = a.size();

    for (int i=1, j=0 ; i<n ; i++){
        int bit = (n>>1);
        for ( ; j&bit ; bit>>=1){
            j ^= bit;
        }
        j ^= bit;
        if (i<j){
            swap(a[i], a[j]);
        }
    }

    for (int len=2 ; len<=n ; len<<=1){
        cd wlen = polar(1.0, (inv ? 2 : -2)*PI/len);

        for (int i=0 ; i<n ; i+=len){
            cd w(1);
            for (int j=0 ; j<len/2 ; j++){
                cd u = a[i+j];
                cd v = a[i+j+len/2]*w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= wlen;
            }
        }
    }

    if (inv){
        for (auto &x : a){
            x /= n;
        }
    }
    
    return;
}

vector<cd> polyMul(vector<cd> a, vector<cd> b){
    int sa = a.size(), sb = b.size(), n = 1;

    while (n<sa+sb-1) n *= 2;
    a.resize(n);
    b.resize(n);
    vector<cd> c(n);

    FFT(a, 0);
    FFT(b, 0);
    for (int i=0 ; i<n ; i++) c[i] = a[i]*b[i];
    FFT(c, 1);

    c.resize(sa+sb-1);

    return c;
}