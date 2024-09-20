/*
可以在有 n 個點的簡單多邊形內，用 O(n) 的時間回傳：
1: 在多邊形內, 0: 在多邊形上, -1: 在多邊形外
*/
const int MAX_POS = 1e9+5; // [記得修改] 座標的最大值
int in_polygon(vector<point> &v, point a){
	int c = v.size();
    v.push_back(v[0]); // 已經用好循環了
    point b = {MAX_POS, a.y+1};
    int cnt = 0;
 
    for (int i=0 ; i<n ; i++){
        if (in(v[i], v[i+1], a)) return 0;
        if (banana(a, b, v[i], v[i+1])) cnt++;
    }
 
    return cnt%2 ? 1 : -1;
}