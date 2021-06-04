package acm.geometry;

public class ConvexHull2d {
    CycleList<Vector> points;

    ConvexHull2d(CycleList<Vector> points){
        this.points = points;
    }
    ConvexHull2d() {
    }

    public void grahamScan(){
        Vector first = points.stream().min(Vector.xFirstComparator).get();
        points.remove(first);
        points.sort((me, other) -> -Vector.sign2dCross(first, me, other));
        CycleList<Vector> ret = new CycleList<>();
        ret.add(first);
        for(Vector p : points){
            while (ret.size() >= 2 && Vector.sign2dCross(ret.getRel(-2), ret.getRel(-1), p) <= Utils.eps)
                ret.popLast();
            ret.add(p);
        }
        points = ret;
    }

    public void randomFill(int n, double lim){
        points = new CycleList<>();
        for(int i = 0; i < n; i++)
            points.add(Vector.random2d(lim));
    }

    public static ConvexHull2d trivialMerge(ConvexHull2d hull1, ConvexHull2d hull2){
        CycleList<Vector> points = new CycleList<>();
        points.addAll(hull1.points);
        points.addAll(hull2.points);
        ConvexHull2d newHull = new ConvexHull2d(points);
        newHull.grahamScan();
        return newHull;
    }

    public boolean trivialCheckStrictInside(Vector v){
        for(int i = 0; i < points.size(); i++){
            if(Vector.sign2dCross(v, points.get(i), points.getRel(i, 1)) <= Utils.eps)
                return false;
        }
        return true;
    }

    public int getPositionInTriangulation(int startPoint, Vector v){
        if(Vector.sign2dCross(points.getRel(startPoint, 0), points.getRel(startPoint, 1), v) < -Utils.eps)
            return points.getRelIndex(startPoint, 0);
        if(Vector.sign2dCross(points.getRel(startPoint, 0), points.getRel(startPoint, -1), v) > Utils.eps)
            return points.getRelIndex(startPoint, 0);
        int l = 0, r = points.size();
        while (r-l > 1){
            int mid = (l+r) >> 1;
            if(Vector.sign2dCross(points.get(startPoint), points.getRel(startPoint, mid), v) >= Utils.eps)
                l = mid;
            else
                r = mid;
        }
        return points.getRelIndex(startPoint, l);
    }

    public boolean checkStrictInside(Vector v){
        int pos = getPositionInTriangulation(0, v);
        if(pos == 0)
            return false;
        return Vector.sign2dCross(points.get(pos), points.getRel(pos, 1), v) > Utils.eps;
    }
    public boolean checkStrictOutside(Vector v){
        int pos = getPositionInTriangulation(0, v);
        if(pos == 0)
            return true;
        return Vector.sign2dCross(points.get(pos), points.getRel(pos, 1), v) < -Utils.eps;
    }

    public Vector getFistLineIntersection(Vector v) {
        int pos = getPositionInTriangulation(0, v);
        int l = 0, r = points.size();
        while(r-l > 1){
            int mid = (l+r) >> 1;
            boolean check = true;
            if(Vector.sign2dCross(v, points.get(pos), points.getRel(pos, mid)) >= -Utils.eps)
                check = false;
            if(Vector.sign2dCross(v, points.getRel(pos, mid-1), points.getRel(pos, mid)) > Utils.eps)
                check = false;
            if(check)
                l = mid;
            else
                r = mid;
        }
        return points.getRel(pos, l);
    }

    public Vector getSecondLineIntersection(Vector v) {
        int pos = getPositionInTriangulation(0, v);
        int l = 0, r = points.size();
        while(r-l > 1){
            int mid = (l+r) >> 1;
            boolean check = true;
            if(Vector.sign2dCross(v, points.get(pos), points.getRel(pos, -mid)) <= Utils.eps)
                check = false;
            if(Vector.sign2dCross(v, points.getRel(pos, -mid), points.getRel(pos, -mid+1)) > Utils.eps)
                check = false;
            if(check)
                l = mid;
            else
                r = mid;
        }
        return points.getRel(pos, -l);
    }
}
