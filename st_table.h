#ifndef __ST_TABLE_H__
#define __ST_TABLE_H__

#include<vector>

typedef long long ll;

struct StTable{//ST表 
    typedef ll Tp;
	static int lg2(ll x){
	    for(int i=0;i<=62;i++) if(x<(1<<i)) return i-1;
	    return 62;
	}
    int n,L;
    std::vector<std::vector<Tp> > a1,a2; //a中[i,i+2^j)最大值，最小值 
    StTable(int nn, Tp a[]){
        n=nn,L=lg2(n)+1; a1.resize(n),a2.resize(n);
        for(int i=1;i<=n;i++) 
            a1[i].resize(L),a2[i].resize(L),a1[i][0]=a2[i][0]=a[i];
        for(int j=1;j<L;j++)
            for(int i=1;i+(1<<j)-1<=n;i++){
                int p=i+(1<<(j-1));
                a1[i][j]=std::max(a1[i][j-1],a1[p][j-1]);
                a2[i][j]=std::min(a2[i][j-1],a2[p][j-1]);
            }
    }
    ll mx(int x,int y){
        int l=lg2(y-x+1);
        return std::max(a1[x][l],a1[y-(1<<l)+1][l]);
    }
    ll mn(int x,int y){
        int l=lg2(y-x+1);
        return std::min(a2[x][l],a2[y-(1<<l)+1][l]);
    }
};

#endif
