// c 是否在 ab 裡面
bool in(point a, point b, point c){
    if (ori(a, b, c)) return 0;
    return sign((a-c)*(b-c))<=0;
}

// 判斷 ab 是否跟 cd 相交 
bool banana(point a, point b, point c, point d){
    int s1=ori(a, b, c);
    int s2=ori(a, b, d);
    int s3=ori(c, d, a);
    int s4=ori(c, d, b);
    if (in(a, b, c) || in(a, b, d) || in(c, d, a) || in(c, d, b)) return 1;
    return (s1*s2<0) && (s3*s4<0);
}