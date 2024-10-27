// 注意，當 |s|=1 時，lcp 不會有值，務必測試 |s|=1 的 case
struct SuffixArray {
    vector<int> sa, lcp;
    SuffixArray(string& s, int lim = 256) {
        // 49c4d2
        int n = SZ(s)+1, k = 0, a, b;
        vector<int> x(ALL(s)), y(n), ws(max(n, lim)), rank(n);
        x.push_back(0);
        sa = lcp = y;
        iota(ALL(sa), 0);
        for (int j=0, p=0 ; p<n ; j=max(1LL, j*2), lim=p) {
            p = j;
            iota(ALL(y), n-j);
            for (int i=0 ; i<n ; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
            fill(ALL(ws), 0);
            for (int i=0 ; i<n ; i++) ws[x[i]]++;
            for (int i=1 ; i<lim ; i++) ws[i] += ws[i - 1];
            for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            for (int i=1 ; i<n ; i++){
                a = sa[i - 1];
                b = sa[i];
                x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
            }
        }

        // 7181dd
        for (int i=1 ; i<n ; i++) rank[sa[i]] = i;
        for (int i=0, j ; i<n-1 ; lcp[rank[i++]]=k)
            for (k && k--, j=sa[rank[i]-1] ; i+k<SZ(s) && j+k<SZ(s) && s[i+k]==s[j+k] ; k++);
        sa.erase(sa.begin());
        lcp.erase(lcp.begin(), lcp.begin()+2);
    }
};
