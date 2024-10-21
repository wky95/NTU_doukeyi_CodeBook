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
int k_th(int k){ // 回傳 BIT 中第 k 小的元素（based-1）
    int res = 0;
    for (int i=MAX_N>>1 ; i>=1 ; i>>=1)
        if (bit[res+i]<k)
            k -= bit[res+=i];
    return res+1;
}