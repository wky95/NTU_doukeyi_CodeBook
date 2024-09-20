// priority_queue
struct cmp{
    bool operator () (Data a, Data b){
        return a.x<b.x;
    }
};
priority_queue<Data, vector<Data>, cmp> pq;

// set
struct Data{
    int x;

    bool operator < (const Data &b){
        return x<b.x;
    }
};