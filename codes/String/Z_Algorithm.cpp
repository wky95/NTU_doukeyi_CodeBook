// 定義一個長度為 n 的文本為 T ，則陣列 Z 的 Z[i] 代表 T[0:n] 和 T[i:n] 最長共同前綴
// bcfbd6
vector<int> z_function(string s){
    vector<int> ret(s.size());
    int ll = 0, rr = 0;

    for (int i=1 ; i<s.size() ; i++){
        int j = 0;

        if (i<rr) j = min(ret[i-ll], rr-i);
        while (s[j]==s[i+j]) j++;
        ret[i] = j;

        if (i+j>rr){
            ll = i;
            rr = i+j;
        }
    }

    ret[0] = s.size();
    return ret;
}
