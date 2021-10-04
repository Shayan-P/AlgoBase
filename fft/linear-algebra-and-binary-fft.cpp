#include<bits/stdc++.h>

#define bit(n, k) (((n)>>(k))&1)

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<pll, pll> pl4;


pl4 swapax(pl4 a, int axis) {
    if(axis == 0)
        return {a.second, a.first};
    return {
        {a.first.second, a.first.first},
        {a.second.second, a.second.first}
    };
}
pll operator * (pl4 a, pll b) {
    return {
        a.first.first * b.first + a.first.second * b.second,
        a.second.first * b.first + a.second.second * b.second
    };
}
pl4 operator * (pl4 a, pl4 b) {
    return {
        a * (pll){b.first.first, b.second.first},
        a * (pll){b.first.second, b.second.second}
    };
}
pll operator * (pll a, pll b) {
    return {a.first * b.first, a.second * b.second};
}
pll operator / (pll a, int x) {
    return {a.first / x, a.second / x};
}
pll bin(bool x) {
    return {!x, x};
}

struct BinaryConvoloutionFunction {
    pl4 MA;
    pl4 MB;
    pl4 MC;
    int c;

    BinaryConvoloutionFunction(pl4 _MA, pl4 _MB, pl4 _MC, int _c) {
        MA = _MA;
        MB = _MB;
        MC = _MC;
        c = _c;
    }

    pll forward(pll X, int who) {
        if(who == 0)
            return MA * X;
        else
            return MB * X;
    }

    pll backward(pll C) {
        pll x = MC * C;
        return x / c;
    }

    pll full(pll A, pll B) {
        return backward(forward(A, 0) * forward(B, 1));
    }

    BinaryConvoloutionFunction not_gate(int mask) {
        // 3 bit
        pl4 AA = MA;
        pl4 BB = MB;
        pl4 CC = MC;
        if(bit(mask, 0))
            AA = swapax(AA, 1);
        if(bit(mask, 1))
            BB = swapax(BB, 1);
        if(bit(mask, 2))
            CC = swapax(CC, 0);
        return BinaryConvoloutionFunction(AA, BB, CC, c);
    }

    bool ok(vector<vector<int>> &p) {
        for(int i: {0, 1}) {
            for(int j: {0, 1}) {
                if(full(bin(i), bin(j)) != bin(p[i][j]))
                    return false;
            }
        }
        return true;
    }
};

void transform(vector<BinaryConvoloutionFunction> &ops, ll *a, ll *b, int tw){
    for(int ind = 0, ln=1;(2*ln)<=tw;ln*=2, ind++){
        for(int l=0;l<tw;l+=ln+ln){
            for(int i=0;i<ln;i++){
                pll A = {a[l+i], a[l+ln+i]};
                pll B = {b[l+i], b[l+ln+i]};
                A = ops[ind].forward(A, 0);
                B = ops[ind].forward(B, 1);
                a[l+i] = A.first, a[l+ln+i] = A.second;
                b[l+i] = B.first, b[l+ln+i] = B.second;
            }
        }
    }
}
void inv_transform(vector<BinaryConvoloutionFunction> &ops, ll *c, int tw){
    for(int ind = 0, ln=1;(2*ln)<=tw;ln*=2, ind++){
        for(int l=0;l<tw;l+=ln+ln){
            for(int i=0;i<ln;i++){
                pll C = {c[l+i], c[l+ln+i]};
                C = ops[ind].backward(C);
                c[l+i] = C.first, c[l+ln+i] = C.second;
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    
    pl4 XR = {{1, 1}, {1, -1}};
    pl4 AND = {{0, 1}, {1, 1}};
    pl4 ANDR = {{-1, 1}, {1, 0}};
    pl4 TWO = {{1, 1}, {1, 1}};
    pl4 ONE = {{1, 0}, {0, 1}};
    pl4 T = {{1, 1}, {0, 0}};

    vector<vector<int>> and_truth_table = {{0, 0}, {0, 1}};
    vector<vector<int>> neg1_and_truth_table = {{0, 1}, {0, 0}};
    vector<vector<int>> neg2_and_truth_table = {{0, 0}, {1, 0}};
    vector<vector<int>> or_truth_table = {{0, 1}, {1, 1}};
    vector<vector<int>> first_one_important = {{0, 0}, {1, 1}};
    vector<vector<int>> neg_first_one_important = {{1, 1}, {0, 0}};

    BinaryConvoloutionFunction f(AND, AND, ANDR, 1);
    BinaryConvoloutionFunction f2(ONE, TWO, ONE, 1);

    cout << f.ok(and_truth_table) << endl; // true
    cout << f.not_gate(1).ok(neg1_and_truth_table) << endl; // true
    cout << f.not_gate(2).ok(neg2_and_truth_table) << endl; // true
    cout << f.not_gate(7).ok(or_truth_table) << endl; // true
    cout << f2.ok(first_one_important) << endl; // true
    cout << f2.not_gate(1).ok(neg_first_one_important) << endl; // true
    cout << f2.not_gate(4).ok(neg_first_one_important) << endl; // true
    cout << f2.not_gate(2).ok(neg_first_one_important) << endl; // false
    cout << f2.not_gate(7).ok(neg_first_one_important) << endl; // false
}
