/*
時間複雜度為 O(sqrt(n))
區間為 [l, r]
*/
for(int i=1 ; i<=n ; i++){
    int l = i, r = n/(n/i);
    i = r;
    ans.push_back(r);
}