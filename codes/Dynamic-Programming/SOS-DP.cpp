// 總時間複雜度為 O(n 2^n)
// 計算 dp[i] = i 所有 bit mask 子集的和
for (int i=0 ; i<n ; i++){
	for (int mask=0 ; mask<(1<<n) ; mask++){
		if ((mask>>i)&1){
			dp[mask] += dp[mask^(1<<i)];
		}
	}
}