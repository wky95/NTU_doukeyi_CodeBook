struct Treap{
    Treap *l, *r;
    int pri, val, sz;
 
    Treap(int _val){
        l = nullptr;
        r = nullptr;
        pri = rand();
        val = _val;
        sz = 1;
    }
} *root;
 
int size(Treap *a){
    return a ? a->sz : 0;
}
 
void pull(Treap *t){
    t->sz = size(t->l)+size(t->r)+1;
}
 
Treap *merge(Treap *a, Treap *b){
    // 如果一個為空，就回傳另一個
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
 
void split(Treap *&t, int k, Treap *&a, Treap *&b){
    // 如果樹為空就直接返回
    if (!t) a = b = nullptr;

    else if (size(t->l)+1<=k){ // 用 k 分割 treap
        // 如果以左子節點為根 + 目前節點合法：
        a = t;
        split(t->r, k-size(t->l)-1, a->r, b);
        pull(a);
    }else{
        b = t;
        split(t->l, k, a, b->l);
        pull(b);
    }
}
 
ostream & operator << (ostream &os, Treap *t){
    if (t==0) return os;
    os << t->l;
    os << (char)t->val;
    os << t->r;
    return os;
}
 
void print(Treap *t){
    if (t->l!=0) print(t->l);
    cout << (char)t->val;
    if (t->r!=0) print(t->r);
}