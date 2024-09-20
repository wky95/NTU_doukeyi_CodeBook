/*
s = temmie
pos = 6 5 1 4 3 2 0 
rnk = 6 2 5 4 3 1 0 

pos:
(空字串) -> e -> emmie -> ie -> mie -> mmie -> temmie

rnk[i] = i 在 pos 的哪個位置（第幾小的陣列）
*/

vector<int> pos, rnk;

void Radix_Sort(vector<array<int, 3>> &v){
    int n = v.size();
    
    for (int p=1 ; p>=0 ; p--){
        vector<int> cnt(n);
        for (auto x : v){
            cnt[x[p]]++;
        }

        vector<array<int, 3>> tmp(n);
        vector<int> ptr(n); // ptr[i] = 目前 second 是 i 的元素要放在哪個位置
        ptr[0] = 0;
        for (int i=1 ; i<n ; i++){
            ptr[i] = ptr[i-1]+cnt[i-1];
        }
        for (auto x : v){
            int i = x[p];
            tmp[ptr[i]] = x;
            ptr[i]++;
        }
        v = tmp;
    }
    return;
}

void Build_SA(string s){
    s += '$';
    int n = s.size();
    rnk.resize(n);
    pos.resize(n);

    vector<array<int, 2>> tmp(n);
    for (int i=0 ; i<n ; i++) tmp[i] = {s[i], i};
    sort(tmp.begin(), tmp.end());
    for (int i=0 ; i<n ; i++) pos[i] = tmp[i][1];
    rnk[pos[0]] = 0;
    for (int i=1 ; i<n ; i++){
        if (tmp[i][0]==tmp[i-1][0]) rnk[pos[i]] = rnk[pos[i-1]];
        else rnk[pos[i]] = rnk[pos[i-1]]+1;
    }
    
    for (int k=0 ; (1<<k)<n ; k++){
        vector<array<int, 3>> tmp(n);
        for (int i=0 ; i<n ; i++) tmp[i] = {rnk[i], rnk[(i+(1<<k))%n], i};
        Radix_Sort(tmp);
        for (int i=0 ; i<n ; i++) pos[i] = tmp[i][2];
        rnk[pos[0]] = 0;
        for (int i=1 ; i<n ; i++){
            if (tmp[i][0]==tmp[i-1][0] && tmp[i][1]==tmp[i-1][1]) rnk[pos[i]] = rnk[pos[i-1]];
            else rnk[pos[i]] = rnk[pos[i-1]]+1;
        }
    }
}