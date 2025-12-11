const int inf = 1e18;
class SegmentTree {
private:
#define lc x * 2 + 1
#define rc x * 2 + 2
    int n;
    const vector<int>& data;
    vector<int> sum, mx, smx, mxcnt, lz;
    void apply(int x, int v) {
        if (v >= mx[x]) return;
        sum[x] += (v - mx[x]) * mxcnt[x];
        mx[x] = v;
        chmin(lz[x], v);
    }
    void push(int x, int lx, int rx) {
        if (lx + 1 >= rx) return;
        if (lz[x] != inf) {
            int v = lz[x];
            if (mx[lc] > v) apply(lc, v);
            if (mx[rc] > v) apply(rc, v);
            lz[x] = inf; 
        }
    }
    void pull(int x) {
        sum[x] = sum[lc] + sum[rc];
        if (mx[lc] == mx[rc]) {
            mx[x] = mx[lc];
            mxcnt[x] = mxcnt[lc] + mxcnt[rc];
            smx[x] = max(smx[lc], smx[rc]);
        } else if (mx[lc] > mx[rc]) {
            mx[x] = mx[lc];
            mxcnt[x] = mxcnt[lc];
            smx[x] = max(smx[lc], mx[rc]);
        } else {
            mx[x] = mx[rc];
            mxcnt[x] = mxcnt[rc];
            smx[x] = max(mx[lc], smx[rc]);
        }
    }
    void build(int x, int lx, int rx) {
        lz[x] = inf; 
        if (lx + 1 == rx) {
            sum[x] = mx[x] = data[lx];
            smx[x] = -inf; 
            mxcnt[x] = 1;
            return;
        }
        int mid = (lx + rx) / 2;
        build(lc, lx, mid);
        build(rc, mid, rx);
        pull(x);
    }
    void upd_mn(int x, int lx, int rx, int l, int r, int v) {
        if (v >= mx[x]) return;
        if (lx >= l and rx <= r) {
            if (v > smx[x]) {
                apply(x, v);
                return;
            }
        }
        push(x, lx, rx);
        int mid = (lx + rx) / 2;
        if (l < mid) upd_mn(lc, lx, mid, l, r, v);
        if (r > mid) upd_mn(rc, mid, rx, l, r, v);
        pull(x);
    }
    int qsum(int x, int lx, int rx, int l, int r) {
        if (lx >= l and rx <= r) return sum[x];
        push(x, lx, rx);
        int mid = (lx + rx) / 2;
        int res = 0;
        if (l < mid) res += qsum(lc, lx, mid, l, r);
        if (r > mid) res += qsum(rc, mid, rx, l, r);
        return res;
    }
#undef lc
#undef rc
public:
    SegmentTree(const vector<int> v) : n(v.size()), data(v) {
        if (n == 0) return;
        sum.resize(4 * n);
        mx.resize(4 * n); smx.resize(4 * n);
        mxcnt.resize(4 * n); lz.resize(4 * n);
        build(0, 0, n);
    }
    void upd_mn(int l, int r, int v) {
        if (l >= r or l >= n or r <= 0) return;
        upd_mn(0, 0, n, l, r, v);
    }
    int qsum(int l, int r) {
        if (l >= r or l >= n or r <= 0) return 0;
        return qsum(0, 0, n, l, r);
    }
};