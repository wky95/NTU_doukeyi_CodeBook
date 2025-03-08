// 回傳 s 所有子字串（完全不同）中，第 k 大的
string k_th_substring(string &s, int k){
    int n = s.size();
    SuffixArray sa(s);
    sa.init_lcp();
 
    int prePrefix = 0, nowRank = 0;
    for (int i=0 ; i<n ; i++){
        int len = n-sa[i];
        int add = len-prePrefix;
 
        if (nowRank+add>=k){
            return s.substr(sa[i], prePrefix+k-nowRank);
        }
 
        prePrefix = sa.lcp[i];
        nowRank += add;
    }
}