struct DSU{
    pii par[maxn];
    vector<pair<int, pii>> vec;
    vector<int> rec;
    
    DSU(){
	fill(par, par + maxn, (pii){-1, 0});
    }
    void record(){
	rec.PB(sz(vec));
    }
    void undo(){
	int SZ = rec.back();
	rec.pop_back();
	while(sz(vec) > SZ){
	    par[vec.back().F] = vec.back().S;
	    vec.pop_back();
	}
    }
    pii fnd(int u){
	if(par[u].F < 0)
	    return {u, 0};
	pii p = fnd(par[u].F);
	p.S^= par[u].S;
	return p;
    }
    bool mrg(int a, int b){
	pii A = fnd(a), B = fnd(b);
	if(A.F == B.F){
	    if(A.S == B.S)
		return false;
	    else
		return true;
	}
	if(par[A.F].F > par[B.F].F)
	    swap(A, B);
	vec.PB({A.F, par[A.F]});
	vec.PB({B.F, par[B.F]});
	par[A.F].F+= par[B.F].F;
	par[B.F].F = A.F;
	par[B.F].S = A.S ^ B.S ^ 1;
	return true;
    }
};
