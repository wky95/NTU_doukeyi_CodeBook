
/*
rnk: 
(空字串) -> e -> emmie -> ie -> mie -> mmie -> temmie

lcp[i] = 第 i 小的後綴跟 i-1 小的後綴的 lcp（based-1）
[（無意義, -1）, 0, 1, 0, 0, 1, 0]
*/
vector<int> pos, rnk;
vector<int> lcp;

void Build_LCP(string s){
    int n = s.size();
    s += '$';
    lcp.resize(s.size());
    lcp[0] = -1;
    
    int k = 0;
    for(int i=0 ; i<n ; i++){
        int pi = rnk[i];
        int j = pos[pi-1];

        while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;

        lcp[pi] = k;
        k = max((int)0, k-1);
    }
}