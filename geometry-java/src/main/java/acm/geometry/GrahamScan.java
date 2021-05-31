package acm.geometry;

import java.util.*;

public class GrahamScan extends ConvexHull {

    GrahamScan(CycleList<Vector> points) {
        super(points);
    }
    GrahamScan(){

    }

    @Override
    public void compute() {
        Vector first = points.stream().min(Vector.xFirstComparator).get();
        points.remove(first);
        points.sort((me, other) -> -Vector.signCross(first, me, other));
        CycleList<Vector> computedConvexHull = new CycleList<>();
        computedConvexHull.add(first);
        for(Vector p : points){
            while (computedConvexHull.size() >= 2 && Vector.signCross(computedConvexHull.getRel(-2), computedConvexHull.getRel(-1), p) <= 0)
                computedConvexHull.popLast();
            computedConvexHull.add(p);
        }
        points = computedConvexHull;
    }
}
