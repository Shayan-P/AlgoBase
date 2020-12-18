#include<bits/stdc++.h>

using namespace std;

template<int MAX, int alpha> struct Aho{
    int nxt[MAX][alpha], f[MAX], C;

    // you can change this part
    int val[MAX];
    // you can change this part

    Aho(){
	memset(nxt, 0, sizeof nxt);
	memset(f, 0, sizeof f);
	C = 0;

	// you can change this part
	memset(val, 0, sizeof val);
	// you can change this part
    }
    void in(string s, int vl){
	// you can change this part
	int nw = 0;
	for(char c : s){
	    int x = c-'a';
	    if(nxt[nw][x] == 0)
		nxt[nw][x] = ++C;
	    nw = nxt[nw][x];
	}
	val[nw]+= vl;
	// you can change this part
    }
    void build(){
	queue<int> q;
	for(int i = 0; i < alpha; i++)
	    if(nxt[0][i] != 0)
		q.push(nxt[0][i]);
	while(!q.empty()){
	    int u = q.front();
	    q.pop();
	    
	    // you can change this part
	    val[u]+= val[ f[u] ];
	    // you can change this part

	    for(int i = 0; i < alpha; i++){
		if(nxt[u][i] == 0)
		    nxt[u][i] = nxt[ f[u] ][i];
		else
		    f[ nxt[u][i] ] = nxt[ f[u] ][i], q.push(nxt[u][i]);
	    }		
	}
    }
};

Aho<1000, 26> aho;

int main(){
    aho.in("salam", 22);
    aho.build();
}
