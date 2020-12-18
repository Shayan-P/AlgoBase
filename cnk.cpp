#include<bits/stdc++.h>

using namespace std;

const int maxn = 1e6, mod = 1e9 + 7;

int fac[maxn], ifac[maxn];

int Pow(int a, int b){
    int ans = 1;
    for(; b; b>>=1, a = 1ll * a * a % mod)
	if(b & 1)
	    ans = 1ll * ans * a % mod;
    return ans;
}
int C(int n, int k){
    if(k < 0 || n < k)
	return 0;
    return 1ll * fac[n] * ifac[k] % mod * ifac[n-k] % mod;
}
void prep(){
    fac[0] = 1;
    for(int i = 1; i < maxn; i++)
	fac[i] = 1ll * fac[i-1] * i % mod;
    ifac[maxn-1] = Pow(fac[maxn-1], mod-2);
    for(int i = maxn-2; i >= 0; i--)
	ifac[i] = 1ll * ifac[i+1] * (i+1) % mod;
}

int main(){
    prep();
    cout << C(5, 2) << endl;
}
