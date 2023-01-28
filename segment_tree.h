#ifndef __SEGMENT_TREE_H__
#define __SEGMENT_TREE_H__

//本线段树以 洛谷P3373【模板】线段树2 为原型， 
//是动态开点、标记下传的线段树，
//支持区间加、区间乘、区间求和操作。
//该线段树的所有节点信息使用堆内存存储。 
//代码由wkjfive(luogu.com.cn/user/374495)编写。 

#include<stddef.h>
//using namespace std;
typedef long long ll;

class SegmentTree{
	public:
	class Node{
		private:
		ll sum;//区间和 
		ll delta,dt2;//加法乘法延迟标记(先乘再加) 
		int lef,righ;//范围 
		ll M;//模数 
		Node *ls,*rs;//左右孩子 
		public:
		Node(int l,int r,ll Mod=1LL<<62,ll *a=NULL);//建树 
		~Node();
		void pushdown();//标记下传 
		void modify(int l,int r,ll x);//区间加 
		void mutip(int l,int r,ll x);//区间乘 
		ll query(int l,int r);//区间求和 
	};
	private:
	Node *root;
	public:
	SegmentTree(int size,ll Mod=1LL<<62,ll *a=NULL){
		//initializer_list<ll> val
		//ll a[n];for(int i=0;i<size;i++) a[i]=val[i];
		root=new Node(1,size,Mod,a);
	}
	~SegmentTree(){
		delete root;
	}
	void modify(int l,int r,ll x){//区间加 
		root->modify(l,r,x);
	}
	void mutip(int l,int r,ll x){//区间乘 
		root->mutip(l,r,x);
	}
	ll query(int l,int r){//区间求和 
		return root->query(l,r);
	}
};

SegmentTree::Node::Node(int l,int r,ll Mod,ll *a){//建树 
	M=Mod;lef=l,righ=r;delta=0,dt2=1;ls=rs=NULL;
	if(l==r){
		if(a==NULL) sum=0;
		else sum=a[l];
	}else{
		int m=(l+r)/2;
		if(a==NULL) sum=0;
		else{
			ls=new Node(l,m,M,a);
			rs=new Node(m+1,r,M,a);
			sum=(ls->sum)+(rs->sum);
		}
	} sum%=M;
}
SegmentTree::Node::~Node(){
	if(ls!=NULL) delete ls;
	if(rs!=NULL) delete rs;
}
void SegmentTree::Node::pushdown(){//标记下传 
	int m=(lef+righ)/2;
	//左 
	if(ls==NULL) ls=new Node(lef,m,M);
	((ls->sum)*=dt2)%=M;
	((ls->delta)*=dt2)%=M,((ls->dt2)*=dt2)%=M;
	((ls->sum)+=delta*((ls->righ)-(ls->lef)+1))%=M;
	((ls->delta)+=delta)%=M;
	//右 
	if(rs==NULL) rs=new Node(m+1,righ,M);
	((rs->sum)*=dt2)%=M;
	((rs->delta)*=dt2)%=M,((rs->dt2)*=dt2)%=M;
	((rs->sum)+=delta*((rs->righ)-(rs->lef)+1))%=M;
	((rs->delta)+=delta)%=M;
	//删除标记 
	delta=0; dt2=1;
}
void SegmentTree::Node::modify(int l,int r,ll x){//区间加 
	x%=M;
	if(lef==l&&righ==r){
		(sum+=x*(righ-lef+1))%=M;
		(delta+=x)%=M;
	}else{
		pushdown();
		int m=(lef+righ)/2;
		if(r<=m) ls->modify(l,r,x);
		else if(l>=m+1) rs->modify(l,r,x);
		else ls->modify(l,m,x),rs->modify(m+1,r,x);
		sum=(ls->sum)+(rs->sum);
	}
}
void SegmentTree::Node::mutip(int l,int r,ll x){//区间乘 
	x%=M;
	if(lef==l&&righ==r){
		(sum*=x)%=M;
		(delta*=x)%=M,(dt2*=x)%=M; 
	}else{
		pushdown();
		int m=(lef+righ)/2;
		if(r<=m) ls->mutip(l,r,x);
		else if(l>=m+1) rs->mutip(l,r,x);
		else ls->mutip(l,m,x),rs->mutip(m+1,r,x);
		sum=(ls->sum)+(rs->sum);
	}
}
ll SegmentTree::Node::query(int l,int r){//区间求和 
	if(lef==l&&righ==r){
		return sum;
	}else{
		pushdown();
		int m=(lef+righ)/2;
		if(r<=m) return ls->query(l,r);
		else if(l>=m+1) return rs->query(l,r);
		else return ((ls->query(l,m))+(rs->query(m+1,r)))%M;
	}
}

#endif
