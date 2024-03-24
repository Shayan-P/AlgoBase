#include<bits/stdc++.h>

#include "AlgoBase/number_theory/cnk.h"

const int mod = 1e9 + 7;
const int maxn = 1e5 + 10;

int main() {
    number_theory::CNK<mod, maxn> C;
    assert(C(5, 2) == 10);
    assert(C(maxn-1, 0) == 1);
    assert(C(maxn-1, maxn-1) == 1);
    
    std::cout << "cnk test passed" << std::endl;
}
