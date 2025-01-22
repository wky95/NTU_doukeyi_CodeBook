// 給一個字串 S，定義函數 \pi(i) = k 代表 S[1 ... k] = S[i-k+1 ... i]（最長真前後綴）
// e5b7ce
vector<int> KMP(string &s){
    int n = s.size();
    vector<int> ret(n);
    for (int i=1 ; i<n ; i++){
        int j = ret[i-1];
        while (j>0 && s[i]!=s[j]) j = ret[j-1];
        j += (s[i]==s[j]);
        ret[i] = j;
    }
    return ret;
}