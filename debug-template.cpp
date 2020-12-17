// input output
template<typename A, typename B> ostream& operator << (ostream& out, pair<A, B> p){
    out << "{" << p.first << ", " << p.second << "}";
    return out;
}
template<typename T> ostream& operator << (ostream& out, vector<T> v){
    out << "[";
    for(int i = 0; i < (int)v.size(); i++){
	out << v[i];
	if(i+1 != (int)v.size())
	    out << ", ";
    }
    out << "]";
    return out;
}
template<typename A, typename B> istream& operator >> (istream& in, pair<A, B> &p){
    in >> p.first >> p.second;
    return in;
}



// auto sum and mul!
ll Sum(){ return 0;}
ll Mul(){ return 1;}
template<typename... types> ll Sum(ll x,types... y) { return ((x%mod) + Sum(y...))%mod; }
template<typename... types> ll Mul(ll x,types... y) { return (x%mod)*Mul(y...)%mod; }
