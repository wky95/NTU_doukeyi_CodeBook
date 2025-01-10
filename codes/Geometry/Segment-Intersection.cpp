// 判斷線段 ab, cd 是否相交
bool banana(point<auto> a, point<auto> b, point<auto> c, point<auto> d) {
    #define in(a, b, c) ( ori(a, b, c) \
            ? 0 : (sign((a-c)*(b-c)) <= 0) )
    int s1 = ori(a, b, c);
    int s2 = ori(a, b, d);
    int s3 = ori(c, d, a);
    int s4 = ori(c, d, b);
    if (in(a, b, c) || in(a, b, d) || in(c, d, a) || in(c, d, b)) return 1;
    return (s1 * s2 < 0) && (s3 * s4 < 0);
    #undef in
}