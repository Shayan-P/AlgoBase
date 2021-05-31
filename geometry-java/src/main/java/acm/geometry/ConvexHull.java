package acm.geometry;

abstract public class ConvexHull {
    CycleList<Vector> points;

    ConvexHull(CycleList<Vector> points){
        this.points = points;
    }
    ConvexHull() {
    }

    abstract public void compute();

    public void randomFill(int n, double lim){
        points = new CycleList<>();
        for(int i = 0; i < n; i++)
            points.add(Vector.random2d(lim));
    }

    public static ConvexHull trivialMerge(ConvexHull hull1, ConvexHull hull2){
        CycleList<Vector> points = new CycleList<>();
        points.addAll(hull1.points);
        points.addAll(hull2.points);
        GrahamScan grahamScan = new GrahamScan(points);
        grahamScan.compute();
        return grahamScan;
    }

    public boolean trivialCheckStrictInside(Vector v){
        for(int i = 0; i < points.size(); i++){
            if(Vector.signCross(v, points.get(i), points.getRel(i, 1)) <= 0)
                return false;
        }
        return true;
    }

    public int getPositionInTriangulation(int startPoint, Vector v){
        if(Vector.signCross(points.getRel(startPoint, 0), points.getRel(startPoint, 1), v) < 0)
            return points.getRelIndex(startPoint, 0);
        if(Vector.signCross(points.getRel(startPoint, 0), points.getRel(startPoint, -1), v) > 0)
            return points.getRelIndex(startPoint, 0);
        int l = 0, r = points.size();
        while (r-l > 1){
            int mid = (l+r) >> 1;
            if(Vector.signCross(points.get(startPoint), points.getRel(startPoint, mid), v) >= 0)
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
        return Vector.signCross(points.get(pos), points.getRel(pos, 1), v) > 0;
    }
    public boolean checkStrictOutside(Vector v){
        int pos = getPositionInTriangulation(0, v);
        if(pos == 0)
            return true;
        return Vector.signCross(points.get(pos), points.getRel(pos, 1), v) < 0;
    }

    public Vector getFistLineIntersection(Vector v) {
        int pos = getPositionInTriangulation(0, v);
        int l = 0, r = points.size();
        while(r-l > 1){
            int mid = (l+r) >> 1;
            boolean check = true;
            if(Vector.signCross(v, points.get(pos), points.getRel(pos, mid)) >= 0)
                check = false;
            if(Vector.signCross(v, points.getRel(pos, mid-1), points.getRel(pos, mid)) > 0)
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
            if(Vector.signCross(v, points.get(pos), points.getRel(pos, -mid)) <= 0)
                check = false;
            if(Vector.signCross(v, points.getRel(pos, -mid), points.getRel(pos, -mid+1)) > 0)
                check = false;
            if(check)
                l = mid;
            else
                r = mid;
        }
        return points.getRel(pos, -l);
    }
}
