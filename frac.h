#ifndef __FRAC_H__
#define __FRAC_H__

#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
string str(ll a){
    char s[25]; sprintf(s,"%lld",a); return s;
}
struct Frac{
    ll a,b;// a/b  只有a能为负数 
    Frac(ll aa=0,ll bb=1){
        if(bb<0) aa=-aa,bb=-bb;
        ll c=__gcd(abs(aa),bb);
        a=aa/c,b=bb/c;
    }
    Frac(const Frac& x){
        a=x.a,b=x.b;
    }
};
string str(Frac x){
    if(x.b==1) return str(x.a);
    else return str(x.a)+"/"+str(x.b);
}
Frac operator+(Frac x,Frac y){
    ll c=__gcd(x.b,y.b);
    ll a=x.a*y.b/c+y.a*x.b/c;
    ll b=x.b*y.b/c;
    return Frac(a,b);
}
Frac operator-(Frac x){
    return Frac(-x.a,x.b);
}
Frac operator-(Frac x,Frac y){
    return x+(-y);
}
Frac operator*(Frac x,Frac y){
    return Frac(x.a*y.a,x.b*y.b);
}
Frac operator/(Frac x,Frac y){
    return Frac(x.a*y.b,x.b*y.a);
}
bool operator==(Frac x,Frac y){return x.a==y.a&&x.b==y.b;}
bool operator!=(Frac x,Frac y){return !(x==y);}
istream& operator>>(istream& is,Frac& x){
    return is>>x.a>>x.b;
}
ostream& operator<<(ostream& os,Frac x){
    if(x.b==1) return os<<x.a;
    else return os<<x.a<<"/"<<x.b;
}

#endif
