#include <bits/stdc++.h>

using namespace std;


template<typename ... T> int sum(T ... t) {
    int res = 0;
    auto sum = [&](auto&& x) {
        cout << "HEY " << x << endl;
        res += x;
        cout << "RES " << res << endl;
    };
    (sum(t), ...);
    return res;
}

template<typename ... T> bool all(T ... t) {
    return (t && ...);
}

#define any _any_

template<typename ... T> bool any(T ... t) {
    return (t || ...);
}

int main() {
    cout << sum(1, 2, 3, 10) << endl; // 16
    cout << any(0, 0, nullptr) << endl; // false
    cout << any(0, 0, 19) << endl; // true
    cout << all(1, 2, 3, 4, 5) << endl; // true
    cout << all() << endl; // true
}