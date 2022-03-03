#include<bits/stdc++.h>

using namespace std;

typedef long long ll;


// copy from here --->

const int mod = 998244353;

int binpow(int a, int b) {
    int ans = 1;
    for(; b; a = 1ll * a * a % mod, b>>=1) {
        if(b & 1)
            ans = 1ll * ans * a % mod;
    }
    return ans;
}

struct Matrix {
	int n , m;
	vector < vector < int > > a;

	void print() {
		cerr << "matrix size(" << n << " , " << m << ")\n";
		for(int i = 0;i < n;++ i) {
			for(int j = 0;j < m;++ j)
				cerr << a[i][j] << " ";
			cerr << "\n";
		}
	}
	Matrix(int _n , int _m) {
		n = _n;
		m = _m;
		a.clear();
		a.resize(n , vector < int >(m , 0));
	}

    static Matrix identity(int n) {
        Matrix r(n, n);
        for(int i = 0; i < n; i++)
            r.a[i][i] = 1;
        return r;
    }

	Matrix operator + (const Matrix& X) {
		assert(n == X.n && m == X.m);
		Matrix r(n , m);
		for(int i = 0;i < n;++ i)
			for(int j = 0;j < m;++ j)
				r.a[i][j] = (a[i][j] + X.a[i][j]) % mod;
		return r;
	}
	Matrix operator - (const Matrix& X) {
		assert(n == X.n && m == X.m);
		Matrix r(n , m);
		for(int i = 0;i < n;++ i)
			for(int j = 0;j < m;++ j)
				r.a[i][j] = (a[i][j] - X.a[i][j] + mod) % mod;
		return r;
	}
	Matrix operator * (const Matrix& X) {
		assert(m == X.n);
		Matrix r(n , X.m);
		for(int i = 0;i < n;++ i)
			for(int k = 0;k < m;++ k)
				for(int j = 0;j < X.m;++ j)
					r.a[i][j] = (r.a[i][j] + a[i][k] * 1ll * X.a[k][j]) % mod;
		return r;
	}
	Matrix operator ^ (long long pw) {
		assert(n == m);
		Matrix r = identity(n);
		Matrix aux = (* this);
		for(;pw;pw >>= 1 , aux *= aux)
			if(pw & 1)
				r = r * aux;
		return r;
	}
	void operator += (const Matrix& X) { (* this) = (* this) + X; }
	void operator *= (const Matrix& X) { (* this) = (* this) * X; }
	void operator ^= (long long pw) { (* this) = (* this) ^ pw; }

    void to_reduced_echelon() { // transform to reduced echelon form
        int row = 0;
        for(int col = 0; col < m; col++) {
            int idx = -1;
            for(int i = row; i < n; i++) {
                if(a[i][col] != 0)
                    idx = i;
            }
            if(idx == -1) {
                continue;
            }
            swap(a[row], a[idx]);
            assert(a[row][col] != 0);
            int inv = binpow(a[row][col], mod-2);
            for(int j = 0; j < m; j++) {
                a[row][j] = 1ll * a[row][j] * inv % mod;
            }
            assert(a[row][col] == 1);
            for(int i = 0; i < n; i++) {
                if(i != row && a[i][col] != 0) {
                    int cof = a[i][col];
                    for(int j = 0; j < m; j++) {
                        a[i][j] = (1ll * a[i][j] - 1ll * a[row][j] * cof) % mod;
                    }
                }
            }
            row++;
        }
    }

    bool operator == (const Matrix &M) {
        if(M.m != m || M.n != n)
            return false;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(M.a[i][j] != a[i][j])
                    return false;
            }
        }
        return true;
    }
};
