int extgcd(int a, int b, int &x, int &y){
    if (b==0){
        x=1, y=0;
        return a;
    }

    int ret=extgcd(b, a%b, y, x);
    y-=a/b*x;
    return ret;
}

// 對於方程組的式子兩兩求解
// {是否有解, {a, m}}
pair<bool, pair<int, int>> CRT(int a1, int m1, int a2, int m2){
    int g=__gcd(m1, m2);
    if ((a2-a1)%g!=0) return {0, {-1, -1}};

    int x, y;
    extgcd(m1, m2, x, y);

    x=(a2-a1)*x/g; // 兩者不能相反
    a1=x*m1+a1;
    m1=m1*m2/g;
    a1=(a1%m1+m1)%m1;
    return {1, {a1, m1}};
}