#include<bits/stdc++.h>

using namespace std;

// put a value some where
// ask for sum of a range

template<typename T, int n> struct Segment{    
    T val[4 * n];

    Segment(){
	memset(val, 0, sizeof val);
    }
    void merge(int id){
	val[id] = val[2*id] + val[2*id+1];
    }
    void put(int pos, T x, int l = 0, int r = n, int id = 1){
	if(r-l == 1){
	    val[id] = x;
	    return;
	}
	int mid = (l+r) >> 1;
	if(pos < mid)
	    put(pos, x, l, mid, 2*id);
	else
	    put(pos, x, mid, r, 2*id+1);
	merge(id);
    }
    T ask(int f, int s, int l = 0, int r = n, int id = 1){
	if(f >= s || l >= r || s <= l || r <= f)
	    return 0;
	if(f <= l && r <= s)
	    return val[id];
	int mid = (l+r) >> 1;
	return ask(f, s, l, mid, 2*id) + ask(f, s, mid, r, 2*id+1);
    }
};

Segment<long long, 10> s;

int main(){
    long long big = 1e12;
    for(int i = 0; i < 10; i++)
	s.put(i, big * i);
    cout << s.ask(0, 10) << endl;
}

