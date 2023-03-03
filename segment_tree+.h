//±¾Ïß¶ÎÊ÷ÒÔ Âå¹ÈP3373¡¾Ä£°å¡¿Ïß¶ÎÊ÷2 ÎªÔ­ÐÍ£¬ 
//ÊÇ¶¯Ì¬¿ªµã¡¢±ê¼ÇÏÂ´«µÄÏß¶ÎÊ÷£¬
//Ö§³ÖÇø¼ä¼Ó¡¢Çø¼ä³Ë¡¢Çø¼äÇóºÍ²Ù×÷¡£
//¸ÃÏß¶ÎÊ÷µÄËùÓÐ½ÚµãÐÅÏ¢Ê¹ÓÃ¶ÑÄÚ´æ´æ´¢¡£ 
//´úÂëÓÉwkjfive(luogu.com.cn/user/374495)±àÐ´¡£
 
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
        Tp sm;//Çø¼äºÍ 
        Tp dt,dt2;//¼Ó·¨³Ë·¨ÑÓ³Ù±ê¼Ç(ÏÈ³ËÔÙ¼Ó) 
        int lt,rt;//·¶Î§ 
        Tp M;//Ä£Êý 
        Node *ls,*rs;//×óÓÒº¢×Ó 
        
        public:
        Node(int l,int r,Tp Mod=1LL<<62,Tp* a=NULL);//½¨Ê÷ 
        Node(const Node& x);
        Node& operator=(const Node& x);
        #if defined(__cplusplus) && __cplusplus>=201100L
        Node(Node&& x);
        Node& operator=(Node&& x);
        #endif
        ~Node();
        
        void pushdown();//±ê¼ÇÏÂ´« 
        void add(int l,int r,Tp k);//Çø¼ä¼Ó 
        void mutip(int l,int r,Tp k);//Çø¼ä³Ë 
        Tp sum(int l,int r);//Çø¼äÇóºÍ 
    };
    Node *root;
    
    public:
    SegmentTree(int size,Tp Mod=1LL<<62,Tp* a=NULL){
        root=new Node(1,size,Mod,a);
    }
    SegmentTree(const SegmentTree& x){
        root=new Node(*x.root);
    }
    SegmentTree& operator=(const SegmentTree& x){
        delete root; root=new Node(*x.root);
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
        if(root!=NULL) delete root;
    }
    
    void add(int l,int r,Tp k){//Çø¼ä¼Ó 
        root->add(l,r,k);
    }
    void add(int x,int k){
        add(x,x,k);
    }
    void mutip(int l,int r,Tp k){//Çø¼ä³Ë 
        root->mutip(l,r,k);
    }
    void mutip(int x,Tp k){
        mutip(x,x,k);
    }
    Tp sum(int l,int r){//Çø¼äÇóºÍ 
        return root->sum(l,r);
    }
};

SegmentTree::Node::Node(int l,int r,Tp Mod,Tp* a){//½¨Ê÷ 
    M=Mod;lt=l,rt=r;dt=0,dt2=1;ls=rs=NULL;
    if(l==r){
        if(a==NULL) sm=0;
        else sm=a[l];
    }else{
        int m=(l+r)>>1;
        if(a==NULL) sm=0;
        else{
            ls=new Node(l,m,M,a);
            rs=new Node(m+1,r,M,a);
            sm=(ls->sm)+(rs->sm);
        }
    } sm%=M;
}
SegmentTree::Node::Node(const Node& x){
    sm=x.sm,dt=x.dt,dt2=x.dt2,lt=x.lt,rt=x.rt,M=x.M;
    if(x.ls!=NULL) ls=new Node(*x.ls);
    if(x.rs!=NULL) rs=new Node(*x.rs);
}
SegmentTree::Node& SegmentTree::Node::operator=(const Node& x){
    if(ls!=NULL) delete ls;
    if(rs!=NULL) delete rs;
    sm=x.sm,dt=x.dt,dt2=x.dt2,lt=x.lt,rt=x.rt,M=x.M;
    if(x.ls!=NULL) ls=new Node(*x.ls);
    if(x.rs!=NULL) rs=new Node(*x.rs);
}
#if defined(__cplusplus) && __cplusplus>=201100L
SegmentTree::Node::Node(Node&& x){
    sm=x.sm,dt=x.dt,dt2=x.dt2,lt=x.lt,rt=x.rt,M=x.M;
    ls=x.ls,x.ls=NULL; rs=x.rs,x.rs=NULL;
}
SegmentTree::Node::Node& SegmentTree::Node::operator=(Node&& x){
    if(ls!=NULL) delete ls;
    if(rs!=NULL) delete rs;
    sm=x.sm,dt=x.dt,dt2=x.dt2,lt=x.lt,rt=x.rt,M=x.M;
    ls=x.ls,x.ls=NULL; rs=x.rs,x.rs=NULL;
}
#endif
SegmentTree::Node::~Node(){
    if(ls!=NULL) delete ls;
    if(rs!=NULL) delete rs;
}

void SegmentTree::Node::pushdown(){//±ê¼ÇÏÂ´« 
    int m=(lt+rt)>>1;
    //×ó 
    if(ls==NULL) ls=new Node(lt,m,M);
    ((ls->sm)*=dt2)%=M;
    ((ls->dt)*=dt2)%=M,((ls->dt2)*=dt2)%=M;
    ((ls->sm)+=dt*((ls->rt)-(ls->lt)+1))%=M;
    ((ls->dt)+=dt)%=M;
    //ÓÒ 
    if(rs==NULL) rs=new Node(m+1,rt,M);
    ((rs->sm)*=dt2)%=M;
    ((rs->dt)*=dt2)%=M,((rs->dt2)*=dt2)%=M;
    ((rs->sm)+=dt*((rs->rt)-(rs->lt)+1))%=M;
    ((rs->dt)+=dt)%=M;
    //É¾³ý±ê¼Ç 
    dt=0; dt2=1;
}
void SegmentTree::Node::add(int l,int r,Tp k){//Çø¼ä¼Ó 
    k%=M;
    if(lt==l&&rt==r){
        (sm+=k*(r-l+1))%=M;
        (dt+=k)%=M;
    }else{
        pushdown();
        int m=(lt+rt)>>1;
        if(r<=m) ls->add(l,r,k);
        else if(l>=m+1) rs->add(l,r,k);
        else ls->add(l,m,k),rs->add(m+1,r,k);
        sm=(ls->sm)+(rs->sm);
    }
}
void SegmentTree::Node::mutip(int l,int r,Tp k){//Çø¼ä³Ë 
    k%=M;
    if(lt==l&&rt==r){
        (sm*=k)%=M;
        (dt*=k)%=M,(dt2*=k)%=M; 
    }else{
        pushdown();
        int m=(lt+rt)>>1;
        if(r<=m) ls->mutip(l,r,k);
        else if(l>=m+1) rs->mutip(l,r,k);
        else ls->mutip(l,m,k),rs->mutip(m+1,r,k);
        sm=(ls->sm)+(rs->sm);
    }
}
SegmentTree::Tp SegmentTree::Node::sum(int l,int r){//Çø¼äÇóºÍ     
    if(lt==l&&rt==r){
        return sm;
    }else{
        if(ls==NULL&&rs==NULL) return 0;
        pushdown();
        int m=(lt+rt)>>1;
        if(r<=m) return ls->sum(l,r);
        else if(l>=m+1) return rs->sum(l,r);
        else return ((ls->sum(l,m))+(rs->sum(m+1,r)))%M;
    }
}

#endif
