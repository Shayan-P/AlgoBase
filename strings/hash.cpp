#include<bits/stdc++.h>

using namespace std;

struct Hasher{
    // 1 base string
    // [] segments
    // change consts to change to double hash
    
    typedef pair<int, int> hash_type;
    //typedef int hash_type;    
    const hash_type P = {911382323, 972663749}, Mod = {1e9+7, 1e9+7};
    //const hash_type P = 911382323, Mod = 1e9 + 7;

    vector<hash_type> hsh;
    static vector<hash_type> pw;
    
    hash_type mul(hash_type a, hash_type b){
	return {1ll * a.first * b.first % Mod.first, 1ll * a.second * b.second % Mod.second};
	//return 1ll * a * b % Mod;
    }
    hash_type sum(hash_type a, hash_type b){
	return {(a.first + b.first) % Mod.first, (a.second + b.second) % Mod.second};
	//return (a + b) % Mod;
    }
    hash_type neg(hash_type a, hash_type b){// allways returns posetive
	return {(a.first - b.first + Mod.first) % Mod.first, (a.second - b.second + Mod.second) % Mod.second};
       	//return (a - b + Mod) % Mod; 
    }
    static hash_type all(int x){
	return {x, x};
	//return x;
    }
    
    Hasher(string s){
	build(s);
    }
    Hasher(){
	
    }
    void precompute(int n){
	if(pw.empty())
	    pw.push_back(all(1));
	while((int)pw.size() <= n)
	    pw.push_back(mul(pw.back(), P));
    }    
    void build(string s){
	precompute(s.size());
	hsh.push_back(all(0));
	for(char c : s)
	    hsh.push_back(sum(mul(hsh.back(), P), all(c)));
    }
    hash_type get(int l, int r){ // 1 base
	assert(l >= 1);
	assert(l <= r);
	assert(r < (int)hsh.size());
	return neg(hsh[r], mul(pw[r-l+1], hsh[l-1]));
    }
};
vector<Hasher::hash_type> Hasher::pw = {Hasher::all(1)}; // important


// serfan jahat chap shodan pair ha
template<typename A, typename B> ostream& operator << (ostream& out, pair<A, B> p){
    out << "{" << p.first << ", " << p.second << "}";
    return out;
}

int main(){
    string s = "aaaaaaaaaaaaaaaa";
    Hasher h1("saalam"), h2;
    h2.build(s);
    cout << h1.get(2, 3) << endl;
    cout << h2.get(4, 5) << endl;
    cout << h1.get(2, 2) << endl;
}
