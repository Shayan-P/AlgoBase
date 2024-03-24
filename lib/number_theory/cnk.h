#include "utils.h"

namespace number_theory {
    template<int mod, int maxn>
    class CNK {
        int fac[maxn], ifac[maxn], inv[maxn];

    public:
        CNK() {
            fac[0] = 1;
            for(int i = 1; i < maxn; i++)
                fac[i] = 1ll * fac[i-1] * i % mod;
            ifac[maxn-1] = binpow<mod>(fac[maxn-1], mod-2);
            for(int i = maxn-2; i >= 0; i--)
                ifac[i] = 1ll * ifac[i+1] * (i+1) % mod;            
            inv[0] = 1;
            for(int i = 1; i < maxn; i++)
                inv[i] = 1ll * ifac[i] * fac[i-1] % mod;
        }

        int operator() (int n, int k) {
            if(k < 0 || n < k)
                return 0;
            return 1ll * fac[n] * ifac[k] % mod * ifac[n-k] % mod;
        }
    };
}
