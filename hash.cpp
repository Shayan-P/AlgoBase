#include<bits/stdc++.h>

using namespace std;

struct Hasher{
    // 1 base string
    // [] segments
    // change consts to change to double hash
    const pair<int, int> P = {911382323, 972663749}, Mod = {1e9 + 7, 1e9 + 7};
    vector< pair<int, int> > hsh;
    vector< pair<int, int> > pw;
    
    pair<int, int> mkay(pair<int, int> p){
	return {p.first % Mod.first, p.second % Mod.second};
    }
    pair<int, int> mul(pair<int, int> a, pair<int, int> b){
	return {1ll * a.first * b.first % Mod.first, 1ll * a.second * b.second % Mod.second};
    }
    pair<int, int> sum(pair<int, int> a, pair<int, int> b){
	return {(a.first + b.first) % Mod.first, (a.second + b.second) % Mod.second};
    }
    pair<int, int> neg(pair<int, int> a, pair<int, int> b){// allways returns posetive
	return {(a.first - b.first + Mod.first) % Mod.first, (a.second - b.second + Mod.second) % Mod.second};
    }
    pair<int, int> all(int x){
	return {x, x};
    }

    Hasher(string s){
	build(s);
    }
    Hasher(){
	
    }
    void build(string s){
	auto One = all(1), Zero = all(0);
	pw.push_back(One);
	hsh.push_back(Zero);
	for(char c : s){
	    pw.push_back(mul(pw.back(), P));
	    hsh.push_back(sum(mul(hsh.back(), P), all(c)));
	}	
    }
    pair<int, int> get(int l, int r){ // 1 base
	assert(l >= 1);
	assert(l <= r);
	assert(r < (int)hsh.size());
	return neg(hsh[r], mul(pw[r-l+1], hsh[l-1]));
    }
};
