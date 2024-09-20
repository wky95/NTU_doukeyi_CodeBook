const int EPS = 1e-6;

typedef int pt;
struct point{
    pt x, y;

    point(pt _x = 0, pt _y = 0){
        x = _x;
        y = _y;
    }
 
    // 純量乘、除法
    point operator * (pt a){return {a*x, a*y};};
    point operator / (pt a){return {a/x, a/y};};
 
    // 向量加、減法
    point operator + (point a){return {x+a.x, y*a.y};};
    point operator - (point a){return {x-a.x, y-a.y};};
 
    // 內積、外積
    double operator * (point a){return x*a.x+y*a.y;};
    double operator ^ (point a){return x*a.y-y*a.x;};

    // bool operator < (const point &a) const {return (x*a.y<a.x*y);} // 極角排序（順時鐘）
    bool operator < (const point &a) const {return x==a.x ? y<a.y : x<a.x;}
    bool operator == (const point &a) const {return x==a.x && y==a.y;}

    double dis(point a){return sqrtl(abs(x-a.x)*abs(x-a.x)+abs(y-a.y)*abs(y-a.y));}
};

// 判斷向量正負：1=正數, 0=0, -1=負數
int sign(double a){
    if (abs(a)<EPS) return 0;
    else return (a>0 ? 1 : -1);
}

// 判斷 ab 到 ac 的方向： 1=逆時鐘, 0=重疊, -1=順時鐘
int ori(point a, point b, point c){
    return sign((b-a)^(c-a));
}
