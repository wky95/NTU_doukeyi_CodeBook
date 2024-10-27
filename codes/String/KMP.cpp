// 給一個字串 S，定義函數 \pi(i) = k 代表 S[1 ... k] = S[i-k+1 ... i]
// 4c61a3
vector<int> KMP(string &s){
    n = SZ(s);
    vector<int> ret(n);
    int now = 0;
    for (int i=1 ; i<n ; i++){
        int j = ret[i-1];
        while (j>0 && s[i]!=s[j]){
            j = ret[j-1];
        }
        if (s[i]==s[j]) j++;
        ret[i] = j;
    }
    return ret;
}
