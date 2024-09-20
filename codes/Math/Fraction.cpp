#include <bits/stdc++.h>
using namespace std;

/// Fraction template starts ///
#define fraction_template_bonus_check
const long long ll_overflow_warning_value = (long long)(3e9);

long long gcd(long long a, long long b){
    if(a == 0) return 0;
    if(b == 0) return a;
    if(a < b) return gcd(b,a);
    return gcd(b, a%b);
}
struct frac{
    long long a, b;
    frac(long long _a = 0, long long _b = 1){
        a = _a; b = _b;
        if(b == 0){
            cerr << "Error: division by zero\n";
            cerr << "Called : Constructor(" << _a << ", " << _b << ")\n";
            return;
        }
        if(a == 0){b = 1; return;}
        if(b < 0){a = -a; b = -b;}
        long long gcd_ab = gcd(std::abs(a), b);
        if(gcd_ab != 1){a /= gcd_ab; b /= gcd_ab;}

        #ifdef fraction_template_bonus_check
        if(std::abs(a) > ll_overflow_warning_value || b > ll_overflow_warning_value){
            cerr << "Overflow warning : " << a << "/" << b << "\n";}
        #endif // fraction_template_bonus_check
    }
    frac operator+(frac const &B){
        return frac(a*(B.b)+(B.a)*b, b*(B.b));}
    frac operator-(frac const &B){
        return frac(a*(B.b)-(B.a)*b, b*(B.b));}
    frac operator*(frac const &B){
        return frac(a*(B.a), b*(B.b));}
    frac operator/(frac const &B){
        return frac(a*(B.b), b*(B.a));}

    frac operator+=(frac const &B){
        *this = frac(a*(B.b)+(B.a)*b, b*(B.b));}
    frac operator-=(frac const &B){
        *this = frac(a*(B.b)-(B.a)*b, b*(B.b));}
    frac operator*=(frac const &B){
        *this = frac(a*(B.a), b*(B.b));}
    frac operator/=(frac const &B){
        *this = frac(a*(B.b), b*(B.a));}

    frac abs(){
        a = std::abs(a);
        return *this;
    }

    bool operator<(frac const &B){
        return a*B.b < B.a*b;}
    bool operator<=(frac const &B){
        return a*B.b <= B.a*b;}
    bool operator>(frac const &B){
        return a*B.b > B.a*b;}
    bool operator>=(frac const &B){
        return a*B.b >= B.a*b;}
    bool operator==(frac const &B){
        return a * B.b == B.a * b;}
    bool operator!=(frac const &B){
        return a * B.b != B.a * b;}
};
ostream& operator<<(ostream &os, const frac& A){
    os << A.a << "/" << A.b;
    return os;
}
/// Fraction template ends ///

void test(frac A, frac B){
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << endl;
    cout << "A + B = " << A + B << endl;
    cout << "A - B = " << A - B << endl;
    cout << "A * B = " << A * B << endl;
    cout << "A / B = " << A / B << endl;
    cout << endl;
    cout << "(A < B) = " << (A < B) << endl;
    cout << "(A <= B) = " << (A <= B) << endl;
    cout << "(A > B) = " << (A > B) << endl;
    cout << "(A >= B) = " << (A >= B) << endl;
    cout << "(A == B) = " << (A == B) << endl;
    cout << "(A != B) = " << (A != B) << endl;
    cout << "---------------\n";
    return;
}

int main(){
    frac tmp1(-7, 2);
    frac tmp2(5, 3);
    test(tmp1, tmp2);

    frac tmp3(-7);
    frac tmp4(0);
    test(tmp3, tmp4);
    return 0;
}
