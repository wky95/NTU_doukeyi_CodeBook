// z[i] 回傳 s[0...] 跟 s[i...] 的 lcp, z[0] = 0
vector<int> z_function(string s){
    vector<int> z(s.size());
    int l = -1, r = -1;
    for (int i=1 ; i<s.size() ; i++){
        z[i] = i>=r ? 0 : min(r-i, z[i-l]);
        while (i+z[i]<s.size() && s[i+z[i]]==s[z[i]]) z[i]++;
        if (i+z[i]>r) l=i, r=i+z[i];
    }
    return z;
}