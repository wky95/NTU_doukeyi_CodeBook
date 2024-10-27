// 9d296f
int minRotation(string s) {
    int a=0, N=SZ(s); s += s;
    for (int b=0 ; b<N ; b++){
        for (int k=0 ; k<N ; k++){
            if (a+k == b || s[a+k] < s[b+k]) {b += max(0LL, k-1); break;}
            if (s[a+k] > s[b+k]) { a = b; break; }
        }
    }
    return a;
}