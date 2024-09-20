const int MAX_N = 5e5;

// lpf[i] = i 的最小質因數
vector<int> prime, lpf(MAX_N);

void prime_init(){
    for (int i=2 ; i<MAX_N ; i++){
        if (lpf[i]==0){
            lpf[i]=i;
            prime.push_back(i);
        }

        for (int j : prime){
            if (i*j>=MAX_N) break;
            lpf[i*j]=j;
            if (lpf[i]==j) break;
        }
    }
}