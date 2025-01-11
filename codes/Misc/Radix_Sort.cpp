// 值域限制：0 ~ 1073741823(2^30-1)
inline void radix_sort(vector<int> &a, int n){
    static int cnt[32768] = {0};
    vector<int> tmpa(n);
    for(int i = 0; i < n; ++i)
        ++cnt[a[i] & 32767];
    for(int i = 1; i < 32768; ++i)
        cnt[i] += cnt[i-1];
    static int temp;
    for(int i = n-1; i >= 0; --i){
        temp = a[i] & 32767;
        --cnt[temp];
        tmpa[cnt[temp]] = a[i];
    }

    static int cnt2[32768] = {0};
    for(int i = 0; i < n; ++i)
        ++cnt2[(tmpa[i]>>15)];
    for(int i = 1; i < 32768; ++i)
        cnt2[i] += cnt2[i-1];

    for(int i = n-1; i >= 0; --i){
        temp = (tmpa[i]>>15);
        --cnt2[temp];
        a[cnt2[temp]] = tmpa[i];
    }
    return;
}