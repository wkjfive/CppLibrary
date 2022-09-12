#ifndef _SEGMENT_TREE_H__
#define _SEGMENT_TREE_H__

//���߶����� ���P3373��ģ�塿�߶���2 Ϊԭ�ͣ���
//�Ƕ�̬���㡢����´����߶�����֧������ӡ�
//����ˡ�������Ͳ��������߶��������нڵ���Ϣʹ�� 
//��̬�ռ䣨���ڴ棩�洢�� 
//������wkjfive(luogu.com.cn/user/374495)��д�� 

#include<stdlib.h>
using namespace std;
typedef long long ll;

class SegmentTree{
	private:
	class Node{
		private:
		ll sum;//����� 
		ll delta;//�ӷ��ӳٱ�� 
		ll dt2;//�˷��ӳٱ��(�ȳ��ټ�) 
		int lef,righ;//��Χ 
		ll M;//ģ�� 
		Node *ls,*rs;//���Һ��� 
		public:
		Node(int l,int r,ll Mod=1LL<<62,ll *a=NULL);//���� 
		~Node();
		void pushdown();//����´� 
		void modify(int l,int r,ll x);//����� 
		void mutip(int l,int r,ll x);//����� 
		ll query(int l,int r);//������� 
	};
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
	void modify(int l,int r,ll x){//����� 
		root->modify(l,r,x);
	}
	void mutip(int l,int r,ll x){//����� 
		root->mutip(l,r,x);
	}
	ll query(int l,int r){//������� 
		return root->query(l,r);
	}
};

SegmentTree::Node::Node(int l,int r,ll Mod,ll *a){//���� 
	M=Mod;
	lef=l,righ=r;
	delta=0;dt2=1;
	if(l==r){
		if(a!=NULL) sum=a[l];
		else sum=0;
	}else{
		int m=(l+r)/2;
		ls=new Node(l,m,M,a);
		rs=new Node(m+1,r,M,a);
		sum=(ls->sum)+(rs->sum);
	} sum%=M;
}
SegmentTree::Node::~Node(){
	if(ls!=NULL) delete ls;
	if(rs!=NULL) delete rs;
}
void SegmentTree::Node::pushdown(){//����´� 
	//�� 
	((ls->sum)*=dt2)%=M;
	((ls->delta)*=dt2)%=M,((ls->dt2)*=dt2)%=M;
	((ls->sum)+=delta*((ls->righ)-(ls->lef)+1))%=M;
	((ls->delta)+=delta)%=M;
	//�� 
	((rs->sum)*=dt2)%=M;
	((rs->delta)*=dt2)%=M,((rs->dt2)*=dt2)%=M;
	((rs->sum)+=delta*((rs->righ)-(rs->lef)+1))%=M;
	((rs->delta)+=delta)%=M;
	//ɾ����� 
	delta=0;
	dt2=1;
}
void SegmentTree::Node::modify(int l,int r,ll x){//����� 
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
void SegmentTree::Node::mutip(int l,int r,ll x){//����� 
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
ll SegmentTree::Node::query(int l,int r){//������� 
	if(lef==l&&righ==r){
		return sum;
	}else{
		pushdown();
		int m=(lef+righ)/2;
		if(r<=m) return ls->query(l,r);
		else if(l>=m+1) return rs->query(l,r);
		else return ((ls->query(l,m))+
			(rs->query(m+1,r)))%M;
	}
}

#endif
