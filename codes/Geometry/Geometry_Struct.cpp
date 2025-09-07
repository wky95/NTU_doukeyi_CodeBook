using ld = double;

// 判斷數值正負：{1:正數,0:零,-1:負數}
int sign(long long x) {return (x >= 0) ? ((bool)x) : -1; }
int sign(ld x) {return (abs(x) < 1e-9) ? 0 : (x>0 ? 1 : -1);}

template<typename T>
struct point {
    T x, y;
    point() {}
    point(const T &x, const T &y) : x(x), y(y) {}
    explicit operator point<ld>() {return point<ld>(x, y); }
    // A [6357c4]
    point operator+(point b) {return {x+b.x, y+b.y}; }
    point operator-(point b) {return {x-b.x, y-b.y}; }
    point operator*(T b) {return {x*b, y*b}; }
    point operator/(T b) {return {x/b, y/b}; }
    bool operator==(point b) {return x==b.x && y==b.y; }

    T operator*(point b) {return x * b.x + y * b.y; }
    T operator^(point b) {return x * b.y - y * b.x; }
    // B [c415da]
    // 逆時針極角排序
    bool side() const{return (y == 0) ? (x > 0) : (y < 0); }
    bool operator<(const point &b) const {
        return side() == b.side() ?
            (x*b.y > b.x*y) : side() < b.side();
    }
    friend ostream& operator<<(ostream& os, point p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
    // 判斷 ab 到 ac 的方向：{1:逆時鐘,0:重疊,-1:順時鐘}
    friend int ori(point a, point b, point c) {
        return sign((b-a)^(c-a));
    }
    friend bool btw(point a, point b, point c) {
        return ori(a, b, c) == 0 && sign((a-c)*(b-c)) <= 0;
    }
    // 判斷線段 ab, cd 是否相交
    friend bool banana(point a, point b, point c, point d) {
        if (btw(a, b, c) || btw(a, b, d)
            || btw(c, d, a) || btw(c, d, b)) return true;
        int u = ori(a, b, c) * ori(a, b, d);
        int v = ori(c, d, a) * ori(c, d, b);
        return u < 0 && v < 0;
    } // C [09fd7c]
    // 判斷 "射線 ab" 與 "線段 cd" 是否相交
    friend bool rayHitSeg(point a,point b,point c,point d) {
        if (a == b) return btw(c, d, a); // Special case
        if (((a - b) ^  (c - d)) == 0) {
            return btw(a, c, b) || btw(a, d, b) || banana(a, b, c, d);
        }
        point u = b - a, v = d - c, s = c - a;
        return sign(s ^ v) * sign(u ^ v) >= 0 && sign(s ^ u)
             * sign(u ^ v) >= 0 && abs(s ^ u) <= abs(u ^ v);
    } // D [db541a]
    // 旋轉 Arg(b) 的角度（小心溢位）
    point rotate(point b){return {x*b.x-y*b.y, x*b.y+y*b.x};}
    // 回傳極座標角度，值域：[-π, +π]
    friend ld Arg(point b) {
        return (b.x != 0 || b.y != 0) ? atan2(b.y, b.x) : 0;
    }
    friend T abs2(point b) {return b * b; }
};

template<typename T>
struct line {
    /*--------------- E [683239] ---------------*/
    point<T> p1, p2;
    // ax + by + c = 0
    T a, b, c; // |a|, |b| ≤ 2C, |c| ≤ 8C²
    line() {}
    line(const point<T> &x,const point<T> &y) : p1(x), p2(y){
        build();
    }
    void build() {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = (-a*p1.x)-b*p1.y;
    } // E [683239]
    // 判斷點和有向直線的關係：{1:左邊,0:在線上,-1:右邊}
    int ori(point<T> &p) {
        return sign((p2-p1) ^ (p-p1));
    }
    // 判斷直線斜率是否相同
    bool parallel(line &l) {
        return ((p1-p2) ^ (l.p1-l.p2)) == 0;
    }
    // 兩直線交點
    point<ld> line_intersection(line &l) {
        using P = point<ld>;
        point<T> u = p2-p1, v = l.p2-l.p1, s = l.p1-p1;
        return P(p1) + P(u) * ((ld(s^v)) / (u^v));
    }
};

template<typename T>
struct polygon {
    vector<point<T>> v;
    polygon() {}
    polygon(const vector<point<T>> &u) : v(u) {}
    // simple 為 true 的時候會回傳任意三點不共線的凸包
    void make_convex_hull(int simple) {
        auto cmp = [&](point<T> &p, point<T> &q) {
            return (p.x == q.x) ? (p.y < q.y) : (p.x < q.x);
        };
        simple = (bool)simple;
        sort(v.begin(), v.end(), cmp);
        v.resize(unique(v.begin(), v.end()) - v.begin());
        if (v.size() <= 1) return;
        vector<point<T>> hull;
        for (int t = 0; t < 2; ++t){
            int sz = hull.size();
            for (auto &i:v) {
                while (hull.size() >= sz+2 && ori(hull[hull.
                      size()-2], hull.back(), i) < simple) {
                    hull.pop_back();
                }
                hull.push_back(i);
            }
            hull.pop_back();
            reverse(v.begin(), v.end());
        }
        swap(hull, v);
    } // F [2bb3ef]
//  可以在有 n 個點的簡單多邊形內，用 O(n) 判斷一個點：
//  {1 : 在多邊形內, 0 : 在多邊形上, -1 : 在多邊形外}
    int in_polygon(point<T> a){
        const T MAX_POS = 1e9 + 5; // [記得修改] 座標的最大值
        point<T> pre = v.back(), b(MAX_POS, a.y + 1);
        int cnt = 0;

        for (auto &i:v) {
            if (btw(pre, i, a)) return 0;
            if (banana(a, b, pre, i)) cnt++;
            pre = i;
        }

        return cnt%2 ? 1 : -1;
    } // G [f11340]
/// 警告：以下所有凸包專用的函式都只接受逆時針排序且任三點不共線的凸包 ///
//  可以在有 n 個點的凸包內，用 O(log n) 判斷一個點：
//  {1 : 在凸包內, 0 : 在凸包邊上, -1 : 在凸包外}
    int in_convex(point<T> p) {
        int n = v.size();
        int a = ori(v[0], v[1], p), b = ori(v[0], v[n-1], p);
        if (a < 0 || b > 0) return -1;
        if (btw(v[0], v[1], p)) return 0;
        if (btw(v[0], v[n - 1], p)) return 0;
        int l = 1, r = n - 1, mid;
        while (l + 1 < r) {
            mid = (l + r) >> 1;
            if (ori(v[0], v[mid], p) >= 0) l = mid;
            else r = mid;
        }
        int k = ori(v[l], v[r], p);
        if (k <= 0) return k;
        return 1;
    } // H [e64f1e]
//  凸包專用的環狀二分搜，回傳 0-based index
    int cycle_search(auto &f) {
        int n = v.size(), l = 0, r = n;
        if (n == 1) return 0;
        bool rv = f(1, 0);
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (f(0, m) ? rv: f(m, (m + 1) % n)) r = m;
            else l = m;
        }
        return f(l, r % n) ? l : r % n;
    } // I [fe2f51]
//  可以在有 n 個點的凸包內，用 O(log n) 判斷一條直線：
//  {1 : 穿過凸包, 0 : 剛好切過凸包, -1 : 沒碰到凸包}
    int line_cut_convex(line<T> L) {
        L.build();
        point<T> p(L.a, L.b);
        auto gt = [&](int neg) {
            auto f = [&](int x, int y) {
                return sign((v[x] - v[y]) * p) == neg;
            };
            return -(v[cycle_search(f)] * p);
        };
        T x = gt(1), y = gt(-1);
        if (L.c < x || y < L.c) return -1;
        return not (L.c == x || L.c == y);
    } // J [b6a4c8]
//  可以在有 n 個點的凸包內，用 O(log n) 判斷一個線段：
//  {1 : 存在一個凸包上的邊可以把這個線段切成兩半,
//   0 : 有碰到凸包但沒有任何凸包上的邊可以把它切成兩半,
//  -1 : 沒碰到凸包}
/// 除非線段兩端點都不在凸包邊上，否則此函數回傳 0 的時候不一定表示線段沒有通過凸包內部 ///
    int segment_across_convex(line<T> L) {
        L.build();
        point<T> p(L.a, L.b);
        auto gt = [&](int neg) {
            auto f = [&](int x, int y) {
                return sign((v[x] - v[y]) * p) == neg;
            };
            return cycle_search(f);
        };
        int i = gt(1), j = gt(-1), n = v.size();
        T x = -(v[i] * p), y = -(v[j] * p);
        if (L.c < x || y < L.c) return -1;
        if (L.c == x || L.c == y) return 0;

        if (i > j) swap(i, j);
        auto g = [&](int x, int lim) {
            int now = 0, nxt;
            for (int i = 1 << __lg(lim); i > 0; i /= 2) {
                if (now + i > lim) continue;
                nxt = (x + i) % n;
                if (L.ori(v[x]) * L.ori(v[nxt]) >= 0) {
                    x = nxt;
                    now += i;
                }
            } //   ↓ BE CAREFUL
            return -(ori(v[x], v[(x + 1) % n], L.p1) * ori(v[x], v[(x + 1) % n], L.p2));
        };
        return max(g(i, j - i), g(j, n - (j - i)));
    } // K [b4f073]
//  可以在有 n 個點的凸包內，用 O(log n) 判斷一個線段：
//  {1 : 線段上存在某一點位於凸包內部（邊上不算）,
//   0 : 線段上存在某一點碰到凸包的邊但線段上任一點均不在凸包內部,
//  -1 : 線段完全在凸包外面}
    int segment_pass_convex_interior(line<T> L) {
        if (in_convex(L.p1) == 1 || in_convex(L.p2) == 1) return 1;
        L.build();
        point<T> p(L.a, L.b);
        auto gt = [&](int neg) {
            auto f = [&](int x, int y) {
                return sign((v[x] - v[y]) * p) == neg;
            };
            return cycle_search(f);
        };
        int i = gt(1), j = gt(-1), n = v.size();
        T x = -(v[i] * p), y = -(v[j] * p);
        if (L.c < x || y < L.c) return -1;
        if (L.c == x || L.c == y) return 0;

        if (i > j) swap(i, j);
        auto g = [&](int x, int lim) {
            int now = 0, nxt;
            for (int i = 1 << __lg(lim); i > 0; i /= 2) {
                if (now + i > lim) continue;
                nxt = (x + i) % n;
                if (L.ori(v[x]) * L.ori(v[nxt]) > 0) {
                    x = nxt;
                    now += i;
                }
            } //   ↓ BE CAREFUL
            return -(ori(v[x], v[(x + 1) % n], L.p1) * ori(v[x], v[(x + 1) % n], L.p2));
        };
        int ret = max(g(i, j - i), g(j, n - (j - i)));
        return (ret == 0) ? (in_convex(L.p1) == 0 && in_convex(L.p2) == 0) : ret;
    } // L [5f45ca]
//  回傳點過凸包的兩條切線的切點的 0-based index（不保證兩條切線的順逆時針關係）
    pair<int,int> convex_tangent_point(point<T> p) {
        int n = v.size(), z = -1, edg = -1;
        auto gt = [&](int neg) {
            auto check = [&](int x) {
                if (v[x] == p) z = x;
                if (btw(v[x], v[(x + 1) % n], p)) edg = x;
                if (btw(v[(x + n - 1) % n], v[x], p)) edg = (x + n - 1) % n;
            };
            auto f = [&](int x, int y) {
                check(x); check(y);
                return ori(p, v[x], v[y]) == neg;
            };
            return cycle_search(f);
        };
        int x = gt(1), y = gt(-1);
        if (z != -1) {
            return {(z + n - 1) % n, (z + 1) % n};
        }
        else if (edg != -1) {
            return {edg, (edg + 1) % n};
        }
        else {
            return {x, y};
        }
    } // M [a6f66b]
    friend int halfplane_intersection(vector<line<T>> &s, polygon<T> &P) {
        auto angle_cmp = [&](line<T> &A, line<T> &B) {
            point<T> a = A.p2-A.p1, b = B.p2-B.p1;
            return (a < b);
        };
        sort(s.begin(), s.end(), angle_cmp); // 線段左側為該線段半平面
        int L, R, n = s.size();
        vector<point<T>> px(n);
        vector<line<T>> q(n);
        q[L = R = 0] = s[0];
        for(int i = 1; i < n; ++i) {
            while(L < R && s[i].ori(px[R-1]) <= 0) --R;
            while(L < R && s[i].ori(px[L])   <= 0) ++L;
            q[++R] = s[i];
            if(q[R].parallel(q[R-1])) {
                --R;
                if(q[R].ori(s[i].p1) > 0) q[R] = s[i];
            }
            if(L<R) px[R-1] = q[R-1].line_intersection(q[R]);
        }
        while(L < R && q[L].ori(px[R-1]) <= 0) --R;
        P.v.clear();
        if(R - L <= 1) return 0;
        px[R] = q[R].line_intersection(q[L]);
        for(int i = L; i <= R; ++i) P.v.push_back(px[i]);
        return R - L + 1;
    } // N [102d48]
};

struct Cir {
    point<ld> o; ld r;
    friend ostream& operator<<(ostream& os, Cir c) {
        return os << "(x" << "+-"[c.o.x >= 0] << abs(c.o.x) << ")^2 + (y" << "+-"[c.o.y >= 0] << abs(c.o.y) << ")^2 = " << c.r * c.r;
    }
    bool covers(Cir b) {
        return sqrt((ld)abs2(o - b.o)) + b.r <= r;
    }
    vector<point<ld>> Cir_intersect(Cir c) {
        ld d2 = abs2(o - c.o), d = sqrt(d2);
        if (d < max(r, c.r) - min(r, c.r) || d > r + c.r) return {};
        auto sqdf = [&](ld x, ld y) { return x*x - y*y; };
        point<ld> u = (o + c.o) / 2 + (o - c.o) * (sqdf(c.r, r) / (2 * d2));
        ld A = sqrt(sqdf(r + d, c.r) * sqdf(c.r, d - r));
        point<ld> v = (c.o - o).rotate({0,1}) * A / (2 * d2);
        if (sign(v.x) == 0 && sign(v.y) == 0) return {u};
        return {u - v, u + v};
    } // O [330a1c]
};
