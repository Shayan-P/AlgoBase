namespace number_theory {
    template<int mod>
    int binpow(int a, int b){
        int ans = 1;
        for(; b; b>>=1, a = 1ll * a * a % mod)
        if(b & 1)
            ans = 1ll * ans * a % mod;
        return ans;
    }

    int binpow(int a, int b, int mod){
        int ans = 1;
        for(; b; b>>=1, a = 1ll * a * a % mod)
        if(b & 1)
            ans = 1ll * ans * a % mod;
        return ans;
    }
}
