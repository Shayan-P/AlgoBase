package acm.geometry;

import java.util.ArrayList;

public class CycleList<E> extends ArrayList<E> {
    public E getRel(int pos, int nxt){
        return get(getRelIndex(pos, nxt));
    }
    public E getRel(int nxt){
        return getRel(size(), nxt);
    }
    public void popLast(){
        remove(size()-1);
    }
    public int getRelIndex(int pos, int nxt){
        pos+= nxt;
        if(pos >= size() || pos < 0) {
            pos %= size();
            if(pos < 0)
                pos += size();
        }
        return pos;
    }
}
