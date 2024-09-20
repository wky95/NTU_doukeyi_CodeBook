vector<int> BIT(MAX_SIZE);
void update(int pos, int val){
	for (int i=pos ; i<MAX_SIZE ; i+=i&-i){
		BIT[i]+=val;
	}
}

int query(int pos){
	int ret=0;
	for (int i=pos ; i>0 ; i-=i&-i){
		ret+=BIT[i];
	}
	return ret;
}

// const int MAX_N = (1<<20)
// const int LOG_N = 20;
int k_th(int k){ // 回傳 BIT 中第 k 小的元素（based-1）
	int target = k-1, now = 0;
    for (int i=LOG_N-1 ; i>=0 ; i--){
        if (BIT[now+(1<<i)]<=k){
            k -= BIT[now+(1<<i)];
            now += 1<<i;
        }
    }
    return now+1;
}