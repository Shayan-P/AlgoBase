#include <bits/stdc++.h>

using namespace std;

constexpr long long fib(int n) {
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;
    return fib(n-1) + fib(n-2);
}

template<long long T> struct Fib_Calculator {
    long long get() {
        return T;
    }
};

int main() {
    cout << Fib_Calculator<fib(90)>().get() << endl;
}