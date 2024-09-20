int qp(int b, int p, int m = MOD){
    int ret = 1;
    for ( ; p ; p>>=1){
        if (p&1) ret = ret*b%m;
        b = b*b%m;
    }
    return ret;
}