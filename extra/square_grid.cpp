#include<bits/stdc++.h>

using namespace std;


template <typename T>
class Grid {    
    struct Linear_Combination {
        int cofx, cofy, bias;
        Linear_Combination operator + (const Linear_Combination& other) { return {cofx + other.cofx, cofy + other.cofy, bias + other.bias}; }
        Linear_Combination operator - (const Linear_Combination& other) { return {cofx - other.cofx, cofy - other.cofy, bias - other.bias}; }
        Linear_Combination operator * (const int x) { return {cofx * x, cofy * x, bias * x}; }
        Linear_Combination operator + (const int x) { return {cofx, cofy, bias + x}; }
        Linear_Combination operator - (const int x) { return {cofx, cofy, bias - x}; }
        Linear_Combination operator - () { return {-cofx, -cofy, -bias}; }
        int operator () (int x, int y) { return cofx * x + cofy * y + bias; }
        void swap_axes() { swap(cofx, cofy); }
    };

    int N;
    vector<vector<T>> a;
    Linear_Combination X_ind = {1, 0, 0}, Y_ind = {0, 1, 0};

public:
    Grid(int N): N(N), a(N) {
        for(auto &v: a)
            v.resize(N);
    }
    Grid twisted_like() {
        Grid res(N);
        res.X_ind = X_ind;
        res.Y_ind = Y_ind;
        return res;
    }

    int get_n() {return N;}

    void untwist() {
        X_ind = {1, 0, 0};
        Y_ind = {0, 1, 0};
    }
    void rotate_right() {
        Linear_Combination new_x = -Y_ind + (N-1);
        Linear_Combination new_y = X_ind;
        X_ind = new_x;
        Y_ind = new_y;
    }
    void rotate_left() {
        Linear_Combination new_x = Y_ind;
        Linear_Combination new_y = -X_ind + (N-1);
        X_ind = new_x;
        Y_ind = new_y;
    }
    void swap_axes() {
        X_ind.swap_axes();
        Y_ind.swap_axes();
    }
    void reverse_x() {
        X_ind = -X_ind + (N-1);
    }
    void reverse_y() {
        Y_ind = -Y_ind + (N-1);
    }
    Grid copy() {
        Grid res(N);
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                res.a[i][j] = (*this)(i, j);
    }
    T& operator () (int i, int j) {
        int ii = X_ind(i, j), jj = Y_ind(i, j);
        return a[ii][jj];
    }
};

template <typename T>
ostream& operator << (ostream& out, Grid<T> &g) {
    for(int i = 0; i < g.get_n(); i++) {
        for(int j = 0; j < g.get_n(); j++)
            out << g(i, j) << " \n"[j==g.get_n()-1]; 
    }
    return out;
}


int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    
    Grid<long long> g(3);
    int counter = 0;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            g(i, j) = counter++;
    cout << g << endl;

    cout << "rotate left" << endl;
    g.rotate_left();
    cout << g << endl;

    cout << "rotate left again" << endl;
    g.rotate_left();
    cout << g << endl;    

    cout << "rotate right" << endl;
    g.rotate_right();
    cout << g << endl;    

    cout << "swap axes" << endl;
    g.swap_axes();
    cout << g << endl;    

    cout << "reverse x" << endl;
    g.reverse_x();
    cout << g << endl;    

    cout << "reverse y" << endl;
    g.reverse_y();
    cout << g << endl;    

    cout << "reset rotation" << endl;
    g.untwist();
    cout << g << endl;
}
