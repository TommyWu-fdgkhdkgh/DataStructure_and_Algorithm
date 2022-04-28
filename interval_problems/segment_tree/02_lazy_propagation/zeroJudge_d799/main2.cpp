#include <bits/stdc++.h>

#define int unsigned long long



using namespace std;



int node[2000005];

int add[2000005];

int T[500005];

int N;



void refresh(int l,int r,int ptr){
    if(add[ptr]!=0){
        node[ptr]+=add[ptr]*(r-l+1);

        if(l!=r){
            add[ptr*2]+=add[ptr];

            add[ptr*2+1]+=add[ptr];

        }

        add[ptr]=0;

    }

    return ;

}



void nodebuild(int l,int r,int ptr){
    if(l==r){
        node[ptr]=T[l];

        return ;

    }

    int m=(l+r)/2;

    nodebuild(l,m,ptr*2);

    nodebuild(m+1,r,ptr*2+1);

    node[ptr]=node[ptr*2]+node[ptr*2+1];

    return ;

}



int nodefind(int l,int r,int tl,int tr,int ptr){
    refresh(l,r,ptr);

    if(l==tl&&r==tr){
        return node[ptr];

    }

    int m=(l+r)/2;

    if(tr<=m){
        return nodefind(l,m,tl,tr,ptr*2);

    }else if(m<tl){
        return nodefind(m+1,r,tl,tr,ptr*2+1);

    }else{
        return nodefind(l,m,tl,m,ptr*2)+nodefind(m+1,r,m+1,tr,ptr*2+1);

    }

}



void nodeadd(int l,int r,int tl,int tr,int ptr,int addval){
    refresh(l,r,ptr);

    node[ptr]+=addval*(tr-tl+1);

    if(l==tl&&r==tr){
        if(l!=r){
            add[ptr*2]+=addval;

            add[ptr*2+1]+=addval;

        }

        return ;

    }

    int m=(l+r)/2;

    if(tr<=m){
        nodeadd(l,m,tl,tr,ptr*2,addval);

        return ;

    }else if(m<tl){
        nodeadd(m+1,r,tl,tr,ptr*2+1,addval);

        return ;

    }else{
        nodeadd(l,m,tl,m,ptr*2,addval);

        nodeadd(m+1,r,m+1,tr,ptr*2+1,addval);

        return ;

    }

}



signed main(){
    ios::sync_with_stdio(0);

    cin.tie(0);

    cout.tie(0);

    int i,j,k,t;

    int M,V;

    memset(node,0,sizeof(node));

    memset(add,0,sizeof(add));

    cin>>N;

    for(i=1;i<=N;++i){
        cin>>T[i];

    }

    nodebuild(1,N,1);

    cin>>M;

    for(M;M>0;--M){
        cin>>V;

        if(V==1){
            cin>>i>>j>>k;

            nodeadd(1,N,i,j,1,k);

        }

        if(V==2){
            cin>>i>>j;

            cout<<nodefind(1,N,i,j,1)<<'\n';

        }

    }

    return 0;

}
