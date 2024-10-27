vector<int> a, m;

int extgcd(int a, int b, int &x, int &y){
    if (b==0){
        x=1, y=0;
        return a;
    }

    int ret=extgcd(b, a%b, y, x);
    y-=a/b*x;
    return ret;
}

// n = 有幾個式子，求解 x \equiv a_i \bmod m_i
int CRT(int n, vector<int> &a, vector<int> &m){
    int p=1, ans=0;

    vector<int> M(n), inv_M(n);

    for (int i=0 ; i<n ; i++) p*=m[i];
    for (int i=0 ; i<n ; i++){
        M[i]=p/m[i];
		int tmp;
        extgcd(M[i], m[i], inv_M[i], tmp);
        ans+=a[i]*inv_M[i]*M[i];
        ans%=p;
    }

    return (ans%p+p)%p;
}
