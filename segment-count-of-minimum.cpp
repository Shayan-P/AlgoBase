#include<bits/stdc++.h>

using namespace std;

// add l r x
// keep minimum and count of minimum of a segment
// watch out for overflows

template<typename T, int n> struct Segment{
    T mn[4 * n], mnc[4 * n], lz[4 * n];

    Segment(){
	memset(mn, 0, sizeof mn);
	memset(lz, 0, sizeof lz);
	build();
    }
    void build(int l = 0, int r = n, int id = 1){ // initialize
	mnc[id] = r-l;
	if(r-l == 1)
	    return;
	int mid = (l+r) >> 1;
	build(l, mid, 2*id);
	build(mid, r, 2*id+1);
    }
    void shift(int l, int r, int id){
	mn[id]+= lz[id];
	if(r-l > 1){
	    lz[2*id]+= lz[id];
	    lz[2*id+1]+= lz[id];
	}
	lz[id] = 0;
    }
    void merge(int id){
	mn[id] = min(mn[2*id], mn[2*id+1]);
	mnc[id] = 0;
	if(mn[id] == mn[2*id])
	    mnc[id]+= mnc[2*id];
	if(mn[id] == mn[2*id+1])
	    mnc[id]+= mnc[2*id+1];	
    }
    void add(int f, int s, T x, int l = 0, int r = n, int id = 1){
	shift(l, r, id); // important
	if(f >= s || l >= r || r <= f || s <= l)
	    return;
	shift(l, r, id);
	if(f <= l && r <= s){
	    lz[id]+= x;
	    shift(l, r, id);
	    return;
	}
	int mid = (l+r) >> 1;
	add(f, s, x, l, mid, 2*id);
	add(f, s, x, mid, r, 2*id+1);
	merge(id);
    }    
};

Segment<long long, 100> s;

int main(){
    s.add(1, 4, -2);
    s.add(4, 5, 2);
    cout << s.mnc[1] << endl;
}
