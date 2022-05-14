#include <bits/stdc++.h>

using namespace std;

template <size_t N>
struct PrimeTable {
  constexpr PrimeTable() : sieve() {
    sieve[0] = sieve[1] = false;
    for (size_t i = 2; i < N; i++) sieve[i] = true;
    for (size_t i = 2; i < N; i++) {
      if (sieve[i])
        for (size_t j = i*i; j < N; j += i) sieve[j] = false;
    }
  }
  bool sieve[N];
};


// proof that it actually works in compile time:

// template<bool b> 
// struct BoolTeller {
//     BoolTeller() {
//         cout << "my bool is " << b << endl;
//     }
// };

// int main() {
//   BoolTeller<PrimeTable<100000>().sieve[3]>();
//   return 0;
// }

// compile fails since -fconstexpr-loop-limit=262144
int main() {
    const int MAX = 2e5;
    constexpr PrimeTable<MAX> prime_table;
    auto start = chrono::steady_clock::now();
    cout << "IS " << MAX-1 << " prime? " << prime_table.sieve[MAX-1] << endl;
    auto end = chrono::steady_clock::now();
    cout << "took " << chrono::duration<double>(end - start).count() << " seconds " << endl;
}