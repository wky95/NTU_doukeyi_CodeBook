// priority_queue，務必檢查相等的 case，給所有元素一個排序的依據
struct cmp{
    bool operator () (Data a, Data b){
        return a.x<b.x;
    }
};
priority_queue<Data, vector<Data>, cmp> pq;

// set，務必檢查相等的 case，給所有元素一個排序的依據
auto cmp = [](int a, int b) {
    return a > b;
};
set<int, decltype(cmp)> s = {1, 2, 3, 4, 5};
cout << *s.begin() << '\n';