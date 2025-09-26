/*Tested: https://judge.yosupo.jp/submission/316309
Write by: temmie*/
const int B = 27;
string p;
for (int i=0 ; i<B ; i++) p += ('a'+i);
p += '*';
vector<vector<double>> res(B);
for (int i=0 ; i<B ; i++){
    vector<double> ss, tt;
    for (auto x : s) ss.push_back(x==p[i] || x=='*');
    for (auto x : t) tt.push_back(x==p[i] || x=='*');
    reverse(tt.begin(), tt.end());
    res[i] = PolyMul(ss, tt);
}
for (int i=t.size()-1 ; i+t.size()-1<res[0].size() ; i++){
    int total = 0;
    for (int j=0 ; j<B-1 ; j++) total += (int)abs(round(res[j][i]));
    total -= 25*(int)abs(round(res[26][i]));
    cout << (total==t.size());
}