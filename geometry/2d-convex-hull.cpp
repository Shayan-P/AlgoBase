#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

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

// to change directions just multyply this function with -1
geo_type operator * (point a, point b){
    return a.first * b.second - a.second * b.first;
}
geo_type len2(point a){
    return a ^ a;
}

inline bool counter_clockwise(point a, point b, point c){
    return (b-a) * (c-a) > 0;
}

// dont know how to handle collinear lines!
/*inline bool counter_clockwise_with_equal(point a, point b, point c){
    geo_type crs = (b-a) * (c-a);
    if(crs != 0)
        return crs > 0;
    geo_type ab = len2(b-a), ac = len2(c-a);
    return ab < ac;
}*/

vector<point> graham_scan(vector<point> pts){ // no &pts
    int n = pts.size();
    for(int i = 1; i < n; i++){
        if(pts[0] > pts[i])
            swap(pts[0], pts[i]);            
    }
    sort(pts.begin() + 1, pts.end(), [&](point a, point b){ return counter_clockwise(pts[0], a, b); });
    vector<point> ans;
    for(int i = 0; i < n; i++){
        while(ans.size() > 1 && !counter_clockwise(ans[ans.size()-2], ans[ans.size()-1], pts[i]))
            ans.pop_back();
        ans.push_back(pts[i]);  
    }
    return ans;
}

// split with respect to line outer -> line[id] and returns length of one side
// handling that outer can be one of the hull points?
int split_hull(vector<point> &hull, point outer, int id){
    assert(hull.size() >= 1);
    int n = hull.size(), l = 1, r = n;
    bool state = counter_clockwise(outer, hull[id], hull[(id+1) %n]);
    while(r-l > 1){
        int mid = (l+r) >> 1;
        point p = hull[(id + mid) % n];
        if(counter_clockwise(outer, hull[id], p) == state)
            l = mid;
        else
            r = mid;
    }
    return r;
}
int first_touch_half_hull_id(vector<point> &hull, point outer, int id, int half_len){
    assert(half_len >= 1);
    int n = hull.size();
    int l = 0, r = half_len-1;
    while(r-l > 1){
        int mid = (l+r) >> 1;
        point p1 = hull[(id + mid) % n], p2 = hull[(id + mid + 1) %n];
        if(counter_clockwise(outer, p1, p2))
            r = mid;
        else
            l = mid;
    }
    return (id + r) % n;
}

// does it work if outer is one of the hull points?
point first_touch_trival(vector<point> &hull, point outer){
    assert(!hull.empty());
    int n = hull.size();
    point ans = hull[0];
    for(int i = 0; i < n; i++){
        if(!counter_clockwise(outer, ans, hull[i]))
            ans = hull[i];
    }
    return ans;
}
point first_touch(vector<point> &hull, point outer){
    assert(hull.size() >= 1);
    int n = hull.size();
    if(n == 1)
        return hull[0];
    int ln = split_hull(hull, outer, 0), id = 0;
    int is_cc = counter_clockwise(outer, hull[0], hull[1]);
    if(is_cc){
        id = ln;
        ln = n-ln + 1;
    }
    return hull[first_touch_half_hull_id(hull, outer, id, ln)];
}
vector<point> merge_convex_hulls(vector< vector<point> > &hulls, int stop_limit){
    assert(hulls.size() >= 1);
    point start = hulls[0][0];
    for(vector<point> &hull : hulls){
        for(point pt: hull){
            if(start > pt)
                start = pt;
        }
    }
    vector<point> ans;
    point tmp = start;
    do{
        point tmp2 = tmp;
        ans.push_back(tmp);
        for(vector<point> &hull : hulls){
            point pt = first_touch(hull, tmp);
            if(tmp != tmp2 || !counter_clockwise(tmp, tmp2, pt))
                tmp2 = pt;
        }
        tmp = tmp2;
    }while((int)ans.size() <= stop_limit && tmp != start);
    return ans;
}
vector<point> chan2(vector<point> pts){
    int n = pts.size();
    for(int bucket : {1<<1, 1<<2, 1<<4, 1<<8, 1<<16, n}){
        vector< vector<point> > hulls;
        vector<point> vec;
        for(int i = 0; i < n; i++){
            vec.push_back(pts[i]);
            if((int)vec.size() == bucket || i == n-1){
                hulls.push_back(graham_scan(vec));
                vec.clear();
            }
        }
        vector<point> ans = merge_convex_hulls(hulls, bucket);
        if((int)ans.size() <= bucket)
            return ans;
    }
    assert(0);
}


int main(){
    
}

// merging convex hulls in linear time?
