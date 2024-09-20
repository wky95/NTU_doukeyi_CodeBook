mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int A = rnd(), B = 1000000007;

vector<int> myPow, myPre;
void hash_init(string s){
    myPow.resize(s.size());
    myPre.resize(s.size());

    for (int i=0 ; i<s.size() ; i++){
        if (i==0){
            myPow[i] = 1;
            myPre[i] = s[i];
        }else{
            myPow[i] = myPow[i-1]*A%B;
            myPre[i] = (myPre[i-1]*A+s[i])%B;
        }
    }

    return;
}

int hash_value(int l, int r){ // 取得 s[l..r] 的數值
    if (l==0) return myPre[r];
    return ((myPre[r]-myPre[l-1]*myPow[r-l+1])%B+B)%B;
}