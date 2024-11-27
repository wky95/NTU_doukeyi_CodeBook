const int EPS = 1e-6;

struct Point{
    Point x, y;

    Point(Point _x = 0, Point _y = 0){
        x = _x;
        y = _y;
    }
 
    // 純量乘、除法
    Point operator * (Point a){return {a*x, a*y};};
    Point operator / (Point a){return {a/x, a/y};};
 
    // 向量加、減法
    Point operator + (Point a){return {x+a.x, y*a.y};};
    Point operator - (Point a){return {x-a.x, y-a.y};};
 
    // 內積、外積
    double operator * (Point a){return x*a.x+y*a.y;};
    double operator ^ (Point a){return x*a.y-y*a.x;};

    // bool operator < (const Point &a) const {return (x*a.y<a.x*y);} // 極角排序（順時鐘）
    bool operator < (const Point &a) const {return x==a.x ? y<a.y : x<a.x;}
    bool operator == (const Point &a) const {return x==a.x && y==a.y;}

    double dis(Point a){return sqrtl(abs(x-a.x)*abs(x-a.x)+abs(y-a.y)*abs(y-a.y));}
};

// 判斷向量正負：1=正數, 0=0, -1=負數
int sign(double a){
    if (abs(a)<EPS) return 0;
    else return (a>0 ? 1 : -1);
}

// 判斷 ab 到 ac 的方向： 1=逆時鐘, 0=重疊, -1=順時鐘
int ori(Point a, Point b, Point c){
    return sign((b-a)^(c-a));
}
