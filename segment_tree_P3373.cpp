#include<bits/stdc++.h>
#include"segment_tree.h"
using namespace std;
typedef long long ll;
const int N=100055;
int n,m;
ll M,a[N];
int main(){
	int n,m;
	scanf("%d%d%lld",&n,&m,&M);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	SegmentTree tr(n,M,a);
	for(int i=1;i<=m;i++){
		int ttt;
		scanf("%d",&ttt);
		if(ttt==1){
			int x,y;ll k;
			scanf("%d%d%lld",&x,&y,&k);
			tr.mutip(x,y,k);
		}else if(ttt==2){
			int x,y;ll k;
			scanf("%d%d%lld",&x,&y,&k);
			tr.modify(x,y,k);
		}else{
			int x,y;
			scanf("%d%d",&x,&y);
			printf("%lld\n",tr.query(x,y));
		}
	}
	return 0;
}
