typedef ll geo_type;
typedef pair<geo_type, geo_type> point;

point operator - (point a, point b){
    return {a.first - b.first, a.second - b.second};
}
point operator - (point a){
    return {-a.first, -a.second};
}
point operator + (point a, point b){
    return {a.first + b.first, a.second + b.second};
}
geo_type operator ^ (point a, point b){
    return a.first * b.first + a.second * b.second;
}
geo_type operator * (point a, point b){
    return a.first * b.second - a.second * b.first;
}
point operator * (point a, geo_type x){
    return {a.first * x, a.second * x};
}
point rotate(point a){
    return {-a.second, a.first};
}
bool upper(point a){
    if(a.S > 0)
        return 1;
    if(a.S < 0)
    	return 0;
    if(a.F > 0)
    	return 1;
    return 0;
}
bool cmp(point a, point b){
    if(upper(a) && !upper(b))
    	return true;
    if(!upper(a) && upper(b))
    	return false;
    return a * b > 0;
}
