//本线段树以 洛谷P3373【模板】线段树2 为原型， 
//是动态开点、标记下传的线段树，
//支持区间加、区间乘、区间求和操作。
//该线段树的所有节点信息使用堆内存存储。 
//代码由wkjfive(luogu.com.cn/user/374495)编写。
 
#ifndef __SEGMENT_TREE_H__
#define __SEGMENT_TREE_H__

#include<stddef.h>
typedef long long ll;

class SegmentTree{
	public:
	typedef ll Tp;
	private:
	class Node{
    	private:
    	Tp sum;//区间和 
    	Tp delta,dt2;//加法乘法延迟标记(先乘再加) 
    	int lef,righ;//范围 
    	Tp M;//模数 
    	Node *ls,*rs;//左右孩子 
    	public:
    	Node(int l,int r,Tp Mod=1LL<<62,Tp* a=NULL);//建树 
    	Node(const Node& x);
    	Node& operator=(const Node& x);
        #if defined(__cplusplus) && __cplusplus>=201100L
    	Node(Node&& x);
    	Node& operator=(Node&& x);
        #endif
        ~Node();
        
    	void pushdown();//标记下传 
    	void modify(int l,int r,Tp k);//区间加 
    	void mutip(int l,int r,Tp k);//区间乘 
    	Tp query(int l,int r);//区间求和 
    };
	Node *root;
	public:
	SegmentTree(int size,Tp Mod=1LL<<62,Tp* a=NULL){
        //initializer_list<Tp> val
        //Tp a[n];for(int i=0;i<size;i++) a[i]=val[i];
    	root=new Node(1,size,Mod,a);
    }
	SegmentTree(const SegmentTree& x){
    	root=new node(*x.root);
    }
	SegmentTree& operator=(const SegmentTree& x){
    	delete root; root=new node(*x.root);
    }
    #if defined(__cplusplus) && __cplusplus>=201100L
	SegmentTree(SegmentTree&& x){
    	root=x.root,x.root=NULL;
    }
	SegmentTree& operator=(SegmentTree&& x){
    	delete(root); root=x.root,x.root=NULL;
    }
    #endif
    ~SegmentTree(){
    	delete root;
    }
    
	void add(int l,int r,Tp k){//区间加 
    	root->add(l,r,k);
    }
	void add(int x,int k){
    	add(x,x,k);
    }
	void mutip(int l,int r,Tp k){//区间乘 
    	root->mutip(l,r,k);
    }
	void mutip(int x,Tp k){
    	mutip(x,x,k);
    }
	Tp query(int l,int r){//区间求和 
    	return root->query(l,r);
    }
};

SegmentTree::Node::Node(int l,int r,Tp Mod,Tp* a){//建树 
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
SegmentTree::Node::Node(const Node& x){
	sum=x.sum,delta=x.delta,dt2=x.dt2,lef=x.lef,righ=x.righ,M=x.M;
	if(x.ls!=NULL) ls=new Node(*x.ls);
	if(x.rs!=NULL) rs=new Node(*x.rs);
}
SegmentTree::Node& SegmentTree::Node::operator=(const Node& x){
	if(ls!=NULL) delete ls;
	if(rs!=NULL) delete rs;
	sum=x.sum,delta=x.delta,dt2=x.dt2,lef=x.lef,righ=x.righ,M=x.M;
	if(x.ls!=NULL) ls=new Node(*x.ls);
	if(x.rs!=NULL) rs=new Node(*x.rs);
}
#if defined(__cplusplus) && __cplusplus>=201100L
SegmentTree::Node::Node(Node&& x){
	sum=x.sum,delta=x.delta,dt2=x.dt2,lef=x.lef,righ=x.righ,M=x.M;
	ls=x.ls,x.ls=NULL; rs=x.rs,x.rs=NULL;
}
SegmentTree::Node::Node& SegmentTree::Node::operator=(Node&& x){
	if(ls!=NULL) delete ls;
	if(rs!=NULL) delete rs;
	sum=x.sum,delta=x.delta,dt2=x.dt2,lef=x.lef,righ=x.righ,M=x.M;
	ls=x.ls,x.ls=NULL;rs=x.rs,x.rs=NULL;
}
#endif
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
void SegmentTree::Node::add(int l,int r,Tp k){//区间加 
	k%=M;
	if(lef==l&&righ==r){
        (sum+=k*(righ-lef+1))%=M;
        (delta+=k)%=M;
    }else{
    	pushdown();
    	int m=(lef+righ)/2;
    	if(r<=m) ls->add(l,r,k);
    	else if(l>=m+1) rs->add(l,r,k);
    	else ls->add(l,m,k),rs->add(m+1,r,k);
    	sum=(ls->sum)+(rs->sum);
    }
}
void SegmentTree::Node::mutip(int l,int r,Tp k){//区间乘 
	k%=M;
	if(lef==l&&righ==r){
        (sum*=k)%=M;
        (delta*=k)%=M,(dt2*=k)%=M; 
    }else{
    	pushdown();
    	int m=(lef+righ)/2;
    	if(r<=m) ls->mutip(l,r,k);
    	else if(l>=m+1) rs->mutip(l,r,k);
    	else ls->mutip(l,m,k),rs->mutip(m+1,r,k);
    	sum=(ls->sum)+(rs->sum);
    }
}
SegmentTree::Tp SegmentTree::Node::query(int l,int r){//区间求和     
	if(lef==l&&righ==r){
    	return sum;
    }else{
    	if(ls==NULL&&rs==NULL) return 0;
    	pushdown();
    	int m=(lef+righ)/2;
    	if(r<=m) return ls->query(l,r);
    	else if(l>=m+1) return rs->query(l,r);
    	else return ((ls->query(l,m))+(rs->query(m+1,r)))%M;
    }
}

#endif
