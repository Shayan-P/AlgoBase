#include<bits/stdc++.h>

using namespace std;

// convex hull with collinear points

// vector
// segment intersection
// convex hull
// merge convex hull
// farthest points
// closest points
// momas dayere
// momas convex hull
// rotating calipers
// rotation
// circle intersection
// circle and line intersection
// circle union
// chan algorithm

// 3d convex hull

typedef long long geoType;

//struct Circle{

//};
struct Point{
	geoType x, y;
	Point(geoType x, geoType y): x(x), y(y) {}
	Point(): x(0), y(0) {}
	Point operator + (const Point &other){ return Point(x+other.x, y+other.y); }
	Point operator - (const Point &other){ return Point(x-other.x, y-other.y); }
  Point operator * (const geoType &k) { return Point(k * x, k * y); }
	geoType operator * (const Point &other){ return geoType(x*other.y - y*other.x); }
	geoType operator ^ (const Point &other){ return geoType(x*other.x + y*other.y); }
	void operator += (const Point &other){ x+= other.x, y+= other.y; }
	void operator -= (const Point &other){ x-= other.x, y-= other.y; }
	bool operator == (const Point &other){ return x == other.x && y == other.y; }
	bool operator != (const Point &other){ return x != other.x || y != other.y; }
};
bool operator == (const Point &a, const Point &b){ return a.x == b.x && a.y == b.y; }

geoType len2(Point p) {
	return p ^ p;
}
bool rotatingCC(Point a, Point b, Point c){
	return (b-a) * (c-a) > 0;
}

bool xFirst(Point a, Point b){
	return a.x != b.x ? a.x < b.x : a.y < b.y;
}
bool slopeFirst(Point a, Point b){
	geoType x = a * b;
 	if (x != 0)
 	 	return x > 0;
  return len2(a) < len2(b);
}

struct ConvexHull{
	vector<Point> grahamScan(vector<Point> points) { 	// no three colinear points
		int leftMostId = min_element(points.begin(), points.end(), xFirst) - points.begin();
		swap(points[leftMostId], points[0]);
		Point leftMost = points[0];
		for (auto &p : points)
			p -= leftMost;
		sort(points.begin() + 1, points.end(), slopeFirst);
		vector<Point> answer;
		for (auto p : points) {
			while (answer.size() >= 2 && !rotatingCC(answer[answer.size()-2], answer[answer.size()-1], p))
				answer.pop_back();
			answer.push_back(p);  
		}
		for (auto &p : answer)
			p += leftMost;
		return answer;
	}
	vector<Point> giftWrapping(vector<Point> points) {
		Point leftMost = *min_element(points.begin(), points.end(), xFirst);
		vector<Point> ans;
		Point last = leftMost;
		Point newPoint;
		do{
      newPoint = last;
			for (auto p : points)
				if (slopeFirst(newPoint-last, p-last))
					newPoint = p;
			last = newPoint;
			ans.push_back(last);
		} while(newPoint != leftMost);
		reverse(ans.begin(),ans.end());
		return ans;
	}
	vector<Point> upperLowerHull(vector<Point> points) {
		if (points.size() == 1)
			return points;
		sort(points.begin(), points.end(), xFirst);
		vector<Point> upperHull, lowerHull;
		for (auto p : points) {
			while (upperHull.size() >= 2 && !rotatingCC(upperHull[upperHull.size()-2], p, upperHull[upperHull.size()-1]))
				upperHull.pop_back();
			upperHull.push_back(p);
		}
		reverse(points.begin(), points.end());
		for (auto p : points) {
			while (lowerHull.size() >= 2 && !rotatingCC(lowerHull[lowerHull.size()-2], p, lowerHull[lowerHull.size()-1]))
				lowerHull.pop_back();
			lowerHull.push_back(p);
		}
		/*
		   It should be better.
		 */
		lowerHull.pop_back(), upperHull.pop_back();
		for (auto p : lowerHull)
			upperHull.push_back(p);
		
		return upperHull;
	}
};















Point randomPoint(){
	int MAX_INT = 300000000;
	return Point((rand() % MAX_INT) - MAX_INT/2, (rand() % MAX_INT) - MAX_INT/2);
}
vector<Point> randomGeneratorCollinear(int n){
	vector<Point> points;
  while(points.size() < n){
  	Point p1 = randomPoint(), p2 = randomPoint();
  	points.push_back(p1);
    if(points.size() < n){
      points.push_back(p2);
		}
    if(points.size() < n){
      points.push_back(p1 + (p2 - p1) * 2);
		}
    if(points.size() < n){
      points.push_back(p1 + (p2 - p1) * 3);
		}
	}
  return points;
}
vector<Point> randomGenerator(int n){
	vector<Point> points;
  while(points.size() < n){
  	points.push_back(randomPoint());
	}
  return points;
}
bool checkEqual(vector<Point> a, vector<Point> b){
  sort(a.begin(), a.end(), xFirst);
  sort(b.begin(), b.end(), xFirst);
  if(a.size() != b.size())
    return false;
  bool yes = 1;
  for(int i = 0; i < a.size(); i++)
    yes&= a[i] == b[i];
  return yes;
}

int main(){
	ios_base::sync_with_stdio(false);

  srand(time(0));

	int tc;
#ifndef random_test
		cin >> tc;
#else
    tc = 1000;
#endif
	int sz = 1;
	while (tc --){
		int n;
#ifndef random_test
		cin >> n;
#else
    n = 100000;
#endif
#ifndef random_test
		vector<Point> p(n);
		for (int i = 0; i < n; i++){
			int x, y;
			cin >> x >> y;
			p[i] = Point(x,y);
		}
#else
    vector<Point> p = randomGeneratorCollinear(n);
#endif
  	ConvexHull ch;
#ifndef random_test
		p = ch.giftWrapping(p);
		cout << "Case #" << sz++ << '\n';
		for (auto it : p)
			cout << it.x << " " << it.y << '\n';	
#else
    cout << "Case #" << sz++ << endl;
//    cout << "test case:\n";
//		for (auto it : p)
//			cout << it.x << " " << it.y << "\n";	
    assert(checkEqual(ch.grahamScan(p), ch.giftWrapping(p)));
#endif
	}
}