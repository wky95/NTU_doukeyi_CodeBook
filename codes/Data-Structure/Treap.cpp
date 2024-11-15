struct Treap{
    Treap *l = nullptr, *r = nullptr;
    int pri = rand(), val = 0, sz = 1;
 
    Treap(int _val){
        val = _val;
    }
};
 
int size(Treap *t){return t ? t->sz : 0;}
void pull(Treap *t){
    t->sz = size(t->l)+size(t->r)+1;
}
 
Treap* merge(Treap *a, Treap *b){
    if (!a || !b) return a ? a : b;

    if (a->pri>b->pri){
        a->r = merge(a->r, b);
        pull(a);
        return a;
    }else{
        b->l = merge(a, b->l);
        pull(b);
        return b;
    }
 
}
 
pair<Treap*, Treap*> split(Treap *&t, int k){ // 1-based <前 k 個元素, 其他元素>
    if (!t) return {};
    if (size(t->l)>=k){
        auto pa = split(t->l, k);
        t->l = pa.second;
        pull(t);
        return {pa.first, t};
    }else{
        auto pa = split(t->r, k-size(t->l)-1);
        t->r = pa.first;
        pull(t);
        return {t, pa.second};
    }
}

// functions
Treap* build(vector<int> v){
    Treap* ret;
    for (int i=0 ; i<SZ(v) ; i++){
        ret = merge(ret, new Treap(v[i]));
    }
    return ret;
}

array<Treap*, 3> cut(Treap *t, int l, int r){ // 1-based <前 1~l-1 個元素, l~r 個元素, r+1 個元素>
    array<Treap*, 3> ret;
    tie(ret[1], ret[2]) = split(t, r);
    tie(ret[0], ret[1]) = split(ret[1], l-1);
    return ret;
}

void print(Treap *t, bool flag = true){
    if (t->l!=0) print(t->l, false);
    cout << t->val;
    if (t->r!=0) print(t->r, false);
    if (flag) cout << endl;
}