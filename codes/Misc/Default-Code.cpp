#include <bits/stdc++.h>
#define int long long
#define fastio ios::sync_with_stdio(0), cin.tie(0);
using namespace std;

#ifdef LOCAL
void debug(){cerr << "\n";}
template<class T, class ... U>
void debug(T a, U ... b){cerr << a << " ", debug(b...);}
template<class T> void pary(T l, T r){
    while (l!=r) cerr << *l << " ", l++;
    cerr << "\n";
}
#else
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt")
#define debug(...) void()
#define pary(...) void()
#endif

const int MAX_N = 5e5+10;
const int INF = 2e18;

int n, tmp;
vector<int> v;

void solve1(){

    return;
}

signed main(){

    fastio;

    int t = 1;
    while (t--){
        solve1();
    }

    return 0;
}