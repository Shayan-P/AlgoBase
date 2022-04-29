#include<bits/stdc++.h>

using namespace std;


template<typename T> struct Matrix {
    struct All {
        int n, m;
        T x;
        All(int n, int m, T x): n(n), m(m), x(x) {}
    };

    struct Identity {
        int n;
        Identity(int n): n(n) {}
    };

    struct Diagonal {
        vector<T> d;
        Diagonal(vector<T> &d): d(d) {}
        Diagonal(vector<T> d): d(d) {}
    };

    vector<vector<T>> a;
    int n, m;

    void check_dimention() {
        if(n == 0)
            assert(m == 0);
        assert(n == (int)a.size());
        for(auto &X : a)
            assert(m == (int)X.size());
    }

    Matrix(int n, int m): n(n), m(m) {
        a.resize(n);
        for(int i = 0; i < n; i++)
            a[i].resize(m);
    }

    Matrix(const initializer_list<vector<T>> data): a(data), n(data.size()), m(data.size() ? data.begin()->size() : 0) { check_dimention(); }
    Matrix(const initializer_list<initializer_list<Matrix<T>>> data) {
        for(auto &Row: data) {
            assert(Row.size() > 0);
            int L = a.size();
            int N = Row.begin()->n;
            for(int i = 0; i < N; i++)
                a.emplace_back();
            for(auto &M: Row) {
                assert(M.n == N);
                for(int i = 0; i < N; i++)
                    for(int j = 0; j < M.m; j++)
                        a[L + i].push_back(M.a[i][j]);
            }
        }
        n = a.size();
        m = a.size() ? a[0].size() : 0;
    }


    Matrix(const Identity &I) {
        n = m = I.n;
        a.resize(n);
        for(int i = 0; i < n; i++) {
            a[i].resize(m);
            a[i][i] = 1;
        }
    }

    Matrix(const Diagonal &D) {
        n = m = D.d.size();
        a.resize(n);
        for(int i = 0; i < n; i++) {
            a[i].resize(m);
            a[i][i] = D.d[i];
        }
    }

    Matrix(const All &A) {
        n = A.n;
        m = A.m;
        a.resize(n);
        for(int i = 0; i < n; i++) {
            a[i].resize(m);
            for(int j = 0; j < m; j++)
                a[i][j] = A.x;
        }
    }

    // [)
    Matrix sub_matrix(int lx, int ly, int rx, int ry) {
        if(lx >= rx || ly >= ry)
            return Matrix(0, 0);
        Matrix ans(rx-lx, ry-ly);
        for(int i = lx; i < rx; i++)
            for(int j = ly; j < ry; j++)
                ans.a[i-lx][j-ly] = a[i][j];
        return ans;
    }

    Matrix transpose() const {
        Matrix ans(m, n);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                ans.a[j][i] = a[i][j];
        return ans;
    }

    vector<T>& operator [] (int i) {
        return a[i];
    } 

    Matrix<T> operator + (const Matrix<T> &other) const {
        assert(n == other.n && m == other.m);
        Matrix ans(n, m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                ans.a[i][j] = a[i][j] + other.a[i][j];
        return ans;
    }

    Matrix<T> operator - (const Matrix<T> &other) const {
        assert(n == other.n && m == other.m);
        Matrix ans(n, m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                ans.a[i][j] = a[i][j] - other.a[i][j];
        return ans;
    }

    Matrix<T> operator - () const {
        Matrix ans(n, m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                ans.a[i][j] = -a[i][j];
        return ans;
    }

    Matrix<T> operator * (const Matrix<T> &other) const {
        assert(m == other.n);
        int same = m;
        Matrix<T> ans(n, other.m);
        Matrix<T> other_T = other.transpose();
        for(int i = 0; i < ans.n; i++)
            for(int j = 0; j < ans.m; j++)
                for(int k = 0; k < same; k++)
                    ans.a[i][j] += a[i][k] * other_T.a[j][k];
        return ans;
    }

    Matrix<T> operator * (const T x) const {
        Matrix<T> ans(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                ans.a[i][j] = a[i][j] * x;
            }
        }
        return ans;
    }

    Matrix<T> operator ^ (int k) const {
        assert(n == m);
        Matrix<T> _A = *this, ans = Identity(n);
        for(; k; k>>=1, _A = _A * _A)
            if(k & 1)
                ans = ans * _A;
        return ans;
    }

    void append(const Matrix<T> &A, int axis) {
        assert(axis == 0 || axis == 1);
        if(axis == 0) {
            assert(m == A.m);
            n += A.n;
            for(int i = 0; i < A.n; i++)
                a.push_back(A.a[i]);
        } else {
            assert(n == A.n);
            m += A.m;
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < A.m; j++)
                    a[i].push_back(A.a[i][j]);
            }
        }
    }

    T trace() {
        if(n != m)
            cerr << "trace of non square matrix " << n << " " << m << endl;
        T ans = 0;
        for(int i = 0; i < n && i < m; i++)
            ans += a[i][i];
        return ans;
    }

    vector<T> sum(int axis) const {
        assert(axis == 0 || axis == 1);
        if(axis == 0) {
            vector<T> ans(m);
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++)
                    ans[j] += a[i][j];
            }
            return std::move(ans);
        } else {
            vector<T> ans(n);
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++)
                    ans[i] += a[i][j];
            }
            return std::move(ans);
        }
    }
};

template<typename T>
Matrix<T> append(const Matrix<T> &A, const Matrix<T> &B, int axis) {
    Matrix<T> copy(A);
    copy.append(B, axis);
    return copy;
}

template<typename T>
ostream& operator << (ostream &out, const vector<T> &vec) {
    out << "[";
    for(unsigned i = 0; i < vec.size(); i++) {
        out << vec[i];
        if(i+1 != vec.size())
            out << ",";
    }
    out << "]";
    return out;
}

template<typename T>
ostream& operator << (ostream &out, const Matrix<T> &M) {
    out << "Matrix " << M.n << " X " << M.m << "\n";
    out << "[";
    for(int i = 0; i < M.n; i++) {
        out << M.a[i];
        if(i+1 != M.n)
            out << ",\n";
    }
    out << "]";
    return out;
}




int main() {
    Matrix<int> M = {
        {1, 1}, 
        {1, 0}
    };
    Matrix<int> A = {
        {1},
        {1}
    };
    auto fib = [&](int n) {
        return ((M^n) * A).sub_matrix(1, 0, 2, 1).trace();
    };
    for(int i = 0; i < 10; i++) {
        cout << "fib " << i << " -> " << fib(i) << endl;
    }

    cout << (Matrix<int>){{M, M}, {M, M}} << endl;
}