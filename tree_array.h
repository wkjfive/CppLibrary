//本树状数组支持区间加、区间乘、区间求和操作。
//该树状数组的所有数据使用vector存储。 
//代码由wkjfive(luogu.com.cn/user/374495)编写。

#ifndef __TREE_ARRAY_H__
#define __TREE_ARRAY_H__

#include<stddef.h>
#include<vector>
typedef long long ll;
class TreeArray0{
    public:
    typedef ll Tp;
    private:
    int n;
    std::vector<Tp> v;//v[i]=sum(i-lowbit(i),i]
    public:
    TreeArray0(int nn=0,Tp *a=NULL){
        n=nn; v.resize(n+1);
        for(int i=1;i<=n;i++) v[i]=v[i-1]+a[i];
        for(int i=n;i>=1;i--) v[i]-=v[i-(i&-i)];
    }
    void add(int x,Tp k){ //单点加 
        for(;x<=n;x+=x&-x) v[x]+=k;
    }
    Tp querys(int x){ //区间求和 
        Tp k=0;
        for(;x>0;x-=x&-x) k+=v[x];
        return k;
    }
    Tp query(int l,int r){ //区间求和 
        return querys(r)-querys(l-1);
    }
    Tp query(int x){ //单点求和 
        return query(x,x); 
    }
};
class TreeArray{
    public:
    typedef TreeArray0::Tp Tp;
    private:
    TreeArray0 c,d; //c:差分; d:差分*i 
    public:
    TreeArray(int n=0,Tp *a=NULL){ 
        std::vector<Tp> s(n+1),t(n+1);
        for(int i=1;i<=n;i++) s[i]=a[i]-a[i-1],t[i]=i*s[i];
        c=TreeArray0(n,&s[0]);
        d=TreeArray0(n,&t[0]);
    }
    void add(int l,int r,Tp k){ //区间加 
        c.add(l,k),c.add(r+1,-k);
        d.add(l,k*l),d.add(r+1,-k*(r+1));
    }
    void add(int x,Tp k){ //单点加 
        add(x,x,k);
    }
    Tp querys(int x){ //区间求和 
        return c.querys(x)*(x+1)-d.querys(x);
    }
    Tp query(int l,int r){ //区间求和 
        return querys(r)-querys(l-1);
    }
    Tp query(int x){ //单点求和 
        return query(x,x);
    }
};

#endif
